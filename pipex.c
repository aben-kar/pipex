/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:07:25 by acben-ka          #+#    #+#             */
/*   Updated: 2025/02/06 01:02:08 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_executable_path(char *cmd, char **envp) {
    t_myvariable s;

    if ((access(cmd, F_OK | X_OK)) == 0)
        return (cmd);
    else
    {
        ft_perror("access");
        exit(1);
    }
    
    s.directories = get_path_directories(envp);
    if (!s.directories){
        write(2, "PATH not found in environment.\n", 31);
        return (NULL);
    }
    s.i = 0;
    while (s.directories[s.i]) {
        s.tmp = ft_strjoin(s.directories[s.i], "/");
        s.cmd_path = ft_strjoin(s.tmp, cmd);
        free(s.tmp);
        if ((access(s.cmd_path, F_OK | X_OK)) == 0) {
            ft_free(s.directories);
            return (s.cmd_path);
        }
        free(s.cmd_path);
        s.i++;
    }
    ft_free(s.directories);
    // ft_perror("access");
    // write(2, "Command not found.\n", 19);
    return NULL;
}

void execute_command(char **cmd, char **envp) {
    char *cmd_path;
    
    cmd_path = find_executable_path(cmd[0], envp);
    if (cmd_path)
        execve(cmd_path, cmd, envp);
}

void child_process_1(int *fd, char *input_file, t_myvariable *pipex, char **envp) {
    int in_file = open(input_file, O_RDONLY);
    if (in_file == -1) {
        write(2, "Failed to open input file.\n", 27);
        ft_free(pipex->cmd1);
        ft_free(pipex->cmd2);       
        exit(1);
    }
    close(fd[0]);
    dup2(in_file, 0);
    close(in_file);
    dup2(fd[1], 1);
    close(fd[1]);
    execute_command(pipex->cmd1, envp);
    ft_perror("execve");       
    ft_free(pipex->cmd1);
    ft_free(pipex->cmd2);
    exit(1);
}

void child_process_2(int *fd, char *output_file, t_myvariable *pipex, char **envp) {
    int out_file = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_file == -1) {
        write(2, "Failed to open output file '%s'.\n", 28);
        ft_free(pipex->cmd1);
        ft_free(pipex->cmd2);        
        exit(1);
    }
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    dup2(out_file, 1);
    close(out_file);
    execute_command(pipex->cmd2, envp);
    ft_perror("execve"); 
    ft_free(pipex->cmd1);
    ft_free(pipex->cmd2);       
    exit(1);
}


int main(int ac, char **av, char **envp) {
    t_myvariable s;

    if (ac != 5) {
        write (2, "Invalid number of arguments.\n", 29);
        return 1;
    }
        
    // if (!*av[1] || !*av[2] || !*av[3] || !*av[4]) {
    //     write(2, "Command not foundl.\n", 20);
    // }
        
    s.cmd1 = split_arguments(av[2]);
    s.cmd2 = split_arguments(av[3]);

    if (!s.cmd2) {
        ft_free(s.cmd1);
        write(2, "Command not foundl.\n", 20);
        exit(111);
    }

    int fd[2];
    create_pipe(fd, s.cmd1, s.cmd2);
    create_forks(fd, av, &s, envp);

    ft_free(s.cmd1);
    ft_free(s.cmd2);
    
    return 0;
}
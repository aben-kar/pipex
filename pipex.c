/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 23:07:25 by acben-ka          #+#    #+#             */
/*   Updated: 2025/02/04 23:07:27 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *find_executable_path(char *cmd, char **envp) { //26 line
    struct myvariable vr;

    if ((access(cmd, F_OK | X_OK)) == 0)
        return (cmd); 
    vr.directories = get_path_directories(envp);
    if (!vr.directories)
        handle_error("PATH not found", 1);
    vr.i = 0;
    while (vr.directories[vr.i]) {
        vr.tmp = ft_strjoin(vr.directories[vr.i], "/");
        if (!vr.tmp)
            handle_error("ft_strjoin failed", 1);
        vr.cmd_path = ft_strjoin(vr.tmp, cmd);
        free(vr.tmp);
        if (!vr.cmd_path)
            handle_error("ft_strjoin failed", 1);
        if ((access(vr.cmd_path, F_OK | X_OK)) == 0) {
            ft_free(vr.directories);
            return vr.cmd_path;
        }
        free(vr.cmd_path);
        vr.i++;
    }
    ft_free(vr.directories);
    handle_error("Command not found", 127);
    return NULL;
}

void execute_command(char **cmd, char **envp) {
    char *cmd_path;

    cmd_path = find_executable_path(cmd[0], envp);
    if (cmd_path) {
        execve(cmd_path, cmd, envp);
        handle_error("execve failed", 1);
        free(cmd_path);
        ft_free(cmd);
        exit(1);
    }
}

void child_process_1(int *fd, char *input_file, char **cmd, char **envp) {
    int in_file = open(input_file, O_RDONLY);
    if (in_file == -1) {
        handle_error("open failed", 1);
        ft_free(cmd);       
        exit(1);
    }
    close(fd[0]);
    dup2(in_file, 0);
    close(in_file);
    dup2(fd[1], 1);
    close(fd[1]);
    execute_command(cmd, envp);
}

void child_process_2(int *fd, char *output_file, char **cmd2, char **envp) {
    int out_file = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_file == -1) {
        handle_error("open failed", 1);
        ft_free(cmd2);        
        exit(1);
    }
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    dup2(out_file, 1);
    close(out_file);
    execute_command(cmd2, envp);
}


int main(int ac, char **av, char **envp) {
    t_myvariable pipex;

    if (ac != 5) {
        handle_error("Failed arguments!", 1);
        return 1;
    }
    if (!*av[1] || !*av[2] || !*av[3] || !*av[4]) {
        handle_error("Argument is empty!", 1);
    }

    pipex.cmd1 = split_arguments(av[2]);
    pipex.cmd2 = split_arguments(av[3]);

    if (!pipex.cmd2) {
        ft_free(pipex.cmd1);
        handle_error("split_arguments failed", 1);
    }

    int fd[2];
    create_pipe(fd, pipex.cmd1, pipex.cmd2);
    create_forks(fd, av, &pipex, envp);

    ft_free(pipex.cmd1);
    ft_free(pipex.cmd2);
    
    return 0;
}

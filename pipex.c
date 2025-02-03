#include "pipex.h"

char *find_executable_path(char *cmd, char **envp) {
    char **directories = NULL;
    char *cmd_path = NULL;

    if ((access(cmd, F_OK | X_OK)) == 0)
        return (cmd); 
    directories = get_path_directories(envp);
    if (!directories)
        return NULL;

    int i = 0;
    while (directories[i]) {
        char *tmp = ft_strjoin(directories[i], "/");
        if (!tmp) {
            return ft_free(directories);
        }
        cmd_path = ft_strjoin(tmp, cmd);
        free(tmp);
        if (!cmd_path) {
            return ft_free(directories);
        }
        if ((access(cmd_path, F_OK | X_OK)) == 0) {
            ft_free(directories);
            return cmd_path;
        }
        free(cmd_path);
        i++;
    }
    ft_free(directories);
    return NULL;
}

void execute_command(char **cmd, char **cmd2, char **envp) {
    char *cmd_path;

    cmd_path = find_executable_path(cmd[0], envp);
    if (cmd_path) {
        execve(cmd_path, cmd, envp);
        perror("execve");
        free(cmd_path);
        ft_free(cmd);
        ft_free(cmd2);
        exit(1);
    }
}

void child_process_1(int *fd, char *input_file, char **cmd, char **cmd2, char **envp) {
    int in_file = open(input_file, O_RDONLY | O_CREAT, 0644);
    if (in_file == -1) {
        perror("open");
        ft_free(cmd);
        ft_free(cmd2);        
        exit(1);
    }
    dup2(in_file, 0);
    close(in_file);
    close(fd[0]);
    dup2(fd[1], 1);
    close(fd[1]);
    execute_command(cmd, cmd2, envp);
}

void child_process_2(int *fd, char *output_file, char **cmd2, char **cmd, char **envp) {
    int out_file = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_file == -1) {
        perror("open");
        ft_free(cmd);
        ft_free(cmd2);        
        exit(1);
    }
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    dup2(out_file, 1);
    close(out_file);
    execute_command(cmd2, cmd, envp);
}

int main(int ac, char **av, char **envp) {
    if (ac != 5) {
        write(2, "Failed arguments!\n", 18);
        return 1;
    }
    if (!*av[1] || !*av[2] || !*av[3] || !*av[4]) {
        write(2, "Argument is empty!\n", 19);
        return 1;
    }
    char **cmd1 = ft_split(av[2], ' ');
    if (!cmd1)
        return 1;
    char **cmd2 = ft_split(av[3], ' ');
    if (!cmd2) 
        return (ft_free(cmd1), 1);
    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return (ft_free(cmd1), ft_free(cmd2), 1);
    }
    pid_t id1 = fork();
    if (id1 < 0)
    {
        perror("fork");
        return (ft_free(cmd1), ft_free(cmd2), 1);
    }
    if (id1 == 0)
        child_process_1(fd, av[1], cmd1, cmd2, envp);
    
    pid_t id2 = fork();
    if (id2 == 0)
        child_process_2(fd, av[4], cmd2, cmd1, envp);
    
    close(fd[0]);
    close(fd[1]);

    waitpid(id1, NULL, 0);
    waitpid(id2, NULL, 0);
    
    ft_free(cmd1);
    ft_free(cmd2);
    return 0;
}

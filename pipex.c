#include "pipex.h"

void execute_command(char **cmd, char **envp) { //31 line
    if ((access(cmd[0], F_OK | X_OK)) == 0)
        execve(cmd[0], cmd, envp);

    char **res = envp;
    while (*res) {
        char *found = ft_strnstr(*res, "PATH=", 5);
        if (found) {
            char **split_path = ft_split(found + 5, ':');
            if (split_path) {
                int i = 0;
                while (split_path[i]) {
                    char *tmp = ft_strjoin(split_path[i], "/");
                    char *cmd_path = ft_strjoin(tmp, cmd[0]);
                    free(tmp);
                    if ((access(cmd_path, F_OK | X_OK)) == 0) {
                        execve(cmd_path, cmd, envp);
                        free(cmd_path);
                        ft_free(split_path);
                    }
                    free(cmd_path);
                    i++;
                }
            }
            ft_free(split_path);
        }
        res++;
    }
    write(2, "command not found\n", 18);
    exit(1);
}

void child_process_1(int *fd, char *input_file, char **cmd, char **envp) {
    int in_file = open(input_file, O_RDONLY | O_CREAT, 0644);
    if (in_file == -1) {
        write(2, "Error opening input file\n", 26);
        exit(1);
    }
    dup2(in_file, 0);
    close(in_file);
    close(fd[0]);
    dup2(fd[1], 1);
    close(fd[1]);
    execute_command(cmd, envp);
    ft_free(cmd);
}

void child_process_2(int *fd, char *output_file, char **cmd, char **envp) {
    int out_file = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_file == -1) {
        write(2, "Error opening output file\n", 27);
        exit(1);
    }
    close(fd[1]);
    dup2(fd[0], 0);
    close(fd[0]);
    dup2(out_file, 1);
    close(out_file);
    execute_command(cmd, envp);
    ft_free(cmd);
}

int main(int ac, char **av, char **envp) { //34 line
    if (ac != 5) {
        write(2, "Failed arguments!\n", 18);
        return 1;
    }
    if (!*av[1] || !*av[2] || !*av[3] || !*av[4]) {
        write(2, "Argument is empty!\n", 19);
        return 1;
    }
    
    char **cmd1 = ft_split(av[2], ' ');
    char **cmd2 = ft_split(av[3], ' ');
    if (!cmd1 || !cmd2) return 1;
    
    int fd[2];
    if (pipe(fd) == -1) return 1;
    
    int id1 = fork();
    if (id1 == 0)
        child_process_1(fd, av[1], cmd1, envp);
    
    int id2 = fork();
    if (id2 == 0)
        child_process_2(fd, av[4], cmd2, envp);
    
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    
    ft_free(cmd1);
    ft_free(cmd2);
    return 0;
}

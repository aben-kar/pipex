#include "pipex.h"

char *find_executable_path(char *cmd, char **envp) {
    struct myvariable vr;

    if ((access(cmd, F_OK | X_OK)) == 0)
        return (cmd); 
    vr.directories = get_path_directories(envp);
    if (!vr.directories)
        return NULL;
    vr.i = 0;
    while (vr.directories[vr.i]) {
        vr.tmp = ft_strjoin(vr.directories[vr.i], "/");
        if (!vr.tmp)
            ft_free(vr.directories);
        vr.cmd_path = ft_strjoin(vr.tmp, cmd);
        free(vr.tmp);
        if (!vr.cmd_path)
            ft_free(vr.directories);
        if ((access(vr.cmd_path, F_OK | X_OK)) == 0) {
            ft_free(vr.directories);
            return vr.cmd_path;
        }
        free(vr.cmd_path);
        vr.i++;
    }
    ft_free(vr.directories);
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

void child_process_1(int *fd, char *input_file, char **cmd,char **cmd2, char **envp) {
    int in_file = open(input_file, O_RDONLY);
    if (in_file == -1) {
        perror("open");
        ft_free(cmd);
        ft_free(cmd2);        
        exit(1);
    }
    close(fd[0]);
    dup2(in_file, 0);
    close(in_file);
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
        // return 1;
    }
    pipex_process(av, envp);
    return 0;
}
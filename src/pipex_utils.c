/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:36:34 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/13 14:01:52 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

int	create_process(char **argv, char **paths, t_fd fds, char **envp)
{
	pid_t	pid;
	pid_t	pid1;
	int		pipefd[2];
	t_cmds	*cmds;

	if (pipe(pipefd) < 0)
		process_error(0);
	pid = fork();
	if (pid < 0)
		process_error(1);
	cmds = malloc(sizeof(t_cmds));
	get_cmd_fullname(&cmds, paths, argv[2]);
	if (pid == 0)
		handle_cmd1(fds, pipefd, cmds, envp);
	else
	{
		free(cmds->cmd_path);
		free_array(cmds->cmd_args);
		get_cmd_fullname(&cmds, paths, argv[3]);
		pid1 = fork();
		if (pid1 < 0)
			process_error(1);
		if (pid1 == 0)
			handle_cmd2(fds, pipefd, cmds, envp);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid1, NULL, 0);
	free(cmds->cmd_path);
	free_array(cmds->cmd_args);
	free(cmds);
	return (0);
}

int	handle_cmd1(t_fd fds, int pipefd[2], t_cmds *cmds, char **envp)
{
	if (dup2(fds.infile, STDIN_FILENO) < 0)
		perror("Error");
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		perror("Error");
	close(pipefd[0]);
	close(pipefd[1]);
	if (cmds->cmd_path == 0)
	{
		close(fds.infile);
		close(fds.outfile);
		exit(1);
	}
	if (execve(cmds->cmd_path, cmds->cmd_args, envp) < 0)
		perror("execve failed: ");
	close(fds.infile);
	close(fds.outfile);
	return (0);
}

int	handle_cmd2(t_fd fds, int pipefd[2], t_cmds *cmds, char **envp)
{
	if (dup2(fds.outfile, STDOUT_FILENO) < 0)
		perror("Error");
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		perror("Error");
	close(pipefd[0]);
	close(pipefd[1]);
	if (cmds->cmd_path == 0)
	{
		close(fds.infile);
		close(fds.outfile);
		exit(1);
	}
	if (execve(cmds->cmd_path, cmds->cmd_args, envp) < 0)
		perror("execve failed: ");
	close(fds.infile);
	close(fds.outfile);
	return (0);
}

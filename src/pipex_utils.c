/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:36:34 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/22 13:45:59 by tlemos-m         ###   ########.fr       */
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

void	free_cmds(char **array, char *path)
{
	free_array(array);
	free(path);
}

int	create_process(char **argv, char **paths, t_fd *fds, char **envp)
{
	pid_t	pid;
	pid_t	pid1;

	pid = -1;
	pid1 = -1;
	if (pipe(fds->pipefd) < 0)
		process_error(0, fds);
	pid = fork();
	if (pid < 0)
		process_error(1, fds);
	if (pid == 0)
	{
		if (fds->infile == -1)
			return (close_pipe(fds));
		update_pipes(fds, 0);
		if (fds->fds[0] < 0 || fds->fds[1] < 0)
			dup_failed(fds, paths);
		handle_cmd(fds, paths, argv[2], envp);
	}
	else
		pid1 = fork_process(fds, paths, argv[3], envp);
	close_and_wait(pid, pid1, fds);
	return (0);
}

int	handle_cmd(t_fd *fds, char **paths, char *argv, char **envp)
{
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	get_cmd_fullname(&cmds, paths, argv);
	if (cmds->cmd_path == 0)
	{
		close(fds->infile);
		close(fds->outfile);
		close(fds->fds[0]);
		close(fds->fds[1]);
		free_cmds(cmds->cmd_args, cmds->cmd_path);
		free(cmds);
		return (1);
	}
	if (execve(cmds->cmd_path, cmds->cmd_args, envp) < 0)
		perror("execve failed: ");
	close(fds->infile);
	close(fds->outfile);
	free_cmds(cmds->cmd_args, cmds->cmd_path);
	free(cmds);
	return (0);
}

void	update_pipes(t_fd *fds, int flag)
{
	if (flag == 0)
	{
		fds->fds[0] = dup2(fds->infile, STDIN_FILENO);
		fds->fds[1] = dup2(fds->pipefd[1], STDOUT_FILENO);
		if (fds->fds[0] < 0 || fds->fds[1] < 0)
		{
			perror("Error");
			return ;
		}
	}
	if (flag == 1)
	{
		fds->fds[0] = dup2(fds->outfile, STDOUT_FILENO);
		fds->fds[1] = dup2(fds->pipefd[0], STDIN_FILENO);
		if (fds->fds[0] < 0 || fds->fds[1] < 0)
		{
			perror("Error");
			return ;
		}
	}
	close(fds->pipefd[0]);
	close(fds->pipefd[1]);
	return ;
}

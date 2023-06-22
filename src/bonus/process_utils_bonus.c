/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 08:33:49 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/22 13:40:56 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	create_pipes(t_fd *fds)
{
	int	i;

	i = -1;
	fds->pipefd = (int **)malloc(sizeof(int *) * (fds->n_cmds));
	if (!fds->pipefd)
	{
		close_files(*fds, fds->n_cmds);
		process_error(0);
	}
	fds->pipefd[fds->n_cmds -1] = 0;
	while (++i < fds->n_cmds - 1)
	{
		fds->pipefd[i] = malloc(sizeof(int) * 2);
		if (!fds->pipefd[i] || pipe(fds->pipefd[i]) < 0)
		{
			close_files(*fds, fds->n_cmds);
			free_all(0, fds->pipefd, fds->pid);
			process_error(0);
		}
	}
	return ;
}

pid_t	fork_processes(int pid, t_fd *fds)
{
	int	i;

	i = -1;
	pid = fork();
	if (pid < 0)
	{
		close_files(*fds, fds->n_cmds);
		while (++i < fds->n_cmds - 1)
		{
			close(fds->pipefd[i][0]);
			close(fds->pipefd[i][1]);
		}
		free_all(fds->paths, fds->pipefd, fds->pid);
		process_error(1);
	}
	return (pid);
}

void	update_pipe_ends(t_fd *fds, int i)
{
	if (i == 0)
	{
		fds->fds[0] = dup2(fds->infile, STDIN_FILENO);
		fds->fds[1] = dup2(fds->pipefd[i][1], STDOUT_FILENO);
		if (fds->fds[0] < 0 || fds->fds[1] < 0)
			perror("Error");
	}
	else if (i == (fds->n_cmds - 1))
	{
		fds->fds[0] = dup2(fds->pipefd[i - 1][0], STDIN_FILENO);
		fds->fds[1] = dup2(fds->outfile, STDOUT_FILENO);
		if (fds->fds[0] < 0 || fds->fds[1] < 0)
			perror("Error");
	}
	else
	{
		fds->fds[0] = dup2(fds->pipefd[i - 1][0], STDIN_FILENO);
		fds->fds[1] = dup2(fds->pipefd[i][1], STDOUT_FILENO);
		if (fds->fds[0] < 0 || fds->fds[1] < 0)
			perror("Error");
	}
}

void	init_pid(t_fd *fds)
{
	int	i;

	i = -1;
	fds->pid = (pid_t *)malloc(sizeof(pid_t) * fds->n_cmds);
	if (!fds->pid)
	{
		close_files(*fds, fds->n_cmds);
		close_pipes(fds);
		free_all(0, fds->pipefd, fds->pid);
		perror("Error");
		exit(1);
	}
	while (++i < fds->n_cmds)
		fds->pid[i] = -1;
}

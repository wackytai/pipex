/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 08:33:49 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/02 15:49:50 by tlemos-m         ###   ########.fr       */
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
		close_files(*fds);
		process_error(0);
	}
	fds->pipefd[fds->n_cmds -1] = 0;
	while (++i < fds->n_cmds - 1)
	{
		fds->pipefd[i] = malloc(sizeof(int) * 2);
		if (!fds->pipefd[i] || pipe(fds->pipefd[i]) < 0)
		{
			close_files(*fds);
			free_pipes(fds->pipefd);
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
		close_files(*fds);
		free_array(fds->paths);
		while (++i < fds->n_cmds)
		{
			close(fds->pipefd[i][0]);
			close(fds->pipefd[i][1]);
		}
		free_pipes(fds->pipefd);
		process_error(1);
	}
	return (pid);
}

int	update_pipe_ends(t_fd *fds, int i)
{
	int	out;

	if (i == 0)
	{
		dup2(fds->infile, STDIN_FILENO);
		dup2(fds->pipefd[i][1], STDOUT_FILENO);
		out = fds->pipefd[i][1];
		printf("\tPIPE %i IN: infile\tOUT: pipefd[%i]\n", i, i);
	}
	else if (i == (fds->n_cmds - 1))
	{
		dup2(fds->pipefd[i - 1][0], STDIN_FILENO);
		dup2(fds->outfile, STDOUT_FILENO);
		out = fds->outfile;
		printf("\tPIPE %i IN: %i\tOUT: outfile\n", i, (i - 1));
	}
	else
	{
		dup2(fds->pipefd[i - 1][0], STDIN_FILENO);
		dup2(fds->pipefd[i][1], STDOUT_FILENO);
		out = fds->pipefd[i][1];
		printf("\tPIPE %i IN: pipefd[%i]\tOUT: pipefd[%i]\n", i, (i - 1), i);
	}
	return (out);
}

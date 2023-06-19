/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:36:34 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/19 10:19:54 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	free_all(char **arrays, int **ints, pid_t *pids)
{
	int	i;

	i = -1;
	if (arrays != 0)
	{
		while (arrays[++i])
			free(arrays[i]);
		free(arrays);
	}
	i = -1;
	if (ints != 0)
	{
		while (ints[++i])
			free(ints[i]);
		free(ints);
	}
	free(pids);
}

void	close_pipes(t_fd *fds)
{
	int	i;

	i = -1;
	while (fds->pipefd[++i])
	{
		close(fds->pipefd[i][0]);
		close(fds->pipefd[i][1]);
	}
	return ;
}

void	wait_processes(t_fd *fds)
{
	int	i;
	int	test;
	int	status;

	i = -1;
	while (++i < fds->n_cmds)
	{
		test = 0;
		while (!test)
		{
			test = waitpid(fds->pid[i], &status, WNOHANG);
			if (WIFEXITED(status) == 1)
				break ;
		}
	}
	return ;
}

int	handle_child(t_fd *fds, int i, char **envp)
{
	t_cmds	cmds;

	get_cmd_fullname(&cmds, fds, fds->cmd, (i + fds->ishdoc));
	update_pipe_ends(fds, i);
	close_pipes(fds);
	execve(cmds.cmd_path, cmds.cmd_args, envp);
	perror("\texecve failed: ");
	free_all(cmds.cmd_args, 0, fds->pid);
	free(cmds.cmd_path);
	free_all(fds->paths, fds->pipefd, 0);
	close(fds->infile);
	close(fds->outfile);
	exit (1);
}

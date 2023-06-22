/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:36:34 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/22 13:17:08 by gacorrei         ###   ########.fr       */
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

	i = -1;
	while (++i < fds->n_cmds)
		waitpid(fds->pid[i], NULL, 0);
	return ;
}

int	handle_child(t_fd *fds, int i, char **envp)
{
	t_cmds	cmds;

	update_pipe_ends(fds, i);
	if (fds->fds[0] < 0 || fds->fds[1] < 0)
	{
		free_all(fds->paths, 0, 0);
		close_pipes(fds);
		close(fds->infile);
		close(fds->outfile);
		exit (1);
	}
	get_cmd_fullname(&cmds, fds, fds->cmd, (i + fds->ishdoc));
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

int	get_len(char *s1, char *s2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 > len2)
		return (len1);
	else
		return (len2);
}

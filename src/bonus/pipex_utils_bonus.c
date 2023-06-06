/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:36:34 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/06 14:19:06 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	free_pipes(int **array)
{
	int	i;

	i = -1;
	while (array[++i] != 0)
		free(array[i]);
	free(array);
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

int	handle_child(t_fd *fds, int i, char **envp)
{
	t_cmds	cmds;

	get_cmd_fullname(&cmds, fds, fds->cmd, (i + fds->ishdoc));
	update_pipe_ends(fds, i);
	close_pipes(fds);
	execve(cmds.cmd_path, cmds.cmd_args, envp);
	perror("\texecve failed: ");
	free_array(cmds.cmd_args);
	free(cmds.cmd_path);
	free_array(fds->paths);
	free_pipes(fds->pipefd);
	exit (0);
}

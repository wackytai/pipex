/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:22:56 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/02 14:33:36 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

int	file_error(t_fd fds)
{
	perror("Error");
	close(fds.infile);
	close(fds.outfile);
	exit(1);
}

int	args_error(void)
{
	ft_putendl_fd("usage: ./pipex infile cmd1 cmd2 outfile", STDERR_FILENO);
	exit(1);
}

int	command_error(t_cmds *cmd, int out, int flag, t_fd fds)
{
	free_array(cmd->cmd_args);
	if (flag < (fds.n_cmds - 1))
		ft_putchar_fd('0', out);
	else
		free(cmd->cmd_path);
	close_files(fds);
	while (fds.n_cmds-- >= 0)
	{
		close(fds.pipefd[fds.n_cmds][0]);
		close(fds.pipefd[fds.n_cmds][1]);
	}
	perror("Error");
	exit(1);
}

int	process_error(int flag)
{
	if (flag == 0)
		perror("Pipe failed");
	else
		perror("Fork failed");
	exit(1);
}

void	close_files(t_fd fds)
{
	close(fds.infile);
	close(fds.outfile);
}

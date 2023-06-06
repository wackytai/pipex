/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:22:56 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/06 09:43:02 by tlemos-m         ###   ########.fr       */
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
	printf("pipex: command not found: %s\n", cmd->cmd_args[0]);
	free_array(cmd->cmd_args);
	if (flag >= (fds.n_cmds - 1) && out)
		free(cmd->cmd_path);
	close_files(fds);
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
	if (fds.ishdoc)
	{
		if (unlink("here_doc") != 0)
		{
			perror("Error");
			exit(1);
		}
	}
}

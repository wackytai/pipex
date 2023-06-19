/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:22:56 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/19 12:00:48 by tlemos-m         ###   ########.fr       */
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

int	command_error(t_cmds *cmd, char *argv, int flag, t_fd *fds)
{
	ft_printf("Command not found: '%s'\n", argv);
	if (flag >= (fds->n_cmds - 1))
		free(cmd->cmd_path);
	close_pipes(fds);
	close_files(*fds, flag);
	free_all(cmd->cmd_args, fds->pipefd, fds->pid);
	free_all(fds->paths, 0, 0);
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

void	close_files(t_fd fds, int flag)
{
	close(fds.infile);
	close(fds.outfile);
	if (fds.ishdoc && flag >= (fds.n_cmds - 1))
		unlink("here_doc");
}

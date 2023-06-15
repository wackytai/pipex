/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:22:56 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/15 17:50:53 by tlemos-m         ###   ########.fr       */
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

int	command_error(t_cmds *cmd, int out, int flag, t_fd *fds)
{
	if (cmd->cmd_args[0] == 0)
		ft_printf("Permission denied: \n");
	else
		ft_printf("Command not found: %s\n", cmd->cmd_args[0]);
	if (flag >= (fds->n_cmds - 1) && out)
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
	ft_printf("files close\n");
	if (fds.ishdoc && flag >= (fds.n_cmds - 1))
		unlink("here_doc");
}

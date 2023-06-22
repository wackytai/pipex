/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:22:56 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/22 10:22:58 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

int	file_error(t_fd fds)
{
	perror("Error");
	if (fds.infile >= 0)
		close(fds.infile);
	if (fds.outfile >= 0)
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
	char	*str;

	str = ft_strjoin("Command not found: ", argv);
	ft_putendl_fd(str, STDERR_FILENO);
	free(str);
	if (argv[0] != 0)
		ft_printf("Please ask your administrator.\n");
	if (flag >= (fds->n_cmds - 1))
		free(cmd->cmd_path);
	close_pipes(fds);
	close_files(*fds, flag);
	close(fds->fds[0]);
	close(fds->fds[1]);
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
	if (fds.infile >= 0)
		close(fds.infile);
	if (fds.outfile >= 0)
		close(fds.outfile);
	if (fds.ishdoc && flag >= (fds.n_cmds - 1))
		unlink("here_doc");
}

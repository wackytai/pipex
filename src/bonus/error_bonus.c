/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:22:56 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/26 13:49:34 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

int	file_error(char *str, t_fd fds)
{
	ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	close(fds.infile);
	close(fds.outfile);
	exit(0);
}

int	permission_error(char *str, t_fd fds)
{
	ft_putstr_fd("zsh: permission denied: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	close(fds.infile);
	close(fds.outfile);
	exit(0);
}

int	args_error(void)
{
	ft_putendl_fd("usage: ./pipex infile cmd1 cmd2 outfile", STDERR_FILENO);
	exit(0);
}

int	command_error(char *str, t_fd fds, int flag)
{
	if (flag > 0)
		ft_putchar_fd('0', fds.outfile);
	ft_putstr_fd("zsh: command not found: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (4);
}

int	process_error(int flag)
{
	if (flag == 0)
		ft_putendl_fd("Pipe failed", STDERR_FILENO);
	else
		ft_putendl_fd("Fork failed", STDERR_FILENO);
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:22:56 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/26 19:36:40 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	file_error(t_fd fds)
{
	perror("Error");
	/* ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO); */
	close(fds.infile);
	close(fds.outfile);
	exit(1);
}

int	permission_error(t_fd fds)
{
	perror("Error");
	/* ft_putstr_fd("zsh: permission denied: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO); */
	close(fds.infile);
	close(fds.outfile);
	exit(1);
}

int	args_error(void)
{
	ft_putendl_fd("usage: ./pipex infile cmd1 cmd2 outfile", STDERR_FILENO);
	exit(1);
}

int	command_error(char *str, int out, int flag)
{
	if (flag > 0)
		ft_putchar_fd('0', out);
	ft_putstr_fd("zsh: command not found: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (4);
}

int	process_error(int flag)
{
	if (flag == 0)
		perror("Pipe failed");
	else
		perror("Fork failed");
	exit(1);
}

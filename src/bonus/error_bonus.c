/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:22:56 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/31 12:41:50 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

int	file_error(t_fd fds)
{
	perror("Error");
	close(fds.infile);
	close(fds.outfile);
	exit(1);
}

int	permission_error(t_fd fds)
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

int	command_error(char *str, int out, int flag)
{
	if (flag > 0 && *str)
		ft_putchar_fd('0', out);
	perror("Error");
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

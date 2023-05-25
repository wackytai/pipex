/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:22:56 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/25 13:49:05 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"


int	file_error(char *str)
{
	ft_putstr_fd("zsh: no such file or directory: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (1);
}

int	permission_error(char *str)
{
	ft_putstr_fd("zsh: permission denied: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (2);
}

int	args_error(void)
{
	ft_putendl_fd("Usage: ./pipex infile cmd1 cmd2 outfile", STDERR_FILENO);
	return (3);
}

int	command_error(char *str)
{
	ft_putstr_fd("zsh: command not found: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (4);
}

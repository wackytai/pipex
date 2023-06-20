/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:22:56 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/20 11:57:25 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	file_error(t_fd *fds)
{
	perror("Error");
	close(fds->infile);
	close(fds->outfile);
	exit(1);
}

int	args_error(void)
{
	ft_putendl_fd("usage: ./pipex infile cmd1 cmd2 outfile", STDERR_FILENO);
	exit(1);
}

int	command_error(char *str)
{
	char	*str1;

	str1 = ft_strjoin("Command not found: ", str);
	ft_putendl_fd(str1, STDERR_FILENO);
	free(str1);
	if (str[0] != 0)
		ft_printf("Please ask your administrator.\n");
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

void	close_and_wait(int pid, int pid1, t_fd *fds)
{
	close(fds->pipefd[0]);
	close(fds->pipefd[1]);
	close(fds->infile);
	close(fds->outfile);
	waitpid(pid, NULL, 0);
	waitpid(pid1, NULL, 0);
}

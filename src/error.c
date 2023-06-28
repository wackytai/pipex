/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:22:56 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/28 09:30:45 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	file_error(t_fd *fds)
{
	perror("Error");
	if (fds->infile >= 0)
		close(fds->infile);
	if (fds->outfile >= 0)
		close(fds->outfile);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
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

	str1 = ft_strjoin(str, ": command not found");
	ft_putendl_fd(str1, STDERR_FILENO);
	free(str1);
	return (4);
}

int	process_error(int flag, t_fd *fds)
{
	if (flag == 0)
		perror("Pipe failed");
	else
		perror("Fork failed");
	if (fds->infile >= 0)
		close(fds->infile);
	if (fds->outfile >= 0)
		close(fds->outfile);
	close(fds->fds[0]);
	close(fds->fds[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(1);
}

void	close_and_wait(int pid, int pid1, t_fd *fds)
{
	close(fds->pipefd[0]);
	close(fds->pipefd[1]);
	if (fds->infile >= 0)
		close(fds->infile);
	if (fds->outfile >= 0)
		close(fds->outfile);
	waitpid(pid, NULL, 0);
	waitpid(pid1, NULL, 0);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

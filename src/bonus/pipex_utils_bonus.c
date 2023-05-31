/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:36:34 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/31 15:16:08 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	free_pipes(int **array)
{
	int	i;

	i = -1;
	while (array[++i] != 0)
		free(array[i]);
	free(array);
}

int	create_process(char **argv, int nb, t_fd fds, char **envp)
{
	int		**pipefd;
	int		i;
	/* pid_t	pid;
	t_cmds	*cmds; */

	i = -1;
	pipefd = (int **)malloc(sizeof(int *) * (nb + 1));
	pipefd[nb] = 0;
	printf("checked:\nargv 0: %s\tfd in: %i\tenvp 0: %s\n", argv[2], fds.infile, envp[0]);
	while (++i < nb)
	{
		pipefd[i] = malloc(sizeof(int) * 2);
		if (pipe(pipefd[i]) < 0)
		{
			close(fds.infile);
			close(fds.outfile);
			free_pipes(pipefd);
			process_error(0);
		}
	}
	free_pipes(pipefd);
	return (0);
}

int	handle_child(t_fd fds, int pipefd[2], t_cmds *cmds, char **envp)
{
	dup2(fds.infile, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (cmds->cmd_path == 0)
		command_error(cmds->cmd_args[0], pipefd[1], 1);
	else
	{
		execve(cmds->cmd_path, cmds->cmd_args, envp);
		perror("execve failed: ");
	}
	return (0);
}

int	handle_parent(t_fd fds, int pipefd[2], t_cmds *cmds, char **envp)
{
	dup2(pipefd[0], STDIN_FILENO);
	dup2(fds.outfile, STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (cmds->cmd_path == 0)
		command_error(cmds->cmd_args[0], fds.outfile, -1);
	else
	{
		execve(cmds->cmd_path, cmds->cmd_args, envp);
		perror("execve failed: ");
	}
	return (0);
}

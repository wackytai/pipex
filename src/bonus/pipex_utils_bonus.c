/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:36:34 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/02 20:46:42 by tlemos-m         ###   ########.fr       */
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

int	create_process(char **argv, t_fd *fds, char **envp)
{
	pid_t	pid;
	int		i;

	i = -1;
	pid = 0;
	while (++i < fds->n_cmds - 1)
	{
		fds->cmd = argv[i + 2];
		pid = fork_processes(pid, fds);
		if (pid == 0)
			handle_child(fds, i, envp);
		/* else
			handle_parent(fds); */
		waitpid(pid, NULL, 0);
	}
	free_pipes(fds->pipefd);
	return (0);
}

int	handle_child(t_fd *fds, int i, char **envp)
{
	int		j;
	int		out;
	t_cmds	*cmds;

	j = -1;
	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (1);
	//get_cmd_fullname(&cmds, fds->paths, fds->cmd);
	out = update_pipe_ends(fds, i);
	while (++j < (fds->n_cmds - 1))
	{
		close(fds->pipefd[j][0]);
		close(fds->pipefd[j][1]);
		printf("#%i child: pipes %i closed\n", i, j);
	}
	/* if (cmds->cmd_path == 0)
		command_error(cmds, out, i, *fds); */
	printf("\tEXECV #%i: %s\n", out, envp[0]);
	/* execve(cmds->cmd_path, cmds->cmd_args, envp);
	perror("\texecve failed: "); */
	//free_array(cmds->cmd_args);
	free(cmds);
	return (0);
}

int	handle_parent(t_fd *fds)
{
	int	j;

	j = -1;
	while (++j < (fds->n_cmds - 1))
	{
		close(fds->pipefd[j][0]);
		close(fds->pipefd[j][1]);
	}
	close_files(*fds);
	return (0);
}

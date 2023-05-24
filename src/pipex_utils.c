/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:36:34 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/24 19:02:53 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

int	create_child(char **argv, char **paths, t_fd fds, char **envp)
{
	pid_t	pid;
	int		pipefd[2];
	t_cmds	*cmds;

	cmds = malloc(sizeof(t_cmds));
	get_cmd_fullname(fds, cmds, paths, argv[2]);
	if (pipe(pipefd) < 0)
		printf("Error: pipes failed\n");
	pid = fork();
	if (pid < 0)
		printf("Error: fork failed\n");
	if (pid == 0)
	{
		dup2(pipefd[0], fds.infile);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execve(cmds->cmd_path, cmds->cmd_args, envp);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	free_array(cmds->cmd_args);
	free(cmds);
	return (0);
}

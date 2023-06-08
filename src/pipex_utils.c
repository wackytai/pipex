/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:36:34 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/08 08:59:57 by tlemos-m         ###   ########.fr       */
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

int	create_process(char **argv, char **paths, t_fd fds, char **envp)
{
	pid_t	pid;
	int		pipefd[2];
	t_cmds	*cmds;

	if (pipe(pipefd) < 0)
		process_error(0);
	pid = fork();
	if (pid < 0)
		process_error(1);
	cmds = malloc(sizeof(t_cmds));
	get_cmd_fullname(&cmds, paths, argv[2]);
	if (pid == 0)
		handle_child(fds, pipefd, cmds, envp);
	else
	{
		free(cmds->cmd_path);
		free_array(cmds->cmd_args);
		get_cmd_fullname(&cmds, paths, argv[3]);
		handle_parent(fds, pipefd, cmds, envp);
		waitpid(pid, NULL, 0);
	}
	free_array(cmds->cmd_args);
	free(cmds->cmd_path);
	free(cmds);
	return (0);
}

int	handle_child(t_fd fds, int pipefd[2], t_cmds *cmds, char **envp)
{
	dup2(fds.infile, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (cmds->cmd_path != 0)
	{
		execve(cmds->cmd_path, cmds->cmd_args, envp);
		perror("execve failed: ");
	}
	return (0);
}

int	handle_parent(t_fd fds, int pipefd[2], t_cmds *cmds, char **envp)
{
	dup2(fds.outfile, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (cmds->cmd_path != 0)
	{
		execve(cmds->cmd_path, cmds->cmd_args, envp);
		perror("execve failed: ");
	}
	return (0);
}

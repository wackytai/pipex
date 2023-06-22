/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:03:30 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/22 10:51:13 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int		check_outfile(int argc, char **argv, t_fd *fds);

int	main(int argc, char **argv, char **envp)
{
	t_fd	fds;
	char	**paths;

	fds.outfile = -1;
	fds.infile = -1;
	fds.fds[0] = -1;
	fds.fds[1] = -1;
	if (argc < 5)
		return (args_error());
	check_infile(argv[1], &fds);
	if (check_outfile(argc, argv, &fds) == 0)
	{
		paths = get_paths(envp);
		create_process(argv, paths, &fds, envp);
	}
	if (fds.infile >= 0)
		close(fds.infile);
	if (fds.outfile >= 0)
		close(fds.outfile);
	if (paths)
		free_array(paths);
	return (0);
}

int	check_outfile(int argc, char **argv, t_fd *fds)
{
	if (!access(argv[argc - 1], W_OK) == 0 && access(argv[argc - 1], R_OK) == 0)
		return (file_error(fds));
	fds->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fds->outfile < 0)
		return (file_error(fds));
	else
		return (0);
}

int	check_infile(char *argv, t_fd *fds)
{
	if (access(argv, F_OK) != 0)
		return (file_error(fds));
	if (access(argv, R_OK) == 0)
		fds->infile = open(argv, O_RDONLY);
	else
		return (file_error(fds));
	return (0);
}

int	fork_process(t_fd *fds, char **paths, char *argv, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		process_error(1, fds);
	if (pid == 0)
	{
		update_pipes(fds, 1);
		handle_cmd(fds, paths, argv, envp);
	}
	return (pid);
}

int	dup_failed(t_fd *fds, char **paths)
{
	close(fds->infile);
	close(fds->outfile);
	close(fds->pipefd[0]);
	close(fds->pipefd[1]);
	free_array(paths);
	exit (1);
}

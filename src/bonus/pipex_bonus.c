/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:03:30 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/06 10:34:41 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_fd	fds;

	fds.paths = 0;
	fds.pipefd = 0;
	fds.ishdoc = 0;
	fds.outfile = 0;
	if (argc < 5)
		return (args_error());
	check_infile(argv[1], &fds);
	fds.n_cmds = argc - 3 - fds.ishdoc;
	if (check_outfile(argc, argv, &fds) != 0)
		return (file_error(fds));
	here_doc(&fds, argv[2]);
	/* create_pipes(&fds);
	fds.paths = get_paths(envp);
	create_process(argv, &fds, envp); */
	if (fds.paths != 0)
		free_array(fds.paths);
	close_files(fds);
	return (0);
}

int	check_outfile(int argc, char **argv, t_fd *fds)
{
	if (!access(argv[argc - 1], W_OK) && access(argv[argc - 1], R_OK))
		return (file_error(*fds));
	if (fds->ishdoc != 0)
		fds->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		fds->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fds->outfile < 0)
		return (file_error(*fds));
	else
		return (0);
}

int	check_infile(char *argv, t_fd *fds)
{
	if (ft_strncmp(argv, "here_doc", ft_strlen(argv)) == 0)
	{
		fds->ishdoc = 1;
		fds->infile = open(argv, O_RDWR | O_CREAT | O_APPEND, 0644);
		return (0);
	}
	if (access(argv, F_OK | R_OK) != 0)
		perror("Error");
	fds->infile = open(argv, O_RDONLY);
	return (0);
}

int	create_process(char **argv, t_fd *fds, char **envp)
{
	pid_t	pid;
	int		i;

	i = -1;
	pid = 0;
	while (++i < fds->n_cmds)
	{
		if (fds->infile < 0)
			continue ;
		fds->cmd = argv[i + 2 + fds->ishdoc];
		pid = fork_processes(pid, fds);
		if (pid == 0)
			handle_child(fds, i, envp);
	}
	close_pipes(fds);
	free_pipes(fds->pipefd);
	return (0);
}

int	here_doc(t_fd *fds, char *limiter)
{
	int		fd[2];
	int		pid;
	char	*line;

	if (pipe(fd) != 0)
		process_error(0);
	pid = fork();
	if (pid < 0)
		process_error(1);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fds->infile, STDOUT_FILENO);
		while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
			line = get_next_line(STDIN_FILENO);
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	else
	{
		close(fd[1]);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
	return (0);
}

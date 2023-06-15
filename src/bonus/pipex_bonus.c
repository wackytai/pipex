/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:03:30 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/15 16:31:20 by tlemos-m         ###   ########.fr       */
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
	if (argc < 5 || (argc == 5
			&& !ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1]))))
		return (args_error());
	check_infile(argv, &fds);
	fds.n_cmds = argc - 3 - fds.ishdoc;
	if (check_outfile(argc, argv, &fds) != 0)
		return (file_error(fds));
	create_pipes(&fds);
	fds.paths = get_paths(envp);
	create_process(argv, &fds, envp);
	if (fds.paths != 0)
		free_all(fds.paths, 0, 0);
	close_files(fds, fds.n_cmds);
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

int	check_infile(char **argv, t_fd *fds)
{
	int	fd_hd;

	fd_hd = 0;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		fds->ishdoc = 1;
		fd_hd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
		here_doc(fd_hd, argv[2]);
		close(fd_hd);
	}
	if (access(argv[1], F_OK | R_OK) != 0)
		perror("Error");
	fds->infile = open(argv[1], O_RDONLY);
	return (0);
}

int	create_process(char **argv, t_fd *fds, char **envp)
{
	int		i;

	i = -1;
	init_pid(fds);
	while (++i < fds->n_cmds)
	{
		fds->cmd = argv[i + 2 + fds->ishdoc];
		if (fds->infile < 0 || fds->cmd == 0)
			continue ;
		fds->pid[i] = fork_processes(fds->pid[i], fds);
		if (!fds->pid[i])
			handle_child(fds, i, envp);
	}
	i = -1;
	while (++i < fds->n_cmds)
		waitpid(fds->pid[i], NULL, 0);
	close_pipes(fds);
	free_all(0, fds->pipefd, fds->pid);
	return (0);
}

int	here_doc(int fd, char *limiter)
{
	char	*line;

	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line || (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
				&& line[ft_strlen(limiter)] == '\n'))
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	return (0);
}

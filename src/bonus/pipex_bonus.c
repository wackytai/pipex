/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:03:30 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/05 10:46:12 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_fd	fds;

	fds.paths = 0;
	fds.pipefd = 0;
	fds.outfile = 0;
	fds.n_cmds = argc - 3;
	if (argc < 5)
		return (args_error());
	check_infile(argv[1], &fds);
	if (check_outfile(argc, argv, &fds) != 0)
		return (file_error(fds));
	create_pipes(&fds);
	fds.paths = get_paths(envp);
	create_process(argv, &fds, envp);
	if (fds.paths != 0)
		free_array(fds.paths);
	close_files(fds);
	return (0);
}

int	check_outfile(int argc, char **argv, t_fd *fds)
{
	if (access(argv[argc - 1], W_OK) && access(argv[argc - 1], R_OK))
		return (file_error(*fds));
	fds->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fds->outfile < 0)
		return (file_error(*fds));
	else
		return (0);
}

int	check_infile(char *argv, t_fd *fds)
{
	if (access(argv, F_OK | R_OK) != 0)
		perror("Error");
	fds->infile = open(argv, O_RDONLY);
	return (0);
}

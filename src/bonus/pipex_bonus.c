/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:03:30 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/26 13:49:39 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

int		check_outfile(int argc, char **argv, t_fd *fds);

int	main(int argc, char **argv, char **envp)
{
	t_fd	fds;
	char	**paths;

	fds.outfile = argc;
	if (argc >= 5)
	{
		check_infile(argv[1], &fds);
		if (check_outfile(argc, argv, &fds) == 0)
		{
			paths = get_paths(envp);
			create_process(argv, paths, fds, envp);
		}
		else
			return (2);
	}
	else
		return (args_error());
	close(fds.infile);
	close(fds.outfile);
	if (paths)
		free_array(paths);
	return (0);
}

int	check_outfile(int argc, char **argv, t_fd *fds)
{
	if (!access(argv[argc - 1], W_OK) == 0 && access(argv[argc - 1], R_OK) == 0)
		return (file_error(argv[argc - 1], *fds));
	fds->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fds->outfile < 0)
		return (permission_error(argv[argc - 1], *fds));
	else
		return (0);
}

int	check_infile(char *argv, t_fd *fds)
{
	if (access(argv, F_OK) != 0)
		return (file_error(argv, *fds));
	if (access(argv, R_OK) == 0)
		fds->infile = open(argv, O_RDONLY);
	else
		return (permission_error(argv, *fds));
	return (0);
}

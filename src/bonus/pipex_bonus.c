/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:03:30 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/31 15:40:32 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_fd	fds;

	fds.outfile = 0;
	if (argc >= 5)
	{
		check_infile(argv[1], &fds);
		if (check_outfile(argc, argv, &fds) == 0)
			create_process(argv, (argc - 4), fds, envp);
		else
			return (file_error(fds));
	}
	else
		return (args_error());
	close(fds.infile);
	close(fds.outfile);
	return (0);
}

int	check_outfile(int argc, char **argv, t_fd *fds)
{
	if (!access(argv[argc - 1], W_OK) == 0 && access(argv[argc - 1], R_OK) == 0)
		return (file_error(*fds));
	fds->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fds->outfile < 0)
		return (file_error(*fds));
	else
		return (0);
}

int	check_infile(char *argv, t_fd *fds)
{
	if (access(argv, F_OK) != 0)
		return (file_error(*fds));
	if (access(argv, R_OK) == 0)
		fds->infile = open(argv, O_RDONLY);
	else
		return (file_error(*fds));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:03:30 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/10 15:12:05 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv)
{
	t_fd	fds;

	if (argc >= 5)
	{
		printf("N args: OK\n");
		if (access(argv[1], R_OK) == 0)
		{
			printf("infile access: OK\n");
			fds.infile = open(argv[1], O_RDONLY);
			printf("infile fd: %i\n", fds.infile);
		}
		else
			printf("infile access: KO\n");
		if (!check_outfile(argc, argv, fds))
			return (0);
	}
	else
	{
		printf("number of arguments is wrong\n");
		return (0);
	}
	return (0);
}

int	check_outfile(int argc, char **argv, t_fd fds)
{
	if (access(argv[argc - 1], W_OK) == 0 && access(argv[argc - 1], R_OK) == 0)
		printf("outfile access: OK\n");
	else
		printf("outfile access: KO\n");
	fds.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	printf("outfile fds: %i\n", fds.outfile);
	if (fds.outfile < 0)
		return (1);
	else
		return (0);
}

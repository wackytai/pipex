/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:03:30 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/10 14:34:27 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int argc, char **argv)
{
	t_fd	fds;

	if (argc >= 5 && argv)
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
		if (access(argv[argc - 1], W_OK) == 0)
			printf("outfile access: OK\n");
		else
			printf("outfile access: KO\n");
	}
	else
	{
		printf("number of arguments is wrong\n");
		return (0);
	}
	return (0);
}

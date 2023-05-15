/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:03:30 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/15 20:32:32 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int		check_outfile(int argc, char **argv, t_fd fds);
char	*get_paths(char **argv, char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_fd	fds;
	char	*paths;

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
			printf("infile access: KO, go to next pipe\n");
		if (check_outfile(argc, argv, fds) == 0)
		{
			printf("outfile: OK\n");
			paths = get_paths(argv, envp);
			if (paths != NULL)
				printf("cmd found\n");
		}
		else
		{
			printf("outfile access: KO, exit program\n");
			return (2);
		}
	}
	else
	{
		printf("number of arguments is wrong\n");
		return (1);
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

char	*get_paths(char **argv, char **envp)
{
	char	**path;
	int		i;
	int		j;

	i = -1;
	while (envp[++i] != NULL && argv)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
	}
	path = ft_split(envp[i] + 5, ':');
	j = -1;
	while (path[++j] != NULL)
		printf("path: %s\n", path[j]);
	while (i >= 0)
	{
		free(path[i]);
		i--;
	}
	free(path);
	return (NULL);
}

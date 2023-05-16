/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:03:30 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/16 14:55:10 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int		check_outfile(int argc, char **argv, t_fd fds);
char	**get_paths(char **envp);
char	*check_command(char **paths, char *cmd);
void	get_cmd_fullname(t_cmds *cmds, char **paths, char **argv);

int	main(int argc, char **argv, char **envp)
{
	t_fd	fds;
	t_cmds	*cmds;
	char	**paths;

	cmds = malloc(sizeof(t_cmds));
	if (argc >= 5)
	{
		cmds->n = argc - 3;
		if (access(argv[1], R_OK) == 0)
		{
			fds.infile = open(argv[1], O_RDONLY);
			printf("infile fd: %i\n", fds.infile);
		}
		else if (access(argv[1], F_OK) != 0)
			printf("zsh: no such file or directory: %s\n", argv[1]);
		else
			printf("zsh: permission denied: %s\n", argv[1]);
		if (check_outfile(argc, argv, fds) == 0)
		{
			paths = get_paths(envp);
			get_cmd_fullname(cmds, paths, argv);
		}
		else
		{
			printf("outfile access: KO, exit program\n");
			return (2);
		}
	}
	else
	{
		printf("number of arguments is wrong: %i\n", argc);
		return (1);
	}
	free_array(paths);
	free(cmds);
	return (0);
}

int	check_outfile(int argc, char **argv, t_fd fds)
{
	if (access(argv[argc - 1], W_OK) == 0 && access(argv[argc - 1], R_OK) == 0)
		printf("outfile access: OK\n");
	else
		printf("no outfile or no access\n");
	fds.outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	printf("outfile fds: %i\n", fds.outfile);
	if (fds.outfile < 0)
		return (1);
	else
		return (0);
}

char	**get_paths(char **envp)
{
	char	**path;
	char	*temp;
	int		i;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
	}
	path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (path[++i])
	{
		temp = path[i];
		path[i] = ft_strjoin(temp, "/");
		free(temp);
	}
	return (path);
}

char	*check_command(char **paths, char *cmd)
{
	int		i;
	char	*test;
	int		flag;

	i = -1;
	flag = 1;
	while (paths[++i])
	{
		test = ft_strjoin(paths[i], cmd);
		if (access(test, F_OK & X_OK) == 0)
		{
			flag = 0;
			break ;
		}
		free(test);
	}
	if (flag == 1)
		return (0);
	return (test);
}

void	get_cmd_fullname(t_cmds *cmds, char **paths, char **argv)
{
	int		i;
	char	*test;

	i = -1;
	while (++i < cmds->n)
	{
		test = check_command(paths, argv[i + 2]);
		if (test == 0)
			printf("zsh: command not found: %s\n", argv[i + 2]);
		else
			printf("cmd %i path: %s\n", (i + 1), test);
		free(test);
	}
	return ;
}

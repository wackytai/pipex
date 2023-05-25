/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:03:30 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/25 14:01:12 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int		check_outfile(int argc, char **argv, t_fd *fds);
char	**get_paths(char **envp);
char	*check_command(char **paths, char *cmd);
void	get_cmd_fullname(t_cmds **cmds, char **paths, char *argv);

int	main(int argc, char **argv, char **envp)
{
	t_fd	fds;
	char	**paths;

	fds.outfile = argc;
	if (argc >= 5)
	{
		if (access(argv[1], R_OK) == 0)
			fds.infile = open(argv[1], O_RDONLY);
		else if (access(argv[1], F_OK) != 0)
			return (file_error(argv[1]));
		else
			return (permission_error(argv[1]));
		if (check_outfile(argc, argv, &fds) == 0)
		{
			paths = get_paths(envp);
			create_child(argv, paths, fds, envp);
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
		return (file_error(argv[argc - 1]));
	fds->outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fds->outfile < 0)
		return (permission_error(argv[argc - 1]));
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

void	get_cmd_fullname(t_cmds **cmds, char **paths, char *argv)
{
	char	*test;

	(*cmds)->cmd_args = ft_split(argv, ' ');
	/* while ((*cmds)->cmd_args[++i] != NULL)
		ft_putendl_fd((*cmds)->cmd_args[i], 1); */
	test = check_command(paths, (*cmds)->cmd_args[0]);
	if (test == 0)
		command_error(argv);
	else
	{
		(*cmds)->cmd_path = test;
		return ;
	}
	free(test);
	return ;
}

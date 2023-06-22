/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:44:30 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/22 10:08:28 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

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
	if (!path)
		ft_putendl_fd("Malloc error 1", STDERR_FILENO);
	i = -1;
	while (path[++i])
	{
		temp = path[i];
		path[i] = ft_strjoin(temp, "/");
		if (!path[i])
			ft_putendl_fd("Malloc error 2", STDERR_FILENO);
		free(temp);
	}
	return (path);
}

char	*check_command(char **paths, char *cmd)
{
	int		i;
	char	*test;

	i = -1;
	while (paths[++i])
	{
		test = ft_strjoin(paths[i], cmd);
		if (access(test, F_OK & X_OK) == 0)
			return (test);
		free(test);
	}
	if (!test && cmd[0] != 0)
		ft_putendl_fd("Malloc error 3", STDERR_FILENO);
	return (0);
}

void	get_cmd_fullname(t_cmds **cmds, char **paths, char *argv)
{
	char	*test;

	(*cmds)->cmd_args = ft_split(argv, ' ');
	test = check_command(paths, (*cmds)->cmd_args[0]);
	if (test != 0 && (*cmds)->cmd_args[0] != 0)
	{
		(*cmds)->cmd_path = test;
		return ;
	}
	free(test);
	(*cmds)->cmd_path = 0;
	command_error(argv);
	return ;
}

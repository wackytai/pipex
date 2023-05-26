/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:44:30 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/26 09:45:00 by tlemos-m         ###   ########.fr       */
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

void	get_cmd_fullname(t_cmds **cmds, char **paths, char *argv, int flag)
{
	char	*test;

	(*cmds)->cmd_args = ft_split(argv, ' ');
	test = check_command(paths, (*cmds)->cmd_args[0]);
	if (test == 0)
		command_error(argv, flag);
	else
	{
		(*cmds)->cmd_path = test;
		return ;
	}
	free(test);
	return ;
}
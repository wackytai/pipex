/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:44:30 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/19 12:00:55 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex_bonus.h"

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

	i = -1;
	while (paths[++i])
	{
		test = ft_strjoin(paths[i], cmd);
		if (access(test, F_OK & X_OK) == 0)
			return (test);
		free(test);
	}
	return (0);
}

void	get_cmd_fullname(t_cmds *cmds, t_fd *fds, char *argv, int i)
{
	char	*test;

	cmds->cmd_args = ft_split(argv, ' ');
	test = check_command(fds->paths, cmds->cmd_args[0]);
	if (test != 0 && fds->cmd[0] != 0)
	{
		cmds->cmd_path = test;
		return ;
	}
	free(test);
	cmds->cmd_path = 0;
	command_error(cmds, argv, (i - fds->ishdoc), fds);
	return ;
}

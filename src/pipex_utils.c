/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:36:34 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/22 13:47:05 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

int	create_child(char **argv, char **paths, t_cmds cmds, int n_args)
{
	int	i;
	int	*pid;

	i = -1;
	pid = malloc(sizeof(int) * n_args);
	while (++i < n_args && paths && cmds.cmd_path && argv)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			printf("Error forking\n");
	}
	free(pid);
	return (0);
}

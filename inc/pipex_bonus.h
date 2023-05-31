/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:07:14 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/31 12:45:21 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft_gnl/libft.h"

typedef struct s_cmds
{
	char	*cmd_path;
	char	**cmd_args;
}			t_cmds;

typedef struct s_fd
{
	int	infile;
	int	outfile;
}	t_fd;

/* main.c */
int		main(int argc, char **argv, char **envp);
int		check_outfile(int argc, char **argv, t_fd *fds);
int		check_infile(char *argv, t_fd *fds);

/* commands.c */
char	**get_paths(char **envp);
char	*check_command(char **paths, char *cmd);
void	get_cmd_fullname(t_cmds **cmds, char **paths, char *argv);

/* pipex_utils.c */
void	free_array(char **array);
int		create_process(char **argv, char **paths, t_fd fds, char **envp);
int		handle_child(t_fd fds, int pipefd[2], t_cmds *cmds, char **envp);
int		handle_parent(t_fd fds, int pipefd[2], t_cmds *cmds, char **envp);

/* error.c */
int		file_error(t_fd fds);
int		args_error(void);
int		command_error(char *str, int out, int flag);
int		process_error(int flag);

#endif
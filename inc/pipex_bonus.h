/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:07:14 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/06/06 10:08:11 by tlemos-m         ###   ########.fr       */
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
	int		infile;
	int		outfile;
	int		ishdoc;
	int		n_cmds;
	int		**pipefd;
	char	**paths;
	char	*cmd;
}	t_fd;

/* pipex_bonus.c */
int		main(int argc, char **argv, char **envp);
int		check_outfile(int argc, char **argv, t_fd *fds);
int		check_infile(char *argv, t_fd *fds);
int		create_process(char **argv, t_fd *fds, char **envp);
int		here_doc(t_fd *fds, char *limiter);

/* commands_bonus.c */
char	**get_paths(char **envp);
char	*check_command(char **paths, char *cmd);
void	get_cmd_fullname(t_cmds *cmds, t_fd *fds, char *argv, int i);

/* pipex_utils_bonus.c */
void	free_array(char **array);
void	free_pipes(int **array);
void	close_pipes(t_fd *fds);
int		handle_child(t_fd *fds, int i, char **envp);

/* process_utils_bonus.c */
void	create_pipes(t_fd *fds);
pid_t	fork_processes(int pid, t_fd *fds);
int		update_pipe_ends(t_fd *fds, int i);

/* error_bonus.c */
int		file_error(t_fd fds);
int		args_error(void);
int		command_error(t_cmds *cmd, int out, int flag, t_fd fds);
int		process_error(int flag);
void	close_files(t_fd fds);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:07:14 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/15 19:19:39 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft_gnl/libft.h"

typedef struct s_fd
{
	int	infile;
	int	outfile;
}	t_fd;

/* main.c */
int		main(int argc, char **argv, char **envp);
int		check_outfile(int argc, char **argv, t_fd fds);
char	*get_paths(char **argv, char **envp);

#endif
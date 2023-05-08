/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:03:30 by tlemos-m          #+#    #+#             */
/*   Updated: 2023/05/08 16:09:56 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(void)
{
	int		child_pid;
	char	*av[];

	child_pid = fork();
	if (child_pid == 0)
	{
		av[] = {
			"/bin/echo",
			"h_e_l_l_o_ _w_o_r_l_d",
			NULL,
		};
		if (execv(av[0], av) == -1)
		{
			perror("execv: ");
		}
		exit(1);
	}
	return (0);
}

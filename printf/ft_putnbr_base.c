/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemos-m <tlemos-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:06:06 by tlemos-m          #+#    #+#             */
/*   Updated: 2022/11/23 11:17:24 by tlemos-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(long long n, char *base, int b)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
		i = 1;
	}
	if (n / b > 0)
		i += ft_putnbr_base(n / b, base, b);
	ft_putchar(base[n % b]);
	i++;
	return (i);
}

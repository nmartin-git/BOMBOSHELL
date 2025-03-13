/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:50:28 by nmartin           #+#    #+#             */
/*   Updated: 2025/02/05 15:05:48 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	check_sign(long nb, int fd)
{
	if (nb < 0)
	{
		nb = -nb;
		ft_putchar_fd('-', fd);
	}
	return (nb);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = (long)n;
	nb = check_sign(nb, fd);
	if (nb / 10 > 0)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd(nb % 10 + '0', fd);
		nb /= 10;
	}
	else
		ft_putchar_fd(nb % 10 + '0', fd);
}

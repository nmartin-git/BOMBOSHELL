/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:37:32 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/04 22:42:41 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			i++;
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **av, t_shell *shell)
{
	long long	exit_status;

	exit_status = 0;
	write(1, "exit\n", 5);
	if (!av[1])
		exit(exit_status);
	if (!ft_is_number(av[1]))
	{
		printf("exit: %s: numeric argument required\n", av[1]);
		shell->last_exit_status = 2;
	}
	if (av[2])
	{
		ft_printf("exit: Too many arguments");
		shell->last_exit_status = 1;
		return (1);
	}
	exit_status = ft_atoi(av[1]);
	while (exit_status > 256)
		exit_status %= 256;
	shell->last_exit_status = exit_status;
	exit(exit_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:37:32 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/16 23:07:50 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bomboshell.h"
#include "builtins.h"

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

int	ft_exit(t_shell *cmd)
{
	long long	exit_status;

	exit_status = 0;
	if (!cmd->command[1])
		exit(g_exit_status); // TODO fix les leaks avant d'exit
	if (!ft_is_number(cmd->command[1]))
	{
		ft_printf_fd(2, "bomboshell: exit: %s: numeric argument required\n",
			cmd->command[1]);
		g_exit_status = 2;
	}
	if (cmd->command[2])
	{
		ft_printf("bomboshell: exit: Too many arguments");
		g_exit_status = 1;
		return (1);
	}
	exit_status = ft_atoi(cmd->command[1]);
	while (exit_status > 256)
		exit_status %= 256;
	ft_printf_fd(2, "exit %i\n", exit_status);
	g_exit_status = exit_status;
	exit(g_exit_status);
}

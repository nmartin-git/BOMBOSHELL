/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:37:32 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/18 19:17:55 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		exit(g_exit_status);
	}
	if (cmd->command[2])
	{
		g_exit_status = 1;
		ft_printf_fd(2, " too many arguments");
		return (1);
	}
	exit_status = ft_atoi(cmd->command[1]);
	while (exit_status > 256)
		exit_status %= 256;
	ft_printf_fd(1, "exit\n");
	g_exit_status = exit_status;
	free_t_shell(cmd);
	exit(g_exit_status);
}

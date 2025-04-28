/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:37:32 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/27 14:10:36 by nmartin          ###   ########.fr       */
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

static int	is_overflow(const char *arg, long value)
{
	if (ft_strlen(arg) > 20)
		return (1);
	if (value == LONG_MAX && arg[0] != '-')
		return (1);
	if (value == LONG_MIN && arg[0] == '-')
		return (1);
	return (0);
}

static void	exit_numeric_error(char *arg)
{
	ft_printf_fd(2, "bomboshell: exit: %s: numeric argument required\n", arg);
	exit(2);
}

static int	too_many_args(char **args)
{
	if (args[2])
	{
		ft_printf_fd(2, "bomboshell: exit: too many arguments\n");
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

int	ft_exit(t_shell *cmd, t_env *env)
{
	long	exit_status;
	char	*arg;

	ft_printf_fd(1, "exit\n");
	free_env(env);
	arg = cmd->command[1];
	if (!arg)
	{
		free_t_shell(cmd);
		exit(g_exit_status);
	}
	if (!ft_is_number(arg))
		exit_numeric_error(arg);
	exit_status = ft_atol(arg);
	if (is_overflow(arg, exit_status))
		exit_numeric_error(arg);
	if (too_many_args(cmd->command))
		return (1);
	g_exit_status = (unsigned char)exit_status;
	free_t_shell(cmd);
	exit(g_exit_status);
}

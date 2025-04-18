/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:17:52 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/14 19:01:50 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*expand_var(t_shell *shell, char *arg)
{
	char	*var_name;
	char	*var_value;

	if (arg[0] != '$')
		return (ft_strdup(arg));
	if (arg[1] == '?' )
		return (ft_itoa(shell->last_exit_status));
	var_name = arg + 1;
	var_value = get_env_value(shell->env_vars, var_name);
	if (!var_value)
		return (ft_strdup(""));
	return (ft_strdup(var_value));
}

int	ft_echo(t_shell *cmd)
{
	int	i;
	int	flag;
	int	j;

	if (!cmd->command[1])
	{
		printf("\n");
		return (1);
	}
	flag = 1;
	i = 1;
	j = 1;
	while (cmd->command[i]
		&& cmd->command[i][0] == '-' && cmd->command[i][1] == 'n')
	{
		while (cmd->command[i][j] == 'n')
			j++;
		if (cmd->command[i++][j] != '\0')
			break ;
		flag = 0;
	}
	print_echo(cmd->command, i, cmd);
	if (flag)
		printf("\n");
	return (0);
}

void	print_echo(char **av, int i, t_shell *shell)
{
	char	*expanded_arg;

	while (av[i])
	{
		expanded_arg = expand_var(shell, av[i]);
		printf("%s", expanded_arg);
		free(expanded_arg);
		if (av[i + 1])
			printf(" ");
		i++;
	}
}

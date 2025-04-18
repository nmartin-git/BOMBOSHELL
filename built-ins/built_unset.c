/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:36:18 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/14 19:00:58 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*handle_shell_var(t_env *env, char *var, char *cmd)
{
	char	*value;

	if (!var || !*var)
	{
		printf("%s: '': not a valid identifier\n", cmd);
		return (NULL);
	}
	if (var[0] == '$' && var[1])
	{
		value = get_env_value(env, var + 1);
		if (!value)
		{
			printf("%s: '%s': not a valid identifier\n", cmd, var);
			return (NULL);
		}
		if (!is_valid_identifier(value))
		{
			printf("%s: '%s': not a valid identifier\n", cmd, value);
			return (NULL);
		}
		return (ft_strdup(value));
	}
	if (!is_valid_identifier(var))
	{
		printf("%s: '%s': not a valid identifier\n", cmd, var);
		return (NULL);
	}
	return (ft_strdup(var));
}

int	ft_unset(t_shell *cmd)
{
	int	i;

	if (!cmd->env_vars)
		return (0);
	i = 1;
	while (cmd->command[i])
	{
		unset_env_value(cmd->env_vars, cmd->command[i]);
		i++;
	}
	return (0);
}

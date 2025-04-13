/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:36:18 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/06 18:20:54 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	unset_env_value(t_env *env, char *key)
{
	t_env	*current;
	t_env	*prev;
	char	*expanded_key;

	expanded_key = handle_shell_var(env, key, "unset");
	if (!expanded_key)
		return (0);
	prev = NULL;
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, expanded_key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				env = current->next;
			if (current->value)
				free(current->value);
			return (free(current->key), free(current), free(expanded_key), 1);
		}
		prev = current;
		current = current->next;
	}
	return (free(expanded_key), 1);
}

char	*handle_shell_var(t_env *env, char *var, char *cmd)
{
	char	*value;

	value = NULL;
	if (!var || !*var)
		return (print_invalid_id_error(cmd, NULL), NULL);
	if (var[0] == '$' && var[1])
	{
		value = get_env_value(env, var + 1);
		if (!is_valid_identifier(value) || !value)
			return (print_invalid_id_error(cmd, value), NULL);
		return (ft_strdup(value));
	}
	if (!is_valid_identifier(var))
		return (print_invalid_id_error(cmd, value), NULL);
	return (ft_strdup(var));
}

int	ft_unset(t_shell *cmd)
{
	int	i;

	if (!cmd->env_vars)
		return (1);
	i = 1;
	while (cmd->command[i])
	{
		if (!unset_env_value(cmd->env_vars, cmd->command[i]))
			return (1);
		i++;
	}
	return (0);
}

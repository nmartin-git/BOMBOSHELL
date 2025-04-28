/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:36:18 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/18 19:48:11 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

void	unset_env_value(t_env *env, char *key)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				env = current->next;
			if (current->value)
				free(current->value);
			return (free(current->key), free(current));
		}
		prev = current;
		current = current->next;
	}
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

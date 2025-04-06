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

void	unset_env_value(t_env *env, char *key)
{
	t_env	*current;
	t_env	*prev;
	char	*expanded_key;

	expanded_key = handle_shell_var(env, key, "unset");
	if (!expanded_key)
		return ;
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
			return (free(current->key), free(current), free(expanded_key));
		}
		prev = current;
		current = current->next;
	}
	free(expanded_key);
}

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
	int		i;

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
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

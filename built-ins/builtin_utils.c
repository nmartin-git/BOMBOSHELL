/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 00:36:18 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/14 19:01:27 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->key = ft_strdup(key);
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = NULL;
	env->next = NULL;
	return (env);
}

void	add_env(t_env **env_list, t_env *new)
{
	t_env	*current;

	if (!*env_list)
	{
		*env_list = new;
		return ;
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	free_env(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next;
		free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

char	*get_env_value(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	set_env_value(t_env *env, char *key, char *value)
{
	t_env	*current;
	t_env	**head;

	head = &env;
	current = env;
	while (current)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(key) + 1))
		{
			if (current->value)
				free(current->value);
			if (value)
				current->value = ft_strdup(value);
			else
				current->value = NULL;
			return ;
		}
		current = current->next;
	}
	add_env(head, new_env(key, value));
}

int	print_invalid_id_error(char *arg, char *var)
{
	if (!var)
		printf("export: '%s': not a valid identifier\n", arg);
	else
		printf("%s: '%s': not a valid identifier\n", arg, var);
	return (1);
}

char	*trim_quotes(char *value)
{
	size_t	len;
	char	*new_value;

	len = ft_strlen(value);
	if (len >= 2 && ((value[0] == '"' && value[len - 1] == '"')
			|| (value[0] == '\'' && value[len - 1] == '\'')))
	{
		new_value = ft_substr(value, 1, len - 2);
		return (new_value);
	}
	else if ((value[0] == '"' || value[0] == '\'') && value[len
			- 1] != value[0])
		return (NULL);
	return (ft_strdup(value));
}

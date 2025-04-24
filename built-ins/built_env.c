/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:39:25 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/14 19:02:01 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_env *list)
{
	t_env	*current;

	if (!list)
		return (1);
	current = list;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}

static int	split_env_line(char *env_line, char **key, char **value)
{
	int	j;

	j = 0;
	while (env_line[j] && env_line[j] != '=')
		j++;
	*key = ft_substr(env_line, 0, j);
	if (!*key)
		return (0);
	if (env_line[j] == '=')
		*value = ft_strdup(env_line + j + 1);
	else
		*value = NULL;
	return (1);
}

static int	add_env_entry(t_env **env_list, char *key, char *value)
{
	t_env	*new;

	new = new_env(key, value);
	if (!new)
	{
		free(key);
		if (value)
			free(value);
		return (0);
	}
	add_env(env_list, new);
	free(key);
	if (value)
		free(value);
	return (1);
}

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	char	*key;
	char	*value;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		if (!split_env_line(envp[i], &key, &value))
			return (NULL);
		if (!add_env_entry(&env_list, key, value))
			return (NULL);
		i++;
	}
	return (env_list);
}

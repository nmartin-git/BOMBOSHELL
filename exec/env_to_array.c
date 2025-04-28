/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:10:01 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/26 22:15:14 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_env_var(char *arg, t_env *env, int *y)
{
	char	*var_name;
	char	*var_value;

	while (ft_isalnum(arg[*y]) || arg[*y] == '_')
		*y += 1;
	var_name = ft_strndup(arg, *y);
	var_value = ft_strdup(get_env_value(env, var_name));
	free(var_name);
	if (!var_value)
	{
		var_value = ft_strdup("");
		g_exit_status = 0;
	}
	return (var_value);
}

int	count_valid_env_entries(t_env *env_list)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env_list;
	while (current)
	{
		if (current->value)
			count++;
		current = current->next;
	}
	return (count);
}

char	*create_env_string(char *key, char *value)
{
	int		count;
	char	*env_str;

	count = ft_strlen(key) + ft_strlen(value) + 2;
	env_str = (char *)malloc(sizeof(char) * count);
	if (!env_str)
		return (NULL);
	ft_strlcpy(env_str, key, ft_strlen(key) + 1);
	ft_strlcat(env_str, "=", ft_strlen(env_str) + 2);
	ft_strlcat(env_str, value, ft_strlen(env_str) + ft_strlen(value) + 1);
	return (env_str);
}

void	free_env_array(char **env_array, int count)
{
	while (--count >= 0)
		free(env_array[count]);
	free(env_array);
}

char	**env_to_array(t_env *env_list)
{
	int		count;
	t_env	*current;
	char	**env_array;
	int		i;

	count = count_valid_env_entries(env_list);
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		if (current->value)
		{
			env_array[i] = create_env_string(current->key, current->value);
			if (!env_array[i])
				return (free_env_array(env_array, i), NULL);
			i++;
		}
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:39:25 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/06 18:18:05 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

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

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	t_env	*new;
	char	**split;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i])
	{
		split = ft_split(envp[i], '=');
		if (!split)
			return (NULL);
		new = new_env(split[0], split[1]);
		if (!new)
		{
			ft_free_tab(split);
			return (NULL);
		}
		add_env(&env_list, new);
		ft_free_tab(split);
		i++;
	}
	return (env_list);
}

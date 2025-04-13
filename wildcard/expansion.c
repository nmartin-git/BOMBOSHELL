/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atazzit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:31:30 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/11 18:00:48 by atazzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

t_wildcard	*expand_wildcards(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_wildcard		*matches;
	int				i;

	matches = NULL;
	i = 0;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
			continue ;
		if (match_pattern(pattern, entry->d_name))
		{
			list_add_back(&matches, entry->d_name);
			i++;
		}
	}
	closedir(dir);
	if (i == 0)
		list_add_back(&matches, pattern);
	return (matches);
}

char	**expand_args_wildcards(char **args)
{
	int			i;
	t_wildcard	*expanded;
	char		**res;

	i = 0;
	expanded = NULL;
	if (!args)
		return (NULL);
	while (args[i])
	{
		if (has_wildcards(args[i]))
			find_matches(&args[i], expanded, i);
		else
			list_add_back(&expanded, args[i]);
		i++;
	}
	res = list_to_array(expanded);
	list_free(expanded);
	return (res);
}

void	find_matches(char **args, t_wildcard *expanded, int i)
{
	t_wildcard	*current;
	t_wildcard	*matches;

	matches = expand_wildcards(args[i]);
	current = matches;
	while (current)
	{
		list_add_back(&expanded, current->content);
		current = current->next;
	}
	list_free(matches);
}

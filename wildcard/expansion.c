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

static void	handle_dir_entry(DIR *dir, t_wildcard_list **matches, char *pattern,
		int *i)
{
	struct dirent	*entry;
	char			*path;

	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (match_pattern(pattern, entry->d_name))
		{
			path = ft_strjoin(" ", entry->d_name);
			list_add_back_wildcard(matches, path);
			free(path);
			(*i)++;
		}
		entry = readdir(dir);
	}
}

t_wildcard_list	*expand_wildcards(char *pattern)
{
	DIR				*dir;
	t_wildcard_list	*matches;
	int				i;

	dir = opendir(".");
	matches = NULL;
	i = 0;
	if (!dir)
		return (NULL);
	handle_dir_entry(dir, &matches, pattern, &i);
	closedir(dir);
	sort_wildcards(&matches);
	if (i == 0)
		list_add_back_wildcard(&matches, pattern);
	return (matches);
}

char	**expand_args_wildcards(char **args)
{
	int				i;
	t_wildcard_list	*expanded;
	char			**res;

	i = 0;
	expanded = NULL;
	if (!args)
		return (NULL);
	while (args[i])
	{
		if (has_wildcards(args[i]))
			find_matches(&args[i], &expanded, i);
		else
			list_add_back_wildcard(&expanded, args[i]);
		i++;
	}
	res = list_to_array(expanded);
	list_free_wildcard(expanded);
	return (res);
}

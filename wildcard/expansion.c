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

t_wildcard_list	*expand_wildcards(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_wildcard_list	*matches;
	char			*full_path;
	int				i;

	dir = opendir(".");
	matches = NULL;
	i = 0;
	if (!dir)
		return (NULL);
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
			continue ;
		if (match_pattern(pattern, entry->d_name))
		{
			full_path = ft_strjoin(" ", entry->d_name);
			list_add_back_wildcard(&matches, full_path);
			free(full_path);
			i++;
		}
	}
	closedir(dir);
	return (add_match(matches, pattern, i));
}

t_wildcard_list	*add_match(t_wildcard_list *matches, char *pattern, int i)
{
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

void	find_matches(char **args, t_wildcard_list **expanded, int i)
{
	t_wildcard_list	*current;
	t_wildcard_list	*matches;

	matches = expand_wildcards(args[i]);
	current = matches;
	while (current)
	{
		list_add_back_wildcard(expanded, current->content);
		current = current->next;
	}
	list_free_wildcard(matches);
}

char	**list_to_array(t_wildcard_list *head)
{
	t_wildcard_list	*current;
	char			**array;
	int				i;

	current = head;
	i = 0;
	array = malloc(sizeof(char *) * (list_size(head) + 1));
	if (!array)
		return (NULL);
	while (current)
	{
		array[i] = ft_strdup(current->content);
		current = current->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

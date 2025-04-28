/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atazzit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:54:28 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/26 18:54:32 by atazzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

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

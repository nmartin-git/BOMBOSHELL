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

#include "builtins.h"
#include "wildcard.h"

void	find_matches(char **args, t_wildcard_list **expanded, int i)
{
	t_wildcard_list	*current;
	t_wildcard_list	*matches;
	int				m;

	m = 0;
	matches = expand_wildcards(args[i]);
	current = matches;
	while (current)
	{
		list_add_back_wildcard(expanded, current->content);
		current = current->next;
		m = 1;
	}
	if (!m)
		list_add_back_wildcard(expanded, args[i]);
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

void	sort_wildcards(t_wildcard_list **rass)
{
	t_wildcard_list	*cur;
	t_wildcard_list	*i;
	char			*temp;

	if (!(*rass))
		return ;
	cur = *rass;
	while (cur)
	{
		i = cur->next;
		while (i)
		{
			if (ft_strcmp(cur->content, i->content) > 0)
			{
				temp = cur->content;
				cur->content = i->content;
				i->content = temp;
			}
			i = i->next;
		}
		cur = cur->next;
	}
}

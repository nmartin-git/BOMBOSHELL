/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atazzit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:43:02 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/11 17:56:20 by atazzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

void	list_add_back(t_wildcard **head, char *content)
{
	t_wildcard	*new_node;
	t_wildcard	*current;

	new_node = malloc(sizeof(t_wildcard));
	if (!new_node)
		return ;
	new_node->content = strdup(content);
	new_node->next = NULL;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	list_free(t_wildcard *head)
{
	t_wildcard	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->content);
		free(temp);
	}
}

char	**list_to_array(t_wildcard *head)
{
	int			count;
	t_wildcard	*current;
	char		**array;
	int			i;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	current = head;
	i = 0;
	while (current)
	{
		array[i++] = strdup(current->content);
		current = current->next;
	}
	array[i] = NULL;
	return (array);
}

int	has_wildcards(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

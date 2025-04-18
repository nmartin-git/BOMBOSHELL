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

void	list_add_back_wildcard(t_wildcard_list **head, char *content)
{
	t_wildcard_list	*new_node;
	t_wildcard_list	*current;

	new_node = malloc(sizeof(t_wildcard_list));
	if (!new_node)
		return ;
	new_node->content = ft_strdup(content);
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

void	list_free_wildcard(t_wildcard_list *head)
{
	t_wildcard_list	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->content);
		free(tmp);
	}
}

// char	**list_to_array(t_wildcard_list *head)
// {
// 	int				count;
// 	char			**array;
// 	t_wildcard_list	*current;
// 	int				i;

// 	count = 0;
// 	current = head;
// 	while (current)
// 	{
// 		count++;
// 		current = current->next;
// 	}
// 	array = malloc(sizeof(char *) * (count + 1));
// 	if (!array)
// 		return (NULL);
// 	current = head;
// 	i = 0;
// 	while (current)
// 	{
// 		array[i++] = ft_strdup(current->content);
// 		current = current->next;
// 	}
// 	array[i] = NULL;
// 	return (array);
// }

int	list_size(t_wildcard_list *head)
{
	int				count;
	t_wildcard_list	*current;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	has_wildcards(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*' || str[i] == '?')
			return (1);
		i++;
	}
	return (0);
}

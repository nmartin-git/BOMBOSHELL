/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:04:10 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/15 18:07:28 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	token_add(t_token *token_lst, int token)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		exit (127);//mieux gerer l'erreur
	if (token_lst)
	{
		while (token_lst->next)
			token_lst = token_lst->next;
		token_lst->next = new_token;
	}
	else
		token_lst = new_token;
	new_token->token = token;
	new_token->next = NULL;
}

int	token_get(char *input)
{
	if ((input[0] == '|' && input[1] == '|')
		|| (input[0] == '&' && input[1] == '&'))
		return (BOOL);
	else if (input[0] == '|')
		return (PIPE);
	else if ((input[0] == '>' || input[0] == '<'
		|| (input[0] == '>' && input[1] == '>')
		|| (input[0] == '<' && input[1] == '<')))
		return (REDIR);
	else if (input[0] == '(' || input[0] == ')')
		return (PARANTHESIS);
	else if (input[0] == ' ' && input[0] == '\t' && input[0] == '\n'
			&& input[0] == '\v' && input[0] == '\f' && input[0] == '\r')
		return (SPACE);
	else
		return (WORD);
}

t_token	*tokenisation(char *input)
{
	int		i;
	int		token;
	t_token	*token_lst;

	i = 0;
	token_lst = NULL;
	while (input[i])
	{
		token = token_get(&input[i]);
		if (token == SPACE)
		{
			ignore_spaces(input, &i);
			if (!input[i])
				return (token_lst);
			token = token_get(&input[i]);
		}
		token_add(token_lst, token);
		while (input[i + 1] && token == WORD)
			token = token_get(&input[++i]);
		if (!input[i])
			return (token_lst);
		i++;
	}
	return (token_lst);
}

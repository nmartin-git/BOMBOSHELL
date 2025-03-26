/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:04:10 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/26 16:40:21 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_prev_token(t_input *lst, t_input *arg)
{
	int	prev;

	prev = -1;
	if (lst == arg)
		return (-1);
	while (lst->next != arg)
	{
		if (lst->token != PARANTHESIS && lst->token != SPACES)
			prev = lst->token;
		lst = lst->next;
	}
	return (prev);
}

int	get_next_token(t_input *arg)
{
	while (arg->next)
	{
		arg = arg->next;
		if (arg->token != PARANTHESIS && arg->token != SPACES)
			return (arg->token);
	}
	return (-1);
}

void	token_add(t_input **token_lst, int token)
{
	t_input	*new_token;
	t_input	*tmp;

	tmp = NULL;
	if (token_lst)
		tmp = *token_lst;
	new_token = malloc(sizeof(t_input));
	if (!new_token)
		parsing_exit(*token_lst);
	new_token->token = token;
	new_token->arg = NULL;
	new_token->next = NULL;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
	else
		*token_lst = new_token;
}

int	token_get(char *input, int *i)
{
	if (!input[0])
		return (-1);
	if (i && ((input[0] == '|' && input[1] == '|')
			|| (input[0] == '&' && input[1] == '&')
			|| (input[0] == '>' && input[1] == '>')
			|| (input[0] == '<' && input[1] == '<')))
		*i += 1;
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
	else if (input[0] == ' ' || input[0] == '\t' || input[0] == '\n'
		|| input[0] == '\v' || input[0] == '\f' || input[0] == '\r')
		return (SPACES);
	else if (input[0] == '\'' || input[0] == '"')
		return (QUOTE);
	else
		return (WORD);
}

t_input	*tokenisation(char *input)
{
	int		i;
	int		token;
	t_input	*token_lst;

	i = 0;
	token_lst = NULL;
	while (input[i])
	{
		token = token_get(&input[i], &i);
		if (token == SPACES)
			i += ignore_spaces(&input[i]) - 1;
		token_add(&token_lst, token);
		while (token == WORD && token_get(&input[i + 1], NULL) == WORD)
			i++;
		i++;
	}
	return (token_lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:04:10 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/24 17:10:13 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	token_add(t_input **token_lst, int token)
{
	t_input	*new_token;
	t_input	*tmp;

	tmp = NULL;
	if (token_lst)
		tmp = *token_lst;
	new_token = malloc(sizeof(t_input));
	if (!new_token)
		exit (127);//TODO mieux gerer l'erreur
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

void	token_print(t_input *token_lst)//TODO supp
{
	while (token_lst)
	{
		if (token_lst->token == SPACES)
			printf("SPACES -> ");
		else if (token_lst->token == PIPE)
			printf("PIPE -> ");
		else if (token_lst->token == REDIR)
			printf("REDIR -> ");
		else if (token_lst->token == WORD)
			printf("WORD -> ");
		else if (token_lst->token == BOOL)
			printf("BOOL -> ");
		else if (token_lst->token == PARANTHESIS)
			printf("PARANTHESIS -> ");
		else if (token_lst->token == QUOTE)
			printf("QUOTE -> ");
		else if (token_lst->token == WORD_S_QUOTE)
			printf("WORD_S_QUOTE -> ");
		else if (token_lst->token == WORD_D_QUOTE)
			printf("WORD_D_QUOTE -> ");
		token_lst = token_lst->next;
	}
	printf("null\n");
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
	token_print(token_lst); //TODO a supprimer (la fonction aussi)
	return (token_lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 16:04:10 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/16 18:36:51 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	token_add(t_token **token_lst, int token)
{
	t_token	*new_token;
	t_token	*tmp;

	tmp = NULL;
	if (token_lst)
		tmp = *token_lst;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		exit (127);//mieux gerer l'erreur
	new_token->token = token;
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
	else
		return (WORD);
}

#include <stdio.h>
void	token_print(t_token *token_lst)
{
	printf("A");
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
		token_lst = token_lst->next;
	}
	printf("B");
	printf("null\n");
	printf("C");
}

void	token_parse(t_token *token_lst)
{
	token_lst = NULL;
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
		token = token_get(&input[i], &i);
		if (token == SPACES)
		{
			ignore_spaces(input, &i);
			if (!input[i])
				break;//return (token_lst); //remettre quand plus besoin de print
			token = token_get(&input[i], &i);
		}
		token_add(&token_lst, token);
		while (token == WORD && token_get(&input[i + 1], NULL) == WORD)
			i++;
		i++;
	}
	token_print(token_lst); //a supprimer (la fonction aussi)
	printf("A");
	token_parse(token_lst);//faire la fonction
	return (token_lst);
}

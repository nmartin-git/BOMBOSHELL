/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:39:48 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/18 19:56:00 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	lsts_simplify(t_token **token_lst, t_input **arg_lst)
{
	//supprimer les quotes unclosed
	//parse les parantheses unclosed
}

int	token_parse(t_token *token_lst, t_input *arg_lst)
{
	int	prev;

	if (token_lst->token == PIPE || token_lst->token == BOOL
		|| arg_lst->arg[0] == '>' || arg_lst->arg[0] == ')')
		return (parsing_error(arg_lst->arg), 0);
	prev = token_lst->token;
	token_lst = token_lst->next;
	arg_lst = arg_lst->next;
	while (token_lst->next)
	{
		if (prev)
		prev = token_lst->token;
		token_lst = token_lst->next;
		arg_lst = arg_lst->next;
	}
	return (1);
}

int	parsing(char *input)
{
	t_token	*token_lst = NULL;
	t_input	*arg_lst;

	token_lst = tokenisation(input);
	arg_lst = input_set(input);
	if (!lsts_simplify(&token_lst, &arg_lst))
	{
		lsts_free(token_lst, arg_lst);
		return(-1);
	}
	token_parse(token_lst, arg_lst);//supp qd exec fonction faite
	if (token_parse(token_lst, arg_lst))
	{
		lsts_free(token_lst, arg_lst);
		return(0);
	}
	else
	{
		lsts_free(token_lst, arg_lst);
		return(-1);
	}
}

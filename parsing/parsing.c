/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:39:48 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/20 16:53:20 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"



int	lsts_simplify(t_input **arg_lst)
{
	
	int		quotes;
	t_input	*tmp;

	quotes = 0;
	tmp = *arg_lst;
	unclosed_check(arg_lst);
	return (1);
	//supprimer les quotes unclosed
	//parse les parantheses unclosed
}

int	token_parse(t_input *arg_lst)
{
	int	prev;

	if (arg_lst->token == PIPE || arg_lst->token == BOOL
		|| arg_lst->arg[0] == '>' || arg_lst->arg[0] == ')')
		return (ft_printf_fd(2, "bomboshell: parse error near '%s'\n",
			arg_lst->arg), 0);
	prev = arg_lst->token;
	arg_lst = arg_lst->next;
	while (arg_lst)
	{
		if (prev)
			prev = arg_lst->token;
		arg_lst = arg_lst->next;
	}
	return (1);
}

int	parsing(char *input)
{
	t_input	*arg_lst;

	arg_lst = input_set(input);
	if (!lsts_simplify(&arg_lst))
	{
		lsts_free(arg_lst);
		return(-1);
	}
	if (!arg_lst)
	{
		lsts_free(arg_lst);
		return(0);
	}
	//token_parse(arg_lst);//supp qd exec fonction faite
	if (token_parse(arg_lst))
	{
		lsts_free(arg_lst);
		return(0);
	}
	else
	{
		lsts_free(arg_lst);
		return(-1);
	}
}

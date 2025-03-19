/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:39:48 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/19 17:17:00 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	del_last_quote(char quote, t_input **arg_lst)
{
	int		arg_nbr;
	int		del;
	t_input	*arg_tmp;
	t_input	*tmp;

	arg_nbr = 0;
	arg_tmp = *arg_lst;
	while (arg_tmp)
	{
		arg_nbr++;
		if ((*arg_lst)->arg[0] == quote)
			del = arg_nbr;
		arg_tmp = arg_tmp->next;
	}
	arg_nbr = 0;
	arg_tmp = *arg_lst;
	while (++arg_nbr != del)
		arg_tmp = arg_tmp->next;
	if (arg_tmp->next)
		tmp = arg_tmp->next->next;
	else
		tmp = NULL;
	free(arg_tmp->next->arg);
	free(arg_tmp->next);
	arg_tmp->next = tmp;
	// tmp = *arg_lst;
	// while (tmp)
	// {
	// 	printf("%s\n", tmp->arg);
	// 	tmp = tmp->next;
	// }
}

int	lsts_simplify(t_input **arg_lst)
{
	
	int		quotes;
	t_input	*tmp;

	quotes = 0;
	tmp = *arg_lst;
	while (tmp)
	{
		if (tmp->arg[0] == '\'')
			quotes++;
		tmp = tmp->next;
	}
	if (quotes % 2)
		del_last_quote('\'', arg_lst);
	quotes = 0;
	tmp = *arg_lst;
	while (tmp)
	{
		if (tmp->arg[0] == '"')
			quotes++;
		tmp = tmp->next;
	}
	if (quotes % 2)
		del_last_quote('"', arg_lst);
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

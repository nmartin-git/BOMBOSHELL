/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:40:33 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/27 19:27:39 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	del_last_quote(int del, t_input **arg_lst)
{
	t_input	*tmp;
	t_input	*tmp_del;

	if (del == 1)
	{
		tmp_del = *arg_lst;
		*arg_lst = (*arg_lst)->next;
		free(tmp_del->arg);
		free(tmp_del);
	}
	else
	{
		tmp = *arg_lst;
		while (--del != 1)
			tmp = tmp->next;
		tmp_del = tmp->next;
		if (tmp->next)
			tmp->next = tmp->next->next;
		else
			tmp->next = NULL;
		free(tmp_del->arg);
		free(tmp_del);
	}
}

void	get_last_quote(char quote, t_input **arg_lst, int impair)
{
	int		arg_nbr;
	int		del;
	t_input	*arg_tmp;

	if (!(impair % 2))
		return ;
	arg_nbr = 0;
	arg_tmp = *arg_lst;
	while (arg_tmp)
	{
		arg_nbr++;
		if (arg_tmp->arg[0] == quote)
			del = arg_nbr;
		arg_tmp = arg_tmp->next;
	}
	del_last_quote(del, arg_lst);
}

void	unclosed_check(t_input **arg, int s_quotes, int d_quotes, t_input *tmp)
{
	t_input	*check;

	while (tmp)
	{
		check = tmp->next;
		if (tmp->token == QUOTE && tmp->arg[0] == '"')
		{
			d_quotes++;
			while (check && !(check->token == QUOTE && check->arg[0] == '"'))
				check = check->next;
			if (check)
				tmp = unclosed_utils(d_quotes++, check);
		}
		else if (tmp->token == QUOTE && tmp->arg[0] == '\'')
		{
			s_quotes++;
			while (check && !(check->token == QUOTE && check->arg[0] == '\''))
				check = check->next;
			if (check)
				tmp = unclosed_utils(s_quotes++, check);
		}
		tmp = tmp->next;
	}
	get_last_quote('"', arg, d_quotes);
	get_last_quote('\'', arg, s_quotes);
}

void	del_quotes(t_input *prev, t_input *unified, t_input **arg_lst)
{
	t_input	*tmp;

	if (prev)
		(free_arg(prev->next), prev->next = unified);
	else
		(free_arg(*arg_lst), *arg_lst = unified);
	if (unified->token == WORD_D_QUOTE || unified->token == WORD_S_QUOTE)
	{
		tmp = unified->next->next;
		free_arg(unified->next);
		unified->next = tmp;
	}
	else
	{
		tmp = unified->next;
		free_arg(unified);
		if (prev)
			prev->next = tmp;
		else
			*arg_lst = tmp;
	}
}

void	unify(char quote, t_input *tmp, t_input *prev, t_input **arg_lst)
{
	t_input	*unified;
	t_input	*next;

	next = tmp;
	tmp = tmp->next;
	unified = tmp;
	while (tmp && !(tmp->token == QUOTE && tmp->arg[0] == quote))
	{
		if (tmp != unified)
		{
			tmp->arg = ft_strjoin_free(unified->arg, tmp->arg);
			free(unified);
			unified = tmp;
		}
		if (quote == '\'')
			unified->token = WORD_S_QUOTE;
		else
			unified->token = WORD_D_QUOTE;
		next->next = unified;
		tmp = tmp->next;
	}
	del_quotes(prev, unified, arg_lst);
}

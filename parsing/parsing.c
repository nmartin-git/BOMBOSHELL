/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:39:48 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/26 16:49:05 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	paranthesis_check(t_input *arg_lst)
{
	int	paranthesis_count;

	paranthesis_count = 0;
	while (arg_lst)
	{
		if (arg_lst->token == PARANTHESIS && arg_lst->arg[0] == '(')
			paranthesis_count++;
		else if (arg_lst->token == PARANTHESIS && arg_lst->arg[0] == ')')
			paranthesis_count--;
		if (paranthesis_count < 0)
			break ;
		arg_lst = arg_lst->next;
	}
	if (paranthesis_count > 0)
		return (ft_printf_fd(2, "bomboshell: parse error near '('\n", 0), 0);
	else if (paranthesis_count < 0)
		return (ft_printf_fd(2, "bomboshell: parse error near ')'\n", 0), 0);
	return (1);
}

int	quotes_unify(t_input *tmp, t_input *prev, t_input **arg_lst)
{
	t_input	*is_open;

	is_open = tmp->next;
	if (is_open && tmp->token == QUOTE && tmp->arg[0] == '\'')
	{
		while (is_open
			&& !(is_open->token == QUOTE && is_open->arg[0] == '\''))
		{
			if (!is_open->next)
				return (0);
			is_open = is_open->next;
		}
		return (unify('\'', tmp, prev, arg_lst), 1);
	}
	else if (is_open && tmp->token == QUOTE && tmp->arg[0] == '"')
	{
		while (is_open && !(is_open->token == QUOTE && is_open->arg[0] == '"'))
		{
			if (!is_open->next)
				return (0);
			is_open = is_open->next;
		}
		return (unify('"', tmp, prev, arg_lst), 1);
	}
	return (0);
}

int	lsts_simplify(t_input **arg_lst)
{
	t_input	*tmp;
	t_input	*prev;

	tmp = *arg_lst;
	prev = NULL;
	while (tmp && tmp->next)
	{
		if (!quotes_unify(tmp, prev, arg_lst))
			unclosed_check(arg_lst);
		tmp = *arg_lst;
		while (tmp && tmp->token != QUOTE)
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
	unclosed_check(arg_lst);
	if (!paranthesis_check(*arg_lst))
		return (0);
	return (1);
}

int	token_parse(t_input *arg_lst)
{
	t_input	*first;
	int		prev;
	int		next;

	first = arg_lst;
	while (arg_lst)
	{
		while (arg_lst
			&& (arg_lst->token == SPACES || arg_lst->token == PARANTHESIS))
			arg_lst = arg_lst->next;
		if (!arg_lst)
			break ;
		prev = get_prev_token(first, arg_lst);
		next = get_next_token(arg_lst);
		if (!parse_check(prev, next, arg_lst))
			return (ft_printf_fd(2, "bomboshell: parse error near '%s'\n",
					arg_lst->arg), 0);
		arg_lst = arg_lst->next;
	}
	return (1);
}

int	parsing(char *input, t_input **arg_lst)
{
	input_set(input, arg_lst);
	if (!lsts_simplify(arg_lst))
		return (-1);
	if (!*arg_lst)
		return (0);
	if (token_parse(*arg_lst))
		return (0);
	else
		return (-1);
}

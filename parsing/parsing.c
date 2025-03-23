/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:39:48 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/23 18:27:34 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
				return(0);
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
	tmp = *arg_lst;
	token_print(tmp);
	while (tmp)
	{
		printf("%s -> ", tmp->arg);
		tmp = tmp->next;
	}
	printf("null\n");
	unclosed_check(arg_lst);
	tmp = *arg_lst;
	token_print(tmp);
	while (tmp)
	{
		printf("%s -> ", tmp->arg);
		tmp = tmp->next;
	}
	printf("null\n");
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
		return (-1);
	}
	if (!arg_lst)
	{
		lsts_free(arg_lst);
		return (0);
	}
	if (token_parse(arg_lst))
	{
		lsts_free(arg_lst);
		//TODO exec
		return (0);
	}
	else
	{
		lsts_free(arg_lst);
		return (-1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:39:48 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/21 15:43:42 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	unify(char quote, t_input *tmp)
{
	t_input	*unified;
	t_input	*next;

	next = tmp;
	tmp = tmp->next;
	unified = tmp;
	while (tmp && tmp->token == QUOTE && tmp->arg[0] != quote)
	{
		if (tmp != unified)
		{
			tmp->arg = ft_strjoin_free(unified->arg, tmp->arg);
			tmp->token = WORD;
			free(unified);
			unified = tmp;
		}
		next->next = unified;
		tmp = tmp->next;
	}
}

void	quotes_unify(t_input *tmp)
{
	t_input	*is_closed;

	is_closed = tmp;
	if (tmp->token == QUOTE && tmp->arg[0] == '\'')
	{
		while (is_closed && !(is_closed->token == QUOTE && is_closed->arg[0] == '\''))
		{
			if (!is_closed->next)
				return;
			is_closed = is_closed->next;
		}
		unify('\'', tmp);
	}
	else if (tmp->token == QUOTE && tmp->arg[0] == '"')
	{
		while (is_closed && !(is_closed->token == QUOTE && is_closed->arg[0] == '"'))
		{
			if (!is_closed->next)
				return;
			is_closed = is_closed->next;
		}
		unify('"', tmp);
	}
}

int	lsts_simplify(t_input **arg_lst)
{
	t_input	*tmp;

	tmp = *arg_lst;
	while (tmp)
	{
		quotes_unify(tmp);
		tmp = tmp->next;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:40:33 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/22 18:45:50 by nmartin          ###   ########.fr       */
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

void	get_last_quote(char quote, t_input **arg_lst)
{
	int		arg_nbr;
	int		del;
	t_input	*arg_tmp;

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
	arg_tmp = *arg_lst;
	while (arg_tmp)
	{
		printf("%s\n", arg_tmp->arg);
		arg_tmp = arg_tmp->next;
	}
	if (!arg_tmp)
		printf("null\n");
}

void	unclosed_check(t_input **arg_lst)
{
	t_input	*tmp;
	int		quotes;

	tmp = *arg_lst;
	quotes = 0;
	while (tmp)
	{
		if (tmp->arg[0] == '"')
			quotes++;
		tmp = tmp->next;
	}
	if (quotes % 2)
		get_last_quote('"', arg_lst);
	tmp = *arg_lst;
	quotes = 0;
	while (tmp)
	{
		if (tmp->arg[0] == '\'')
			quotes++;
		tmp = tmp->next;
	}
	if (quotes % 2)
		get_last_quote('\'', arg_lst);
}

void	del_quotes(t_input *prev, t_input *unified, t_input **arg_lst)
{
	t_input	*tmp;

	if (prev)
	{
		free(prev->next->arg);
		free(prev->next);
		prev->next = unified;
		if (unified && unified->next)
		{
			tmp = unified->next->next;
			free(unified->next->arg);
			free(unified->next);
			unified->next = tmp;
		}
	}
	else
	{
		tmp = (*arg_lst)->next;
		free((*arg_lst)->arg);
		free(*arg_lst);
		*arg_lst = unified;
	}
}

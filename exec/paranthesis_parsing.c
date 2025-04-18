/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paranthesis_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:08:45 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/18 18:09:17 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	del_paranthesis(t_input **arg_lst, t_input *del, t_input *prev)
{
	if (prev)
		prev->next = del->next;
	else
		*arg_lst = del->next;
	free_arg(del);
}

int	paranthesis_bool(t_input **arg_lst, t_input *tmp, t_input *prev, int i)
{
	t_input	*paranthesis;

	tmp = *arg_lst;
	while (tmp)
	{
		if (tmp->token == PARANTHESIS && tmp->arg[0] == '(')
			i--;
		if (!i)
			break;
		prev = tmp;
		tmp = tmp->next;
	}
	paranthesis = tmp;
	while (tmp && tmp->token != BOOL)
	{
		if (tmp->next && tmp->next->token == PARANTHESIS
			&& tmp->next->arg[0] == ')')
		{
			del_paranthesis(arg_lst, tmp->next, tmp);
			del_paranthesis(arg_lst, paranthesis, prev);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	paranthesis_parsing(t_input **arg_lst, t_input *tmp, t_input *prev)
{
	int		paranthesis_nbr;

	paranthesis_nbr = 0;
	while (tmp)
	{
		if (tmp->token == PARANTHESIS && tmp->arg[0] == '(' && prev
			&& prev->token != PIPE && prev->token != BOOL)
		{
			write(2, "bomboshell: parse error near '('\n", 33);
			return (0);
		}
		if (tmp->token != SPACES)
			prev = tmp;
		tmp = tmp->next;
	}
	tmp = *arg_lst;
	while (tmp)
	{
		if (tmp->token == PARANTHESIS)
			paranthesis_nbr++;
		tmp = tmp->next;
	}
	while (paranthesis_nbr)
		paranthesis_bool(arg_lst, *arg_lst, NULL, paranthesis_nbr--);
	return (1);
}

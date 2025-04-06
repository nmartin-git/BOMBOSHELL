/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokenisation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:01:16 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/06 14:36:51 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_input	*del_redir(t_input **arg_lst, t_input *tmp, t_input *prev)
{
	if (prev)
	{
		prev->next = tmp->next;
		prev = prev->next;
	}
	else
	{
		*arg_lst = tmp->next;
		prev = *arg_lst;
	}
	free_arg(tmp);
	return (prev);
}

void	del_spaces(t_input *tmp)
{
	t_input	*del;

	del = tmp->next;
	while (del && del->token == SPACES)
	{
		tmp->next = del->next;
		free_arg(del);
		del = tmp->next;
	}
}

void	files_tokenisation(t_input **arg_lst, t_input *prev)
{
	t_input	*tmp;

	tmp = *arg_lst;
	while (tmp && tmp->next)
	{
		if (tmp->token == REDIR)
		{
			del_spaces(tmp);
			if (tmp->arg[0] == '<' && tmp->arg[1] == '<')
				tmp->next->token = HERE_DOC;
			else if (tmp->arg[0] == '<')
				tmp->next->token = INFILE;
			else if (tmp->arg[0] == '>' && tmp->arg[1] == '>')
				tmp->next->token = APPEND;
			else if (tmp->arg[0] == '>')
				tmp->next->token = OUTFILE;
			prev = del_redir(arg_lst, tmp, prev);
		}
		else
			prev = tmp;
		if (!prev)
			break ;
		tmp = prev->next;
	}
}

void	cmd_tokenisation(t_input *arg_lst)
{
	t_input	*del;

	while (arg_lst)
	{
		if (arg_lst->token == WORD || arg_lst->token == WORD_S_QUOTE
			|| arg_lst->token == WORD_D_QUOTE)
		{
			arg_lst->token = CMD;
			while (arg_lst->next && (arg_lst->next->token == WORD
					|| arg_lst->next->token == SPACES
					|| arg_lst->next->token == WORD_S_QUOTE
					|| arg_lst->next->token == WORD_D_QUOTE))
			{
				arg_lst->arg = ft_strjoin_free
					(arg_lst->arg, arg_lst->next->arg);
				del = arg_lst->next;
				arg_lst->next = arg_lst->next->next;
				free(del);
			}
		}
		arg_lst = arg_lst->next;
	}
}

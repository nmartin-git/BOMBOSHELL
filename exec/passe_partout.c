/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passe_partout.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:49:19 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/28 18:12:44 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_input	*del_redir(t_input **arg_lst, t_input *tmp, t_input *prev)
{
	t_input	*del;

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
	tmp = prev;
	while (tmp && tmp->next && (tmp->next->token == WORD_D_QUOTE
			|| tmp->next->token == WORD_S_QUOTE))
	{
		tmp->arg = ft_strjoin_free(tmp->arg, tmp->next->arg);
		del = tmp->next;
		tmp->next = tmp->next->next;
		free(del);
	}
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

void	skip_paranthesis_utils(t_input **files, t_exec **exec_tmp, int p)
{
	int	fd_pipe[2];

	*files = (*files)->next;
	while (*files && (*files)->token == SPACES)
		*files = (*files)->next;
	if ((*exec_tmp) && *files && (*files)->token == BOOL)
	{
		if ((*files)->arg[0] == '&')
			(*exec_tmp)->exec_both = 1;
		else
			(*exec_tmp)->exec_both = 0;
	}
	if (*files && (*files)->token == PIPE && *exec_tmp && p > 0)
	{
		ppx_exit(pipe(fd_pipe), "Failed opening the pipe", NULL, 1);
		(*exec_tmp)->input = fd_pipe[0];
		(*exec_tmp)->close_bool = fd_pipe[1];
		bool_output(*exec_tmp, fd_pipe[1], fd_pipe[0]);
	}
}

void	skip_paranthesis(t_input **files, t_exec **exec_tmp, int p, int order)
{
	while (*files && !((*files)->token == PARANTHESIS
			&& (*files)->arg[0] == ')'))
	{
		if (*exec_tmp && (*files)->token == CMD)
		{
			(*files)->token = CMD_BOOL;
			(*exec_tmp)->order = order;
			(*exec_tmp)->paranthesis = p;
			*exec_tmp = (*exec_tmp)->next;
		}
		else if ((*exec_tmp) && (*files)->token == BOOL)
		{
			if (*exec_tmp && (*exec_tmp)->next && (*files)->arg[0] == '&')
				(*exec_tmp)->next->exec_both = 1;
			else if (*exec_tmp && (*exec_tmp)->next)
				(*exec_tmp)->next->exec_both = 0;
		}
		*files = (*files)->next;
		if ((*files)->token == PARANTHESIS && (*files)->arg[0] == '(')
			skip_paranthesis(files, exec_tmp, p + 1, order);
	}
	skip_paranthesis_utils(files, exec_tmp, p);
}

void	next_cmd(t_input **files, t_exec **exec_tmp, t_input **tmp, int *order)
{
	t_input	*is_paranthesis;

	while (*files && (*files)->token != PIPE && (*files)->token != BOOL)
		*files = (*files)->next;
	is_paranthesis = *files;
	if (is_paranthesis && is_paranthesis->next)
		is_paranthesis = is_paranthesis->next;
	while (is_paranthesis && is_paranthesis->token == SPACES)
		is_paranthesis = is_paranthesis->next;
	if (is_paranthesis && is_paranthesis->token == PARANTHESIS)
		*files = is_paranthesis;
	if (*exec_tmp)
		*exec_tmp = (*exec_tmp)->next;
	if (*files && ((*files)->token == BOOL || (*files)->token == PARANTHESIS))
	{
		if ((*exec_tmp) && *files && (*files)->token == BOOL)
		{
			if ((*files)->arg[0] == '&')
				(*exec_tmp)->exec_both = 1;
			else
				(*exec_tmp)->exec_both = 0;
		}
		skip_bool(files, exec_tmp, NULL, order);
	}
	*tmp = *files;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fourre_tout.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:33:37 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/27 14:44:37 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_input	*diddy_shortcut(t_input **arg_lst)
{
	t_input	*tmp;

	tmp = *arg_lst;
	*arg_lst = (*arg_lst)->next;
	return (tmp);
}

void	close_bool(t_exec **exec_lst)
{
	if ((*exec_lst)->input > 2 && !((*exec_lst)->next
			&& (*exec_lst)->input == (*exec_lst)->next->input))
		close((*exec_lst)->input);
	if ((*exec_lst)->output > 2 && !((*exec_lst)->next
			&& (*exec_lst)->output == (*exec_lst)->next->output))
		close((*exec_lst)->output);
}

void	skip_boolgauche(t_input **files, t_exec **exec_tmp)
{
	if ((*exec_tmp))
	{
		if (*exec_tmp && (*files)->arg[0] == '&')
			(*exec_tmp)->exec_both = 1;
		else if (*exec_tmp)
			(*exec_tmp)->exec_both = 0;
	}
	*files = (*files)->next;
	while (*files && (*files)->token == SPACES)
		*files = (*files)->next;
	if (*files && (*files)->token != PARANTHESIS)
	{
		while (*files && (*files)->token != BOOL)
		{
			if (*exec_tmp && (*files)->token == CMD)
			{
				(*files)->token = CMD_BOOL;
				*exec_tmp = (*exec_tmp)->next;
			}
			*files = (*files)->next;
		}
	}
}

int	skip_booldroite(t_input **files, t_exec **exec_tmp, t_input **tmp)
{
	int	fd_pipe[2];

	while (*files && (*files)->token == SPACES)
		*files = (*files)->next;
	if (*files && (*files)->token == PIPE && *exec_tmp
		&& (*exec_tmp)->next)
	{
		ppx_exit(pipe(fd_pipe), "Failed opening the pipe", NULL, 1);
		(*exec_tmp)->input = fd_pipe[0];
		(*exec_tmp)->close_bool = fd_pipe[1];
		bool_output(*exec_tmp, fd_pipe[1], fd_pipe[0]);
	}
	if (tmp)
	{
		*tmp = *files;
		while (*tmp && (*tmp)->token != CMD)
			*tmp = (*tmp)->next;
	}
	if (!*files || ((*files)->token != BOOL
			&& (*files)->token != PARANTHESIS))
		return (0);
	return (1);
}

void	skip_bool(t_input **files, t_exec **exec_tmp, t_input **tmp, int *ordr)
{
	while (*files)
	{
		if (*files && (*files)->token == BOOL)
			skip_boolgauche(files, exec_tmp);
		else if (*files && (*files)->token == PARANTHESIS
			&& (*files)->arg[0] == '(')
		{
			*ordr += 1;
			skip_paranthesis(files, exec_tmp, 1, *ordr);
		}
		else if (!skip_booldroite(files, exec_tmp, tmp))
			break ;
	}
}

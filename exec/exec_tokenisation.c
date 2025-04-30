/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokenisation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:01:16 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/27 14:45:34 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	set_file_token(t_input *tmp)
{
	if (tmp->arg[0] == '<' && tmp->arg[1] == '<')
	{
		if (tmp->next->token == WORD_S_QUOTE)
			tmp->next->here_doc_s_or_d = 0;
		else
			tmp->next->here_doc_s_or_d = 1;
		tmp->next->token = HERE_DOC;
	}
	else if (tmp->arg[0] == '<')
		tmp->next->token = INFILE;
	else if (tmp->arg[0] == '>' && tmp->arg[1] == '>')
		tmp->next->token = APPEND;
	else if (tmp->arg[0] == '>')
		tmp->next->token = OUTFILE;
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
			set_file_token(tmp);
			prev = del_redir(arg_lst, tmp, prev);
		}
		else
			prev = tmp;
		if (!prev)
			break ;
		tmp = prev->next;
	}
}

void	cmd_word_order(t_input *arg, t_input *del, t_input *cmd, t_input *prev)
{
	while (arg->next && arg->next->token != PIPE && arg->next->token != BOOL)
	{
		if (arg->next->token == WORD || arg->next->token == WORD_S_QUOTE
			|| arg->next->token == WORD_D_QUOTE)
		{
			if (arg->token == SPACES)
			{
				cmd->arg = ft_strjoin_free(cmd->arg, ft_strdup(" "));
				del_redir(NULL, arg, prev);
				arg = prev;
			}
			cmd->arg = ft_strjoin_free(cmd->arg, arg->next->arg);
			del = arg->next;
			arg->next = arg->next->next;
			free(del);
		}
		else
		{
			while (arg->next && arg->next->token != WORD_D_QUOTE
				&& arg->next->token != WORD && arg->next->token != WORD_S_QUOTE
				&& arg->next->token != PIPE && arg->next->token != BOOL)
				prev = diddy_shortcut(&arg);
		}
	}
}

void	cmd_tokenisation_utils(t_input *arg_lst)
{
	t_input	*del;

	if (arg_lst->next->token == SPACES && arg_lst->next->next
		&& (arg_lst->next->next->token == WORD
			|| arg_lst->next->next->token == WORD_S_QUOTE
			|| arg_lst->next->next->token == WORD_D_QUOTE))
	{
		arg_lst->arg = ft_strjoin_free(arg_lst->arg,
				ft_strdup(" "));
		del_redir(NULL, arg_lst->next, arg_lst);
	}
	else if (arg_lst->next->token == SPACES)
		del_redir(NULL, arg_lst->next, arg_lst);
	else
	{
		arg_lst->arg = ft_strjoin_free(arg_lst->arg,
				arg_lst->next->arg);
		del = arg_lst->next;
		arg_lst->next = arg_lst->next->next;
		free(del);
	}
}

void	cmd_tokenisation(t_input *arg_lst)
{
	while (arg_lst)
	{
		if (arg_lst->token == WORD || arg_lst->token == WORD_S_QUOTE
			|| arg_lst->token == WORD_D_QUOTE)
		{
			arg_lst->token = CMD;
			if (ft_strncmp(arg_lst->arg, "export", 7) == 0)
				export_parsing(arg_lst);
			cmd_word_order(arg_lst, NULL, arg_lst, arg_lst);
			while (arg_lst->next && (arg_lst->next->token == WORD
					|| arg_lst->next->token == SPACES
					|| arg_lst->next->token == WORD_S_QUOTE
					|| arg_lst->next->token == WORD_D_QUOTE))
				cmd_tokenisation_utils(arg_lst);
		}
		arg_lst = arg_lst->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tokenisation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:01:16 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/10 23:04:59 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

void	export_parsing_utils(t_input* arg_lst)
{
	t_input	*del;

	while (arg_lst->next && arg_lst->next->token == SPACES)
	{
		arg_lst->arg = ft_strjoin_free(arg_lst->arg, arg_lst->next->arg);//TODO gerer l'erreur de malloc
		del = arg_lst->next;
		arg_lst->next = arg_lst->next->next;
		free(del);
	}
	if (!arg_lst->next
		|| arg_lst->next->token == PIPE || arg_lst->token == BOOL)
		return;
	arg_lst->arg = ft_strjoin_free (arg_lst->arg, arg_lst->next->arg);//TODO gerer l'erreur de malloc
	del = arg_lst->next;
	arg_lst->next = arg_lst->next->next;
	free(del);
	return ;
}

void	export_get_arg(t_input *arg_lst, char *str, int i)
{
	t_input	*del;

	if (arg_lst->arg[i] == ' ' || (!arg_lst->arg[i] && !arg_lst->next))
	{
		str = ft_strdup("\"\"");
		arg_lst->arg = ft_strjoin_free(arg_lst->arg, str);
		return ;
	}
	if (!arg_lst->arg[i])
	{
		if (!arg_lst->next)
			return ;
		arg_lst->next->arg = ft_str_quotes(arg_lst->next->arg, '"', '"');//TODO gerer l'erreur
		arg_lst->arg = ft_strjoin_free (arg_lst->arg, arg_lst->next->arg);//TODO gerer l'erreur
		del = arg_lst->next;
		arg_lst->next = arg_lst->next->next;
		free(del);
	}
	else
	{
		str = ft_strdup(&arg_lst->arg[i]);
		str = ft_str_quotes(str, '"', '"');//TODO gerer l'erreur
		arg_lst->arg[i] = '\0';
		arg_lst->arg = ft_strjoin_free(arg_lst->arg, str);
	}
}

void	export_parsing(t_input *arg_lst)
{
	int		i;
	t_input *tmp;

	tmp = arg_lst;
	i = 0;
	while (arg_lst->next && (arg_lst->next->token == WORD
			|| arg_lst->next->token == SPACES
			|| arg_lst->next->token == WORD_S_QUOTE
			|| arg_lst->next->token == WORD_D_QUOTE))
	{
		export_parsing_utils(arg_lst);
		while (arg_lst->arg[i] && arg_lst->arg[i] != '=')
			i++;
		if (arg_lst->arg[i++] == '=')
			export_get_arg(arg_lst, NULL, i);
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
			if (ft_strncmp(arg_lst->arg, "export", 7) == 0)
				export_parsing(arg_lst);
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

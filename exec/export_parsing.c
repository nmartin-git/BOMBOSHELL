/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:54:40 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/16 21:45:23 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_input	*ignore_redir(t_input *arg_lst)
{
	while (arg_lst->next && arg_lst->next->token != PIPE
		&& arg_lst->next->token != BOOL 
		&& (arg_lst->next->token == INFILE || arg_lst->next->token == HERE_DOC
		|| arg_lst->next->token == APPEND || arg_lst->next->token == OUTFILE))
	{
		arg_lst = arg_lst->next;
		if (arg_lst->next && arg_lst->next && arg_lst->next->token == SPACES
			&& !(arg_lst->next->next && (arg_lst->next->next->token == WORD
			|| arg_lst->next->next->token == WORD_D_QUOTE
			|| arg_lst->next->next->token == WORD_S_QUOTE)))
			arg_lst = arg_lst->next;
	}
	return (arg_lst);
}

int	export_parsing_utils(t_input* arg_lst, t_input *first)
{
	t_input	*del;
	int		quotes;

	while (arg_lst->next && arg_lst->next->token == SPACES)
	{
		arg_lst->arg = ft_strjoin_free(arg_lst->arg, arg_lst->next->arg);//TODO gerer l'erreur de malloc
		del = arg_lst->next;
		arg_lst->next = arg_lst->next->next;
		free(del);
	}
	arg_lst = ignore_redir(arg_lst);
	if (!arg_lst->next
		|| arg_lst->next->token == PIPE || arg_lst->token == BOOL)
		return (-1);
	if (arg_lst->next->token == WORD_S_QUOTE
		|| arg_lst->next->token == WORD_D_QUOTE)
		quotes = 1;
	else
		quotes = 0;
	first->arg = ft_strjoin_free (first->arg, arg_lst->next->arg);//TODO gerer l'erreur de malloc
	del = arg_lst->next;
	arg_lst->next = arg_lst->next->next;
	free(del);
	return (quotes);
}

void	export_quotes(t_input *arg_lst, int i)
{
	t_input	*del;
	char	*str;

	if (arg_lst->next->token == SPACES)
		str = ft_strdup(&arg_lst->arg[i]);//TODO gerer l'erreur
	else
		str = ft_strjoin_free(ft_strdup(&arg_lst->arg[i]),
						ft_strdup(arg_lst->next->arg));//TODO gerer l'erreur
	arg_lst->arg[i] = '\0';
	str = ft_str_quotes(str, '"', '"');//TODO gerer l'erreur
	del = arg_lst->next;
	arg_lst->next = arg_lst->next->next;
	free(del);
	arg_lst->arg = ft_strjoin_free(arg_lst->arg, str);//TODO gerer l'erreur
}

void	export_get_arg(t_input *arg_lst, int i, int	quotes)
{
	t_input	*del;
	char	*str;

	if (quotes && arg_lst->arg[i] && arg_lst->next)
		export_quotes(arg_lst, i);
	else if (arg_lst->arg[i] == ' ' || (!arg_lst->arg[i] && (!arg_lst->next
		|| (arg_lst->next && arg_lst->next->token == SPACES))))
		arg_lst->arg = ft_strjoin_free(arg_lst->arg, ft_strdup("\"\""));//TODO gerer l'erreur
	else if (!arg_lst->arg[i]
		&& arg_lst->next->token != PIPE && arg_lst->next->token != BOOL)
	{
		arg_lst->next->arg = ft_str_quotes(arg_lst->next->arg, '"', '"');//TODO gerer l'erreur
		arg_lst->arg = ft_strjoin_free (arg_lst->arg, arg_lst->next->arg);//TODO gerer l'erreur
		del = arg_lst->next;
		arg_lst->next = arg_lst->next->next;
		free(del);
	}
	else
	{
		str = ft_str_quotes(ft_strdup(&arg_lst->arg[i]), '"', '"');//TODO gerer l'erreur
		arg_lst->arg[i] = '\0';
		arg_lst->arg = ft_strjoin_free(arg_lst->arg, str);
	}
}

void	export_parsing(t_input *arg_lst)
{
	int		i;
	int		quotes;
	t_input *del;

	i = 0;
	while (arg_lst->next && arg_lst->next->token != BOOL
		&& arg_lst->next->token != PIPE)
	{
		quotes = export_parsing_utils(arg_lst, arg_lst);
		if (quotes == -1)
			return ;
		while (arg_lst->arg[i] && arg_lst->arg[i] != '=')
			i++;
		if (!arg_lst->arg[i] && arg_lst->next && arg_lst->next->arg[0] == '=')
		{
			arg_lst->arg = ft_strjoin_free(arg_lst->arg, arg_lst->next->arg);//TODO gerer l'erreur de malloc
			del = arg_lst->next;
			arg_lst->next = arg_lst->next->next;
			free(del);
		}
		if (arg_lst->arg[i++] == '=')
			export_get_arg(arg_lst, i, quotes);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:11:00 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/18 19:43:05 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ignore_spaces(char *str, int *i) 
{
	while (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'
			|| str[*i] == '\v' || str[*i] == '\f' || str[*i] == '\r')
		*i += 1;
}

void	lsts_free(t_token *token_lst, t_input *arg_lst)
{
	void	*tmp;
	
	while (token_lst)
	{
		tmp = (void *)token_lst->next;
		free(token_lst);
		token_lst = (t_token *)tmp;
	}
	while (arg_lst)
	{
		tmp = (void *)arg_lst->next;
		free(arg_lst->arg);
		free(arg_lst);
		arg_lst = (t_input *)tmp;
	}
}

void	parsing_error(char *arg)
{
	write(2, "bomboshell: parse error near '", 30);
	write(2, arg, ft_strlen(arg));
	write(2, "'\n", 2);
}
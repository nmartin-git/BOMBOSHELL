/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_tokenisation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:01:16 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/30 14:23:37 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	files_tokenisation(t_input **arg_lst)
{
	t_input	*tmp;
	t_input	*prev;

	tmp = *arg_lst;
	prev = NULL;
	while (tmp && tmp->next)
	{
		
		if (tmp->token == REDIR)
		{
			if (tmp->arg[0] == '<' && tmp->arg[1] == '<')
				
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:11:00 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/23 15:45:35 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_arg(t_input *arg)
{
	free(arg->arg);
	free(arg);
}

int	ignore_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

void	lsts_free(t_input *arg_lst)
{
	t_input	*tmp;

	while (arg_lst)
	{
		tmp = arg_lst->next;
		free(arg_lst->arg);
		free(arg_lst);
		arg_lst = (t_input *)tmp;
	}
}

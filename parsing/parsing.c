/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:39:48 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/16 18:35:01 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

void	ignore_spaces(char *str, int *i) 
{
	while (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'
			|| str[*i] == '\v' || str[*i] == '\f' || str[*i] == '\r')
		*i += 1;
}

int	parsing(char *input)
{
	t_token	*token_lst;
	t_input	*arg_lst;

	(void)input;
	token_lst = tokenisation(input);
	arg_lst = input_set(input);
	//test;
	return (0);
}

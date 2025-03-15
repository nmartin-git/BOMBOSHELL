/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:39:48 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/15 16:22:32 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

void	ignore_spaces(char *str, int *i)
{
	while (str[*i] == ' ' && str[*i] == '\t' && str[*i] == '\n'
			&& str[*i] == '\v' && str[*i] == '\f' && str[*i] == '\r')
		*i++;
}

int	parsing(char *input)
{
	(void)input;
	//test;
	return (0);
}

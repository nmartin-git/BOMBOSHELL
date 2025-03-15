/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomboshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:45:55 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/14 13:57:20 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bomboshell.h"

int	only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
			&& str[i] != '\v' && str[i] != '\f' && str[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("🍑😱💣>");
		if (input)
		{
			parsing(input);
			if (!only_space(input))
				add_history(input);
			if (ft_strncmp(input, "STOP", 4) == 0)
			{
				free(input);
				break ;
			}
			free(input);
		}
	}
	rl_clear_history();
}

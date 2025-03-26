/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomboshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:45:55 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/26 16:50:35 by nmartin          ###   ########.fr       */
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

int	main(int ac, char **av)
{
	char	*input;
	t_input	*arg_lst;

	if (ac != 1)
	{
write(2, "bomboshell: too many arguments\n", 31);
		return (2/*mettre bon exit code*/);
	}
	while (1)
	{
		input = readline("🚀🍑😱💣> ");
		if (!input)
			break ;
		arg_lst = NULL;
		if (parsing(input, &arg_lst))
			write(1, "exec\n", 5);//exec();
		lsts_free(arg_lst);
		if (!only_space(input))
			add_history(input);
		free(input);
	}
	rl_clear_history();
}

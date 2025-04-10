/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomboshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:45:55 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/06 17:55:13 by nmartin          ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_input	*arg_lst;
	t_env	*env;

	(void)av;
	if (ac > 1)
	{
		write(2, "bomboshell: too many arguments\n", 31);
		return (2);
	}
	env = init_env(envp);
	while (1)
	{
		input = readline("🚀🍑😱💣> ");
		if (!input)
			break ;
		arg_lst = NULL;
		if (parsing(input, &arg_lst) && arg_lst)
			exec(&arg_lst, &env);
		lsts_free(arg_lst);
		if (!only_space(input))
			add_history(input);
		free(input);
	}
	rl_clear_history();
}

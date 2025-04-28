/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomboshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:45:55 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/27 18:44:06 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bomboshell.h"

void	prompt_sig(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	shlvl_to_the_moon(t_env *env)
{
	char	*current;
	int		lvl;
	char	*new;

	current = get_env_value(env, "SHLVL");
	if (!current)
		lvl = 0;
	else
		lvl = ft_atoi(current);
	lvl++;
	new = ft_itoa(lvl);
	if (!new)
		return ;
	set_env_value(env, "SHLVL", new);
	free(new);
}

int	only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\v'
			&& str[i] != '\f' && str[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

t_env	*bombostart(int ac, char **av, char **envp)
{
	t_env	*env;

	if (isatty(STDIN_FILENO) == 0 || isatty(STDERR_FILENO) == 0
		|| isatty(STDOUT_FILENO) == 0)
	{
		write(2, "\033[31m\033[1mbomboshell: MI BOMBOCLAT ERROR\n\033[0m", 44);
		exit(1);
	}
	if (ac > 1 && av)
	{
		write(2, "bomboshell: too many arguments\n", 31);
		exit(2);
	}
	env = init_env(envp);
	shlvl_to_the_moon(env);
	prompt_sig();
	return (env);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_input	*arg_lst;
	t_env	*env;
	int		parsing_exit;

	env = bombostart(ac, av, envp);
	while (1)
	{
		input = readline("🚀🍑😱💣> ");
		if (!input)
		{
			write(1, "exit\n", 5);
			g_exit_status = 0;
			break ;
		}
		parsing_exit = parsing(input, &arg_lst);
		if (parsing_exit && arg_lst)
			exec(&arg_lst, &env, NULL, arg_lst);
		else if (!parsing_exit)
			g_exit_status = 2;
		if (!only_space(input))
			add_history(input);
		(lsts_free(arg_lst), free(input));
	}
	(free_env(env), rl_clear_history());
}

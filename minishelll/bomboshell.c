/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomboshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:45:55 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/14 17:06:49 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bomboshell.h"

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
// void	cleanup_resources(t_env *env, t_exec *exec)
// {
// 	free_env_list(env);
// 	if (exec)
// 		free_exec_lst(exec);
// }

// int main()
// {
//     cleanup_resources(env, input, exec_lst);
//     return (exit_status);
// }

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_input	*arg_lst;
	t_env	*env;

	// if (isatty(STDIN_FILENO) == 0 || isatty(STDERR_FILENO) == 0
	// 	|| isatty(STDOUT_FILENO) == 0)
	// 	return (1);
	if (ac > 1 && av)
	{
		write(2, "bomboshell: too many arguments\n", 31);
		return (2);
	}
	env = init_env(envp);
	prompt_sig();
	while (1)
	{
		input = readline("🚀🍑😱💣> ");
		if (!input)
			break ;
		arg_lst = NULL;
		if (parsing(input, &arg_lst) && arg_lst)
			exec(&arg_lst, &env, NULL);
		lsts_free(arg_lst);
		if (!only_space(input))
			add_history(input);
		free(input);
	}
	free_env(env);
	rl_clear_history();
}

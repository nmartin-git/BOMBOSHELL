/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:25:03 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/12 13:17:49 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

t_shell	*set_t_shell(t_env *env, char *cmd)
{
	t_shell	*command;
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
		exit(127);//TODO mieux gerer l'erreur
	command = malloc(sizeof(t_shell));
	if (!command)
		exit(127);//TODO mieux gerer l'erreur
	command->env_vars = env;
	command->current_dir = getcwd(NULL, PATH_MAX_ANANAS);
	command->command = args;
	return (command);
}

void	execute_builtin(t_env **env, char *cmd)
{
	t_shell	*command;

	command = set_t_shell(*env, cmd);
	int i = 0;
	while (command->command[i])
		printf("*%s*\n", command->command[i++]);
	if (ft_strncmp(command->command[0], "cd", 2) == 0)
		return exit(ft_cd(command));
	else if (ft_strncmp(command->command[0], "echo", 4) == 0)
		return exit(ft_echo(command));
	else if (ft_strncmp(command->command[0], "env", 3) == 0)
		return exit(ft_env(*env));
	else if (ft_strncmp(command->command[0], "exit", 4) == 0)
		return exit(ft_exit(command));
	else if (ft_strncmp(command->command[0], "export", 6) == 0)
		return exit(ft_export(command));
	else if (ft_strncmp(command->command[0], "pwd", 3) == 0)
		return exit(ft_pwd(command));
	else if (ft_strncmp(command->command[0], "unset", 5) == 0)
		return exit(ft_unset(command));
	else
		return exit(0);
}
int	is_built_in(char *cmd, int i)
{
	while (cmd[i] == ' ')
		i++;
	if (ft_strncmp(&cmd[i], "cd", 2) == 0
			&& (!cmd[i + 2] || cmd[i + 2] == ' '))
		return (1);
	else if (ft_strncmp(&cmd[i], "echo", 4) == 0
			&& (!cmd[i + 4] || cmd[i + 4] == ' '))
		return (1);
	else if (ft_strncmp(&cmd[i], "env", 3) == 0
			&& (!cmd[i + 3] || cmd[i + 3] == ' '))
		return (1);
	else if (ft_strncmp(&cmd[i], "exit", 4) == 0
			&& (!cmd[i + 4] || cmd[i + 4] == ' '))
		return (1);
	else if (ft_strncmp(&cmd[i], "export", 6) == 0
			&& (!cmd[i + 6] || cmd[i + 6] == ' '))
		return (1);
	else if (ft_strncmp(&cmd[i], "pwd", 3) == 0
			&& (!cmd[i + 3] || cmd[i + 3] == ' '))
		return (1);
	else if (ft_strncmp(&cmd[i], "unset", 5) == 0
			&& (!cmd[i + 5] || cmd[i + 5] == ' '))
		return (1);
	return (0);
}

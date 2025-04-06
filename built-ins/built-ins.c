/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:25:03 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/06 16:10:39 by nmartin          ###   ########.fr       */
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
	command->current_dir = getcwd(NULL, 0);
	command->command = args;
}

int	execute_builtin(t_env *env, char *cmd)
{
	t_shell	*command;

	command = set_t_shell(env, cmd);
	if (ft_strncmp(command->command[0], "cd", 2) == 0)
		return (ft_cd(shell));
	else if (ft_strncmp(command->command[0], "echo", 4) == 0)
		return (ft_echo(shell));
	else if (ft_strncmp(command->command[0], "env", 3) == 0)
		return (ft_env(env));
	else if (ft_strncmp(command->command[0], "exit", 4) == 0)
		return (ft_exit(shell));
	else if (ft_strncmp(command->command[0], "export", 6) == 0)
		return (ft_export(shell));
	else if (ft_strncmp(command->command[0], "pwd", 3) == 0)
		return (ft_pwd(shell));
	else if (ft_strncmp(command->command[0], "unset", 5) == 0)
		return (ft_unset(shell));
	else
		return (0);
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

// int	execute_builtin(char **av, char **envp)
// {
// 	static t_env	*env_list = NULL;
// 	static t_shell	*shell = NULL;
// 	t_command		cmd;

// 	if (!av || !envp)
// 		return (0);
// 	if (!env_list)
// 		env_list = init_env(envp);
// 	if (!shell)
// 	{
// 		shell = malloc(sizeof(t_shell));
// 		if (!shell)
// 			return (0);
// 		shell->env_vars = env_list;
// 		shell->current_dir = getcwd(NULL, 0);
// 		shell->command = NULL;
// 	}
// 	init_command(&cmd, av);
// 	shell->command = &cmd;
// 	return (execute_builtin2(av, shell, env_list));
// }

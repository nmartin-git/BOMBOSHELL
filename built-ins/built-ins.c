/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:25:03 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/14 19:00:33 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	fd_builtin(t_exec *exec)
{
	if (exec->next && exec->next->input > 2)
		close(exec->next->input);
	if (exec->input != STDIN_FILENO)
		close (exec->input);
	if (exec->output != STDOUT_FILENO)
	{
		dup2(exec->output, STDOUT_FILENO);
		close(exec->output);
	}
}

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

void	execute_builtin(t_env **env, char *cmd, t_exec *exec)
{
	t_shell	*command;

	command = set_t_shell(*env, cmd);
	fd_builtin(exec);
	if (ft_strncmp(command->command[0], "cd", 2) == 0)
		exit(ft_cd(command));
	else if (ft_strncmp(command->command[0], "echo", 4) == 0)
		exit(ft_echo(command));
	else if (ft_strncmp(command->command[0], "env", 3) == 0)
		exit(ft_env(*env));
	else if (ft_strncmp(command->command[0], "exit", 4) == 0)
		exit(ft_exit(command));
	else if (ft_strncmp(command->command[0], "export", 6) == 0)
		exit(ft_export(command, cmd));
	else if (ft_strncmp(command->command[0], "pwd", 3) == 0)
		exit(ft_pwd(command));
	else if (ft_strncmp(command->command[0], "unset", 5) == 0)
		exit(ft_unset(command));
	else
		exit(0);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:25:03 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/04 22:45:19 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

void	init_command(t_command *cmd, char **av)
{
	int	i;

	i = 0;
	cmd->argc = 0;
	cmd->next = NULL;
	while (av[i] && i < MAX_ARGS)
	{
		cmd->argv[i] = ft_strdup(av[i]);
		cmd->argc++;
		i++;
	}
	while (i < MAX_ARGS)
	{
		cmd->argv[i] = NULL;
		i++;
	}
}

int	execute_builtin2(char **av, t_shell *shell, t_env *env_list)
{
	if (ft_strncmp(av[0], "cd", 2) == 0)
		return (ft_cd(shell->command, shell));
	else if (ft_strncmp(av[0], "echo", 4) == 0)
		return (ft_echo(av, shell));
	else if (ft_strncmp(av[0], "env", 3) == 0)
		return (ft_env(env_list));
	else if (ft_strncmp(av[0], "exit", 4) == 0)
		return (ft_exit(av, shell));
	else if (ft_strncmp(av[0], "export", 6) == 0)
		return (ft_export(shell, shell->command));
	else if (ft_strncmp(av[0], "pwd", 3) == 0)
		return (ft_pwd(shell));
	else if (ft_strncmp(av[0], "unset", 5) == 0)
		return (ft_unset(shell, shell->command));
	else
		return (0);
	return (1);
}
int	is_built_in(char **av)
{
	if (ft_strncmp(av[0], "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(av[0], "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(av[0], "env", 3) == 0)
		return (1);
	else if (ft_strncmp(av[0], "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(av[0], "export", 6) == 0)
		return (1);
	else if (ft_strncmp(av[0], "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(av[0], "unset", 5) == 0)
		return (1);
	return (0);
}

int	execute_builtin(char **av, char **envp)
{
	static t_env	*env_list = NULL;
	static t_shell	*shell = NULL;
	t_command		cmd;

	if (!av || !envp)
		return (0);
	if (!env_list)
		env_list = init_env(envp);
	if (!shell)
	{
		shell = malloc(sizeof(t_shell));
		if (!shell)
			return (0);
		shell->env_vars = env_list;
		shell->current_dir = getcwd(NULL, 0);
		shell->command = NULL;
	}
	init_command(&cmd, av);
	shell->command = &cmd;
	return (execute_builtin2(av, shell, env_list));
}

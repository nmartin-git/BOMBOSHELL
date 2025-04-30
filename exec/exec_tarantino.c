/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tarantino.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:08:07 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/27 18:24:07 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_cmd_part1(t_input *arg_lst, t_env *env_chained, t_exec *exec)
{
	char	**env;
	char	**cmd;

	cmd = ft_split(arg_lst->arg, ' ');
	lsts_free(arg_lst->first);
	if (!cmd)
	{
		ft_printf_fd(2, "bomboshell: memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	env = env_to_array(env_chained);
	free_env(env_chained);
	if (!env)
	{
		ft_printf_fd(2, "bomboshell: memory allocation failed\n");
		(ft_free_tab(cmd), free_exec_lst(exec->first));
		exit(EXIT_FAILURE);
	}
	exec_cmd_part2(cmd, env, exec);
}

void	exec_cmd_part2(char **cmd, char **env, t_exec *exec)
{
	if (exec->next && exec->next->input > 2)
		close(exec->next->input);
	if (exec->input != STDIN_FILENO)
	{
		dup2(exec->input, STDIN_FILENO);
		close(exec->input);
	}
	if (exec->output != STDOUT_FILENO)
	{
		dup2(exec->output, STDOUT_FILENO);
		close(exec->output);
	}
	free_exec_lst(exec->first);
	if (!cmd[0] || cmd[0][0] == '\0')
	{
		ft_free_tab(cmd);
		ft_free_tab(env);
		ft_printf_fd(2, "\033[1m\033[31mPAS DE BOMBOLEAKS ICI\n\033[0m");
		exit(0);
	}
	exec_cmd_part3(cmd, env);
}

void	exec_cmd_part3(char **cmd, char **env)
{
	char	*env_set;

	if (!cmd[0] || cmd[0][0] == '\0')
	{
		ft_printf_fd(2, "bomboshell: command not found\n");
		ft_free_tab(env);
		exit(127);
	}
	env_set = exec_envset(env, cmd[0]);
	exec_cmd_part4(cmd, env, env_set);
}

void	exec_cmd_part4(char **cmd, char **env, char *env_set)
{
	struct stat	file_status;

	if (cmd[0][0] == '.' && cmd[0][1] == '\0')
	{
		ft_printf_fd(2, "bomboshell: .: filename argument required\n");
		ft_printf_fd(2, ".: usage: . filename [arguments]\n");
		free_cmd_fail(env, cmd, env_set, 2);
	}
	if (stat(env_set, &file_status) == 0 && S_ISDIR(file_status.st_mode)
		&& (ft_strchr(cmd[0], '/')))
	{
		ft_printf_fd(2, "bomboshell: %s: Is a directory\n", cmd[0]);
		free_cmd_fail(env, cmd, env_set, 126);
	}
	if (ft_strchr(cmd[0], '/') && access(env_set, F_OK) == 0 && access(env_set,
			X_OK) != 0)
	{
		ft_printf_fd(2, "bomboshell: %s: Permission denied\n", cmd[0]);
		free_cmd_fail(env, cmd, env_set, 126);
	}
	exec_cmd_part5(cmd, env, env_set);
}

void	exec_cmd_part5(char **cmd, char **env, char *env_set)
{
	if (cmd && cmd[0])
	{
		default_sig();
		execve(env_set, cmd, env);
		if (env_set[0] == '/' || (env_set[0] == '.' && env_set[1] == '/'))
		{
			ft_printf_fd(2, "bomboshell: %s: No such file or directory\n",
				cmd[0]);
		}
		else
			ft_printf_fd(2, "bomboshell: %s: command not found\n", cmd[0]);
	}
	g_exit_status = 127;
	if (env_set != cmd[0])
		free(env_set);
	ft_free_tab(cmd);
	ft_free_tab(env);
	exit(g_exit_status);
}

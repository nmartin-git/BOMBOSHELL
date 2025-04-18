/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:20:42 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/16 23:34:31 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_one_cmd(int dup_stdout)
{
	if (dup_stdout != -1)
	{
		dup2(dup_stdout, STDOUT_FILENO);
		close(dup_stdout);
	}
}

int	one_cmd_fds(t_exec *exec)
{
	int dup_stdout;

	if (exec->input != STDIN_FILENO)
		close(exec->input);
	if (exec->output != STDOUT_FILENO)
	{
		dup_stdout = dup(STDOUT_FILENO);
		dup2(exec->output, STDOUT_FILENO);
		close(exec->output);
	}
	else
		dup_stdout = -1;
	return (dup_stdout);
}

int	exec_one_cmd(t_env **env, char *cmd, t_exec *exec)
{
	t_shell	*command;
	int		exit_code;
	int		dup_stdout;

	exit_code = 0;
	command = set_t_shell(*env, cmd);
	dup_stdout = one_cmd_fds(exec);
	if (ft_strncmp(command->command[0], "cd", 2) == 0)
		exit_code = ft_cd(command);
	else if (ft_strncmp(command->command[0], "echo", 4) == 0)
		exit_code = ft_echo(command);
	else if (ft_strncmp(command->command[0], "env", 3) == 0)
		exit_code = ft_env(*env);
	else if (ft_strncmp(command->command[0], "exit", 4) == 0)
		exit_code = ft_exit(command);
	else if (ft_strncmp(command->command[0], "export", 6) == 0)
		exit_code = ft_export(command, cmd);
	else if (ft_strncmp(command->command[0], "pwd", 3) == 0)
		exit_code = ft_pwd(command);
	else if (ft_strncmp(command->command[0], "unset", 5) == 0)
		exit_code = ft_unset(command);
	close_one_cmd(dup_stdout);
	return (exit_code);
}

int	one_cmd(t_input *arg_lst, t_env **env, t_exec *exec_lst)
{
	t_input	*cmd;

	cmd = arg_lst;
	if (!exec_lst)
		return (0);
	exec_lst->pid_to_wait = 0;
	while (cmd && cmd->token != CMD)
		cmd = cmd->next;
	if (exec_lst->next || !cmd || cmd->token != CMD)
		return (0);
	if (is_built_in(cmd->arg, 0))
	{
		set_fds(arg_lst, exec_lst);
		/*TODO last_exit = */exec_one_cmd(env, cmd->arg, exec_lst);
		free_exec_lst(exec_lst);
		return (1);
	}
	else
		return (0);
}

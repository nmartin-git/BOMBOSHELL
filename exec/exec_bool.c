/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:57:56 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/21 19:47:25 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	next_bool(t_exec **exec_lst, t_input **files, int paranthesis, int exe)
{
	t_input	*tmp;
	int		order;

	if (*exec_lst && !exe)
		(*exec_lst)->pid = -1;
	if (*exec_lst)
	{
		order = (*exec_lst)->order;
		*exec_lst = (*exec_lst)->next;
	}
	else
		order = -1;
	while (*files && (*files)->token != PIPE && (*files)->token != BOOL)
	{
		// if ((*files)->token == CMD && *exec_lst)
		// 	(*exec_lst) = (*exec_lst)->next;
		*files = (*files)->next;
	}
	if (*files)
		*files = (*files)->next;
	tmp = *files;
	while (tmp && tmp->token != CMD && tmp->token != CMD_BOOL)
		tmp = tmp->next;
	// if (tmp && tmp->token == CMD)
	// 	next_bool(exec_lst, files, paranthesis);
	if (*exec_lst && (*exec_lst)->order != order)
		return ;
	if (*exec_lst && (*exec_lst)->paranthesis >= paranthesis && paranthesis > 0)
		next_bool(exec_lst, files, paranthesis, exe);
}

void	handle_bool_exec(t_input *cmd, t_input *file, t_exec *exec, t_env **env)
{
	int	pid;

	set_fds(file, exec, *env);
	default_sig();
	if (exec->input == -1 || exec->output == -1)
	{
		g_exit_status = 1;
		return (close_fds(exec));
	}
	ppx_exit(pid = fork(), "Fork failed", NULL, 1); // TODO gerer l'erreur
	if (pid != 0)
		exec->pid = pid;
	if (pid == 0)
	{
		if (exec->close_bool)
			close(exec->close_bool);
		default_sig();
		if (is_built_in(cmd->arg, 0))
			execute_builtin(env, cmd->arg, exec);
		else
			exec_cmd_part1(cmd, *env, exec);
	}
	if (exec->input > 2 && !(exec->next && exec->input == exec->next->input))
		close(exec->input);
	if (exec->output > 2 && !(exec->next && exec->output == exec->next->output))
		close(exec->output);
}

int	wait_bool(t_exec *exec)
{
	int	status;

	if (exec->prev && exec->prev->pid == -1)
	{
		while (exec->prev && exec->prev->pid == -1)
			exec = exec->prev;
	}
	if (!exec->prev || (exec->prev && !exec->prev->pid))
	{
		if (!exec->prev || exec->prev->exec_both)
			return (0);
		else
			return (1);
	}
	waitpid(exec->prev->pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	exec->prev->pid = 0;
	return (status);
}

void	exec_bool(t_exec *exec_lst, t_input *files, t_env **env)
{
	int		result;
	t_input	*tmp;

	tmp = files;
	while (files && files->token == SPACES)
		files = files->next;
	if (files && files->token == PARANTHESIS)
	{
		while (tmp && tmp->token != CMD_BOOL)
			tmp = tmp->next;
		handle_bool_exec(tmp, files, exec_lst, env);
		tmp = tmp->next;
		next_bool(&exec_lst, &files, 0, 1);
	}
	while (tmp)
	{
		if (tmp->token == CMD_BOOL)
		{
			if (!exec_lst)
				break ;
			result = wait_bool(exec_lst);
			if ((result && exec_lst->exec_both) || (!result
					&& !exec_lst->exec_both))
				next_bool(&exec_lst, &files, exec_lst->paranthesis, 0);
			else
			{
				handle_bool_exec(tmp, files, exec_lst, env);
				next_bool(&exec_lst, &files, 0, 1);
			}
		}
		else if (tmp->token == CMD)
			next_bool(&exec_lst, &files, 1, 1);
		if (tmp)
			tmp = tmp->next;
	}
}

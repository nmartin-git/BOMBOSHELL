/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:57:56 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/28 17:44:43 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	next_bool(t_exec **exec_lst, t_input **files, int paranthesis, int exe)
{
	t_input	*tmp;
	int		order;

	if (*exec_lst)
	{
		if (!exe)
			(*exec_lst)->pid = -1;
		close_bool(exec_lst);
		order = (*exec_lst)->order;
		*exec_lst = (*exec_lst)->next;
	}
	else
		order = -1;
	while (*files && (*files)->token != PIPE && (*files)->token != BOOL)
		*files = (*files)->next;
	if (*files)
		*files = (*files)->next;
	tmp = *files;
	while (tmp && tmp->token != CMD && tmp->token != CMD_BOOL)
		tmp = tmp->next;
	if (*exec_lst && (*exec_lst)->order != order)
		return ;
	if (*exec_lst && (*exec_lst)->paranthesis >= paranthesis && paranthesis > 0)
		next_bool(exec_lst, files, paranthesis, exe);
}

void	handle_bool_exec(t_input *cmd, t_input *file, t_exec *exec, t_env **env)
{
	int	pid;
	int	fd_pipe[2];

	set_fds(file, exec, *env, fd_pipe);
	if (exec->input == -1 || exec->output == -1)
		return (g_exit_status = 1, close_fds(exec));
	ppx_exit(pid = fork(), "Fork failed", NULL, 1);
	if (pid != 0)
		exec->pid = pid;
	if (pid == 0)
	{
		if (exec->next && exec->next->input > 2)
			close(exec->next->input);
		if (exec->input != STDIN_FILENO)
			(dup2(exec->input, STDIN_FILENO), close(exec->input));
		if (exec->output != STDOUT_FILENO)
			(dup2(exec->output, STDOUT_FILENO), close(exec->output));
		if (exec->close_bool)
			close (exec->close_bool);
		restore_signals();
		if (is_built_in(cmd->arg, 0))
			execute_builtin(env, cmd->arg, exec, cmd->first);
		else
			exec_cmd_part1(cmd, *env, exec);
	}
}

int	wait_bool(t_exec *exec, int is_both)
{
	int	status;
	is_both = 0;
	if (exec->prev && exec->prev->pid == -1)
	{
		while (exec->prev && exec->prev->pid == -1)
			exec = exec->prev;
	}
	if (!exec->prev || (exec->prev && exec->prev->pid < 1))
	{
		printf("?%d?\n", exec->prev->pid);
		if (exec->prev->pid == 0)
			return (0);
		else
			return (1);
	}
	waitpid(exec->prev->pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	if (WEXITSTATUS(status))
		exec->prev->pid = -2;
	else
		exec->prev->pid = 0;
	return (WEXITSTATUS(status));
}

void	bool_util(t_exec **exec, t_input **files, t_env **env, t_input **tmp)
{
	int		result;

	if (!exec || !*exec)
		return ;
	result = wait_bool(*exec, (*exec)->exec_both);
	printf("%s : result = %d exec_both = %d\n", (*tmp)->arg, result, (*exec)->exec_both);
	if ((result && (*exec)->exec_both)
		|| (!result && !(*exec)->exec_both))
	{
		if ((*exec)->prev
			&& (*exec)->prev->paranthesis == (*exec)->paranthesis
			&& (*exec)->prev->order == (*exec)->order)
			next_bool(exec, files, 0, 0);
		else
			next_bool(exec, files, (*exec)->paranthesis, 0);
	}
	else
	{
		handle_bool_exec(*tmp, *files, *exec, env);
		next_bool(exec, files, 0, 1);
	}
}

void	exec_bool(t_exec *exec_lst, t_input *files, t_env **env, t_input *tmp)
{
	t_input	*first;

	first = files;
	t_exec *exec_tmp= exec_lst;
	while (exec_tmp)
	{
		printf("[order = %d paranthesis = %d exec_both = %d] -> ", exec_tmp->order, exec_tmp->paranthesis, exec_tmp->exec_both);
		exec_tmp = exec_tmp->next;
	}
	printf("null\n");
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
	while (tmp && exec_lst)
	{
		tmp->first = first;
		if (tmp->token == CMD_BOOL)
			bool_util(&exec_lst, &files, env, &tmp);
		else if (tmp->token == CMD)
			next_bool(&exec_lst, &files, 1, 1);
		if (tmp)
			tmp = tmp->next;
	}
}

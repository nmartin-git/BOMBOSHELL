/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bool.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:57:56 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/20 22:52:30 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	next_bool(t_exec **exec_lst, t_input **files, int paranthesis)
{
	t_input	*tmp;

	if (*exec_lst)
		*exec_lst = (*exec_lst)->next;
	while (*files && (*files)->token != PIPE && (*files)->token != BOOL)
	{
		if ((*files)->token == CMD && *exec_lst)
			(*exec_lst) = (*exec_lst)->next;
		*files = (*files)->next;
	}
	if (*files)
		*files = (*files)->next;
	tmp = *files;
	while (tmp && tmp->token != CMD && tmp->token != CMD_BOOL)
		tmp = tmp->next;
	if (tmp && tmp->token == CMD)
		next_bool(exec_lst, files, paranthesis);
	if (paranthesis > 0 && (*exec_lst)->paranthesis == paranthesis)
		next_bool(exec_lst, files, paranthesis);
}

void	handle_bool_exec(t_input *cmd, t_input *file, t_exec *exec, t_env **env)
{
	int	pid;

	set_fds(file, exec, *env);
	default_sig();
	if (exec->input == -1 || exec->output == -1)
		return (close_fds(exec));
	ppx_exit(pid = fork(), "Fork failed", NULL, 1); // TODO gerer l'erreur
	if (pid != 0)
		exec->pid = pid;
	if (pid == 0)
	{
		default_sig();
		if (is_built_in(cmd->arg, 0))
			execute_builtin(env, cmd->arg, exec);
		else
			exec_cmd(cmd, *env, exec);
	}
	close_fds(exec);
}

int		wait_bool(t_exec *exec)
{
	int	status;

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
		next_bool(&exec_lst, &files, 0);
	while (tmp)
	{
		if (tmp->token == CMD_BOOL)
		{
			if (!exec_lst)
				break ;
			printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
			result = wait_bool(exec_lst);
			if ((result && exec_lst->exec_both)
				|| (!result && !exec_lst->exec_both))
				next_bool(&exec_lst, &files, exec_lst->paranthesis);
			else
				handle_bool_exec(tmp, files, exec_lst, env);
			next_bool(&exec_lst, &files, 0);
		}
		if (tmp)
			tmp = tmp->next;
	}
}

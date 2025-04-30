/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:07:27 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/30 19:12:55 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bomboshell.h"
#include "exec.h"

void	handle_exec(t_input *cmd, t_input *file, t_exec *exec_lst, t_env **env)
{
	int	pid;
	int	fd_pipe[2];

	set_fds(file, exec_lst, *env, fd_pipe);
	if (exec_lst->input == -1 || exec_lst->output == -1)
	{
		g_exit_status = 1;
		return (close_fds(exec_lst));
	}
	ppx_exit(pid = fork(), "Fork failed", NULL, 1);
	if (pid != 0)
		exec_lst->pid = pid;
	if (pid == 0)
	{
		if (exec_lst->close_bool > 2)
			close(exec_lst->close_bool);
		if (is_built_in(cmd->arg, 0))
			execute_builtin(env, cmd->arg, exec_lst, cmd->first);
		else
			exec_cmd_part1(cmd, *env, exec_lst);
	}
	close_fds(exec_lst);
}

void	replace_env_var(t_input *arg_lst, t_env *env, int i)
{
	char	*result;
	char	*expand;
	int		y;

	expand = NULL;
	y = 0;
	if (ft_isalpha(arg_lst->arg[i]) || arg_lst->arg[i] == '_')
		expand = get_env_var(&arg_lst->arg[i], env, &y);
	else
	{
		if (arg_lst->arg[i] == '?')
			expand = ft_itoa(g_exit_status);
		else if (arg_lst->arg[i] == '$')
			expand = ft_strdup("P.DIDDY");
		y++;
	}
	if (i > 1)
		result = ft_strjoin_free(ft_strndup(arg_lst->arg, i - 1), expand);
	else
		result = expand;
	if (arg_lst->arg[i + y])
		result = ft_strjoin_free(result, ft_strdup(&arg_lst->arg[i + y]));
	free(arg_lst->arg);
	arg_lst->arg = result;
}

void	expand_env_var(t_input *arg_lst, t_env *env, int i)
{
	while (arg_lst)
	{
		if (arg_lst->token == WORD || arg_lst->token == WORD_D_QUOTE
			|| arg_lst->token == INFILE || arg_lst->token == APPEND
			|| arg_lst->token == OUTFILE)
		{
			i = 0;
			while (arg_lst->arg[i])
			{
				while (arg_lst->arg[i] && arg_lst->arg[i] != '$')
					i++;
				if (arg_lst->arg[i] == '$')
				{
					if (ft_isalpha(arg_lst->arg[i + 1])
						|| arg_lst->arg[i + 1] == '?'
						|| arg_lst->arg[i + 1] == '_'
						|| arg_lst->arg[i + 1] == '$')
						replace_env_var(arg_lst, env, i + 1);
					else
						i++;
				}
			}
		}
		arg_lst = arg_lst->next;
	}
}

int	exec_preliminaires(t_input **arg, t_env **env, t_exec **exec, int *order)
{
	files_tokenisation(arg, NULL);
	expand_env_var(*arg, *env, 0);
	expand_wildcards_in_tokens(*arg);
	cmd_tokenisation(*arg);
	if (!paranthesis_parsing(arg, *arg, NULL))
	{
		*order = 2;
		return (2);
	}
	*exec = exec_init(*arg, NULL, NULL);
	if (one_cmd(*arg, env, *exec))
	{
		*order = 0;
		return (0);
	}
	*order = 0;
	(*arg)->first = *arg;
	return (1);
}

int	exec(t_input **arg_lst, t_env **env, t_exec *exec_lst, t_input *files)
{
	t_input	*tmp;
	t_exec	*exec_tmp;
	int		order;

	if (exec_preliminaires(arg_lst, env, &exec_lst, &order) != 1)
		return (order);
	files = *arg_lst;
	tmp = *arg_lst;
	exec_tmp = exec_lst;
	while (tmp)
	{
		if (tmp->token == CMD)
		{
			if (exec_tmp == exec_lst)
				skip_bool(&files, &exec_tmp, &tmp, &order);
			if (!suicide_squad(exec_tmp, &files, *arg_lst, tmp))
				break ;
			handle_exec(tmp, files, exec_tmp, env);
			next_cmd(&files, &exec_tmp, &tmp, &order);
		}
		if (tmp)
			tmp = tmp->next;
	}
	exec_bool(exec_lst, *arg_lst, env, *arg_lst);
	return (restore_signals(), exec_wait(exec_lst, exec_lst));
}

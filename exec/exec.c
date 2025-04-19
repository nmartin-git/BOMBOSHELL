/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:07:27 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/19 16:38:49 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bomboshell.h"
#include "exec.h"
#include "wildcard.h"
#include <stdio.h> //TODO supp

void	print_tokens(t_input *arg_lst) // TODO supp
{
	t_input *tmp;

	tmp = arg_lst;
	while (tmp)
	{
		if (tmp->token == HERE_DOC)
			printf("HERE_DOC -> ");
		else if (tmp->token == INFILE)
			printf("INFILE -> ");
		else if (tmp->token == OUTFILE)
			printf("OUTFILE -> ");
		else if (tmp->token == APPEND)
			printf("APPEND -> ");
		else if (tmp->token == CMD)
			printf("CMD -> ");
		else if (tmp->token == REDIR)
			printf("REDIR -> ");
		else if (tmp->token == PIPE)
			printf("PIPE -> ");
		else if (tmp->token == WORD)
			printf("WORD -> ");
		else if (tmp->token == WORD_D_QUOTE)
			printf("WORD_D_QUOTE -> ");
		else if (tmp->token == WORD_S_QUOTE)
			printf("WORD_S_QUOTE -> ");
		else if (tmp->token == SPACES)
			printf("SPACES -> ");
		else if (tmp->token == BOOL)
			printf("BOOL -> ");
		else if (tmp->token == PARANTHESIS)
			printf("PARANTHESIS -> ");
		else if (tmp->token == QUOTE)
			printf("QUOTE -> ");
		tmp = tmp->next;
	}
	printf("null\n");
} // TODO supp ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void	handle_exec(t_input *cmd, t_input *file, t_exec *exec_lst, t_env **env)
{
	int	status;
	int	pid;

	status = 0;
	set_fds(file, exec_lst, *env);
	default_sig();
	if (exec_lst->input == -1 || exec_lst->output == -1)
	{
		if (exec_lst->input > 2)
			close(exec_lst->input);
		else if (exec_lst->output > 2)
			close(exec_lst->output);
		return ;
	}
	ppx_exit(pid = fork(), "Fork failed", NULL, 1); // TODO gerer l'erreur
	if (pid != 0)
		exec_lst->pid = pid;
	if (pid == 0)
	{
		default_sig();
		if (is_built_in(cmd->arg, 0))
			execute_builtin(env, cmd->arg, exec_lst);
		else
			exec_cmd(cmd, *env, exec_lst);
	}
	if (exec_lst->input > 2)
		close(exec_lst->input);
	if (exec_lst->output > 2)
		close(exec_lst->output);
}

char	*get_env_var(char *arg, t_env *env, int *y)
{
	char	*var_name;
	char	*var_value;

	while (ft_isalnum(arg[*y]) || arg[*y] == '_')
		*y += 1;
	var_name = ft_strndup(arg, *y);
	var_value = ft_strdup(get_env_value(env, var_name));
	free(var_name);
	if (!var_value)
		var_value = ft_strdup("");
	return (var_value);
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
			expand = ft_itoa(getpid());
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

void	expand_env_var(t_input *arg_lst, t_env *env)
{
	int	i;

	while (arg_lst)
	{
		if (arg_lst->token == WORD || arg_lst->token == WORD_D_QUOTE)
		{
			i = 0;
			while (arg_lst->arg[i])
			{
				while (arg_lst->arg[i] && arg_lst->arg[i] != '$')
					i++;
				if (arg_lst->arg[i] == '$')
				{
					if (ft_isalpha(arg_lst->arg[i + 1]) || arg_lst->arg[i
						+ 1] == '?' || arg_lst->arg[i + 1] == '_')
						replace_env_var(arg_lst, env, i + 1);
					else
						i++;
				}
			}
		}
		arg_lst = arg_lst->next;
	}
}

int	exec(t_input **arg_lst, t_env **env, t_exec *exec_lst)
{
	t_input	*tmp;
	t_input	*files;
	t_exec	*exec_tmp;

	expand_env_var(*arg_lst, *env);
	expand_wildcards_in_tokens(*arg_lst);
	files_tokenisation(arg_lst, NULL);
	cmd_tokenisation(*arg_lst);
	if (!paranthesis_parsing(arg_lst, *arg_lst, NULL))
		return (2);
	tmp = *arg_lst;
	files = *arg_lst;
	exec_lst = exec_init(*arg_lst, NULL, NULL);
	if (one_cmd(*arg_lst, env, exec_lst))
		return (0);
	exec_tmp = exec_lst;
	// while (tmp)
	// {
	// 	printf("_%s_\n", tmp->arg);
	// 	tmp = tmp->next;
	// }
	// tmp = *arg_lst;
	while (tmp)
	{
		if (tmp->token == CMD)
		{
			if (files && files != *arg_lst)
				files = files->next;
			if (!files)
				break;
			handle_exec(tmp, files, exec_tmp, env);
			next_cmd(&files, &exec_tmp);
		}
		tmp = tmp->next;
	}
	restore_signals();
	return (exec_wait(exec_lst));
}

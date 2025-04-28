/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:24:54 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/27 17:57:03 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*get_var_value(char *str, int *i, t_env *env)
{
	char	*var_start;
	char	*var_name;
	char	*var_value;

	var_start = &str[*i + 1];
	while (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_')
		(*i)++;
	var_name = ft_strndup(var_start, &str[*i] - var_start + 1);
	var_value = get_env_value(env, var_name);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	return (ft_strdup(var_value));
}

static char	*append_char_to_result(char *result, char c)
{
	char	*single_char;
	char	*new_result;

	single_char = ft_strndup(&c, 1);
	new_result = ft_strjoin_free(result, single_char);
	return (new_result);
}

char	*expand_env_vars_in_str(char *str, t_env *env)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
			result = ft_strjoin_free(result, get_var_value(str, &i, env));
		else
			result = append_char_to_result(result, str[i]);
		i++;
	}
	free(str);
	return (result);
}

t_exec	*exec_utils(t_exec *exec_lst, t_exec *tmp)
{
	if (!exec_lst)
	{
		exec_lst = malloc(sizeof(t_exec));
		if (!exec_lst)
		{
			ft_printf_fd(2, "bomboshell: memory allocation failed\n");
			g_exit_status = 1;
			return (NULL);
		}
		exec_lst->prev = NULL;
		return (exec_lst);
	}
	else
	{
		tmp->next = malloc(sizeof(t_exec));
		if (!tmp->next)
		{
			ft_printf_fd(2, "bomboshell: memory allocation failed\n");
			g_exit_status = 1;
			free_exec_lst(exec_lst);
			return (NULL);
		}
		tmp->next->prev = tmp;
		return (tmp->next);
	}
}

t_exec	*exec_init(t_input *arg_lst, t_exec *exec_lst, t_exec *tmp)
{
	while (arg_lst)
	{
		if (arg_lst->token == CMD)
		{
			tmp = exec_utils(exec_lst, tmp);
			if (!tmp)
				return (NULL);
			if (!exec_lst)
				exec_lst = tmp;
			tmp->first = exec_lst;
			tmp->input = STDIN_FILENO;
			tmp->output = STDOUT_FILENO;
			tmp->paranthesis = 0;
			tmp->order = 0;
			tmp->pid = 0;
			tmp->exec_both = 1;
			tmp->close_bool = 0;
			tmp->empty = 0;
			tmp->next = NULL;
		}
		arg_lst = arg_lst->next;
	}
	return (exec_lst);
}

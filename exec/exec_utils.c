/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:24:54 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/20 22:16:11 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	bool_output(t_exec *exec_tmp, int output)
{
	int	paranthesis;

	paranthesis = exec_tmp->prev->paranthesis;
	while (exec_tmp->prev && exec_tmp->prev->paranthesis == paranthesis)
	{
		exec_tmp->prev->output = output;
		exec_tmp = exec_tmp->prev;
	}
}

void	skip_paranthesis(t_input **files, t_exec **exec_tmp, int p, int order)
{
	int		fd_pipe[2];

	while (*files && !((*files)->token == PARANTHESIS
		&& (*files)->arg[0] == ')'))
	{
		if (*exec_tmp && (*files)->token == CMD)
		{
			(*files)->token = CMD_BOOL;
			(*exec_tmp)->order = order;
			(*exec_tmp)->paranthesis = p;
			*exec_tmp = (*exec_tmp)->next;
		}
		if ((*exec_tmp) && *files && (*files)->token == BOOL)
		{
			if ((*files)->arg[0] == '&')
				(*exec_tmp)->exec_both = 1;
			else
				(*exec_tmp)->exec_both = 0;
		}
		*files = (*files)->next;
		if ((*files)->token == PARANTHESIS && (*files)->arg[0] == '(')
			skip_paranthesis(files, exec_tmp, p + 1, order);
	}
	*files = (*files)->next;
	while (*files && (*files)->token == SPACES)
			*files = (*files)->next;
	if ((*exec_tmp) && *files && (*files)->token == BOOL)
	{
		if ((*files)->arg[0] == '&')
			(*exec_tmp)->exec_both = 1;
		else
			(*exec_tmp)->exec_both = 0;
	}
	if (*files && (*files)->token == PIPE && *exec_tmp && p > 1)
	{
		ppx_exit(pipe(fd_pipe), "Failed opening the pipe", NULL, 1);//TODO gerer l'erreur
		(*exec_tmp)->input = fd_pipe[0];
		bool_output(*exec_tmp, fd_pipe[1]);
	}
}

void	skip_bool(t_input **files, t_exec **exec_tmp, t_input **tmp, int *ordr)
{
	int	fd_pipe[2];

	while (*files)
	{
		if (*files && (*files)->token == BOOL)
		{
			if ((*exec_tmp))
			{
				if (*exec_tmp && (*files)->arg[0] == '&')
					(*exec_tmp)->exec_both = 1;
				else if (*exec_tmp)
					(*exec_tmp)->exec_both = 0;
			}
			*files = (*files)->next;
			while (*files && (*files)->token == SPACES)
				*files = (*files)->next;
			if (*files && (*files)->token != PARANTHESIS)
			{
				while (*files && (*files)->token != BOOL)
				{
					if (*exec_tmp && (*files)->token == CMD)
					{
						(*files)->token = CMD_BOOL;
						*exec_tmp = (*exec_tmp)->next;
					}
					*files = (*files)->next;
				}
			}
		}
		else if (*files && (*files)->token == PARANTHESIS
			&& (*files)->arg[0] == '(')
		{
			*ordr += 1;
			skip_paranthesis(files, exec_tmp, 1, *ordr);
		}
		else
		{
			while (*files && (*files)->token == SPACES)
				*files = (*files)->next;
			printf("'%s'\n", (*files)->arg);
			if (*files && (*files)->token == PIPE
				&& *exec_tmp && (*exec_tmp)->next)
			{
				ppx_exit(pipe(fd_pipe), "Failed opening the pipe", NULL, 1);//TODO gerer l'erreur
				(*exec_tmp)->input = fd_pipe[0];
				bool_output(*exec_tmp, fd_pipe[1]);
			}
			if (tmp)
			{
				*tmp = *files;
				while (*tmp && (*tmp)->token != CMD)
					*tmp = (*tmp)->next;
			}
			if (!*files
				|| ((*files)->token != BOOL && (*files)->token != PARANTHESIS))
				break;
		}
	}
}

void	next_cmd(t_input **files, t_exec **exec_tmp, t_input **tmp, int *order)
{
	while (*files && (*files)->token != PIPE && (*files)->token != BOOL)
		*files = (*files)->next;
	if (*exec_tmp)
		*exec_tmp = (*exec_tmp)->next;
	if (*files && (*files)->token == BOOL)
	{
		if ((*exec_tmp) && *files && (*files)->token == BOOL)
		{
			if ((*files)->arg[0] == '&')
				(*exec_tmp)->exec_both = 1;
			else
				(*exec_tmp)->exec_both = 0;
		}
		skip_bool(files, exec_tmp, NULL, order);
	}
	*tmp = *files;
	
}

void	close_fds(t_exec *exec_lst)
{
	if (exec_lst->input > 2)
		close(exec_lst->input);
	if (exec_lst->output > 2)
		close(exec_lst->output);
}

int	count_valid_env_entries(t_env *env_list)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env_list;
	while (current)
	{
		if (current->value)
			count++;
		current = current->next;
	}
	return (count);
}

char	*create_env_string(char *key, char *value)
{
	int		count;
	char	*env_str;

	count = ft_strlen(key) + ft_strlen(value) + 2;
	env_str = (char *)malloc(sizeof(char) * count);
	if (!env_str)
		return (NULL);
	ft_strlcpy(env_str, key, ft_strlen(key) + 1);
	ft_strlcat(env_str, "=", ft_strlen(env_str) + 2);
	ft_strlcat(env_str, value, ft_strlen(env_str) + ft_strlen(value) + 1);
	return (env_str);
}

void	free_env_array(char **env_array, int count)
{
	while (--count >= 0)
		free(env_array[count]);
	free(env_array);
}

char	**env_to_array(t_env *env_list)
{
	int		count;
	t_env	*current;
	char	**env_array;
	int		i;

	count = count_valid_env_entries(env_list);
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		if (current->value)
		{
			env_array[i] = create_env_string(current->key, current->value);
			if (!env_array[i])
				return (free_env_array(env_array, i), NULL);
			i++;
		}
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

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
	free (str);
	return (result);
}

t_exec	*exec_init(t_input *arg_lst, t_exec *exec_lst, t_exec *tmp)
{
	while (arg_lst)
	{
		if (arg_lst->token == CMD)
		{
			if (!exec_lst)
			{
				exec_lst = malloc(sizeof(t_exec));
				if (!exec_lst)
					exit(127); // TODO gerer l'erreur
				tmp = exec_lst;
				tmp->prev = NULL;
			}
			else
			{
				tmp->next = malloc(sizeof(t_exec));
				if (!tmp->next)
					exit(127); // TODO gerer l'erreur
				tmp->next->prev = tmp;
				tmp = tmp->next;
			}
			tmp->input = STDIN_FILENO;
			tmp->output = STDOUT_FILENO;
			tmp->paranthesis = 0;
			tmp->order = 0;
			tmp->next = NULL;
		}
		arg_lst = arg_lst->next;
	}
	return (exec_lst);
}

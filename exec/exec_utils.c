/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:24:54 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/18 19:13:02 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	next_cmd(t_input **files, t_exec **exec_tmp)
{
	while (*files && (*files)->token != PIPE && (*files)->token != BOOL)
		*files = (*files)->next;
	if ((*exec_tmp)->next && *files && (*files)->token == BOOL)
	{
		(*exec_tmp)->next->pid_to_wait = (*exec_tmp)->pid;
		if ((*files)->arg[0] == '&')
			(*exec_tmp)->next->exec_both = 1;
		else
			(*exec_tmp)->next->exec_both = 0;
	}
	else if ((*exec_tmp)->next)
		(*exec_tmp)->next->pid_to_wait = 0;
	*exec_tmp = (*exec_tmp)->next;
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
	var_name = ft_strndup(var_start, &str[*i] - var_start);
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
			}
			else
			{
				tmp->next = malloc(sizeof(t_exec));
				if (!tmp->next)
					exit(127); // TODO gerer l'erreur
				tmp = tmp->next;
			}
			tmp->input = STDIN_FILENO;
			tmp->output = STDOUT_FILENO;
			tmp->next = NULL;
		}
		arg_lst = arg_lst->next;
	}
	return (exec_lst);
}

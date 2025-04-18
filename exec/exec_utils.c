/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:24:54 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/18 14:57:29 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	paranthesis_parsing(t_input **arg_lst)
{
	t_input	*tmp;
	t_input	*prev;

	prev = NULL;
	tmp = *arg_lst;
	while (tmp)
	{
		if (tmp->token == PARANTHESIS && prev
			&& (prev->token != PIPE || prev->token != BOOL))
		if (tmp->token != SPACES && tmp->token != PARANTHESIS)
			prev = tmp;
		tmp = tmp->next;
	}
}

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

char **env_to_array(t_env *env_list)
{
	int 	count;
	t_env	*current;
	char	**env_array;
	int		i;

	count = 0;
	current = env_list;
	while (current)
	{
		if (current->value)
			count++;
		current = current->next;
	}
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		if (current->value)
		{
			count = ft_strlen(current->key) + ft_strlen(current->value) + 2;
			env_array[i] = (char *)malloc(sizeof(char) * count);
			if (!env_array[i])
			{
				while (--i >= 0)
					free(env_array[i]);
				free(env_array);
				return (NULL);
			}
			ft_strlcpy(env_array[i], current->key, ft_strlen(current->key) + 1);
			ft_strlcat(env_array[i], "=", ft_strlen(env_array[i]) + 2);
			ft_strlcat(env_array[i], current->value,
				ft_strlen(env_array[i]) + ft_strlen(current->value)+ 1);
			i++;
		}
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

t_exec *exec_init(t_input *arg_lst, t_exec *exec_lst, t_exec *tmp)
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

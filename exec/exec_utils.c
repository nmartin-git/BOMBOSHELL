/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:24:54 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/09 15:34:04 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

char *exec_envset(char **env, char *cmd)
{
	int i;
	char **path;
	char *cmd_path;
	char *tmp;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i] || !cmd)
		return (cmd);
	path = ft_split(&env[i][5], ':');
	if (!path)
		return (cmd);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (ft_free_tab(path), cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_free_tab(path), cmd);
}

void exec_cmd(t_input *arg_lst, t_env *env_chained, t_exec *exec)
{
	char **env;
	char **cmd;
	char *env_set;

	env_set = NULL;
	exec = NULL;
	cmd = ft_split(arg_lst->arg, ' ');
	env = env_to_array(env_chained);
	// dup2(exec->input, STDIN_FILENO);
	// close(exec->input);
	// dup2(exec->output, STDOUT_FILENO);
	// close(exec->output);
	// env_set = exec_envset(env, cmd[0]);
	// if (cmd && cmd[0])
	// 	execve(env_set, cmd, env);
	// ft_printf_fd(2, "pipex : command not found : %s\n", cmd[0]);
	// if (env_set != cmd[0])
	// 	free(env_set);
	ft_free_tab(cmd);
	ft_free_tab(env);
	// exit(127); // TODO gerer l'erreur
}

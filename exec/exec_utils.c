/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:24:54 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/06 14:06:09 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_exec	*exec_init(t_input *arg_lst, t_exec *exec_lst)
{
	t_exec	*tmp;

	while (arg_lst)
	{
		if (arg_lst->token == CMD)
		{
			if (!exec_lst)
			{
				exec_lst = malloc(sizeof(t_exec));
				if (!exec_lst)
					exit (127);//TODO gerer l'erreur
				tmp = exec_lst;
			}
			else
			{
				tmp->next = malloc(sizeof(t_exec));
				if (!tmp->next)
					exit (127);//TODO gerer l'erreur
				tmp = tmp->next;
			}
			tmp->next = NULL;
		}
		arg_lst = arg_lst->next;
	}
	return (exec_lst);
}

char	*exec_envset(char **env, char *cmd)
{
	int		i;
	char	**path;
	char	*cmd_path;
	char	*tmp;

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

void    exec_cmd(t_input *arg_lst, int input, int output)
{
    char    **env = NULL;
    char	**cmd;
    char	*env_set;

	cmd = ft_split(arg_lst->arg, ' ');
    //env = env_in_tab;
	dup2(input, STDIN_FILENO);
	close(input);
	dup2(output, STDOUT_FILENO);
	close(output);
	env_set = exec_envset(env, cmd[0]);
	if (cmd && cmd[0])
		execve(env_set, cmd, env);
	ft_printf_fd(2, "pipex : command not found : %s\n", cmd[0]);
	if (env_set != cmd[0])
		free(env_set);
	ft_free_tab(cmd);
	ft_free_tab(env);
	exit(127);//TODO gerer l'erreur
}

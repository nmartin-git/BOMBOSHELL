/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:10:28 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/14 16:41:18 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_wait(t_exec *exec)
{
	int		status;
	t_exec	*tmp;

	while (exec)
	{
		waitpid(exec->pid, &status, 0);
		//last_exit_code = WEXITSTATUS(status) //TODO
		tmp = exec;
		exec = exec->next;
		free(tmp);
	}
	return (0);
}

void	ppx_exit(int err, const char *str, int *fd_pipe, int status)
{
	if (err == -1)
	{
		ft_printf_fd(2, "bomboshell : %s\n", str);
		if (fd_pipe)
		{
			close(fd_pipe[0]);
			close(fd_pipe[1]);
		}
		exit(status);
	}
}

int	ppx_cmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s2)
		return (0);
	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == 0 && (s2[i] == 0 || (s2[i] == '\n' && s2[i + 1] == 0)))
		return (1);
	return (0);
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
	cmd = ft_split(arg_lst->arg, ' ');
	env = env_to_array(env_chained);
	if (exec->next && exec->next->input > 2)
		close(exec->next->input);
	if (exec->input != STDIN_FILENO)
		(dup2(exec->input, STDIN_FILENO), close(exec->input));
	if (exec->output != STDOUT_FILENO)
		(dup2(exec->output, STDOUT_FILENO), close(exec->output));
	env_set = exec_envset(env, cmd[0]);
	if (cmd && cmd[0])
		execve(env_set, cmd, env);
	ft_printf_fd(2, "bomboshell : command not found : %s\n", cmd[0]);
	if (env_set != cmd[0])
		free(env_set);
	ft_free_tab(cmd);
	ft_free_tab(env);
	exit(127); // TODO gerer l'erreur
}

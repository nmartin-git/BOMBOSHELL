/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:10:28 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/26 19:40:53 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_cmd_fail(char **env, char **cmd, char *env_set, int error_exit)
{
	if (env_set != cmd[0])
		free(env_set);
	ft_free_tab(cmd);
	ft_free_tab(env);
	exit(error_exit);
}

int	exec_wait(t_exec *exec, t_exec *first)
{
	int	status;

	while (exec)
	{
		if (exec->pid > 0)
		{
			waitpid(exec->pid, &status, 0);
			if (WCOREDUMP(status))
			{
				write(2, "Quit (core dumped)\n", 19);
				g_exit_status = 131;
			}
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGPIPE && g_exit_status == 1)
					g_exit_status = 1;
				else
					g_exit_status = 128 + WTERMSIG(status);
			}
		}
		exec = exec->next;
	}
	return (free_exec_lst(first), g_exit_status);
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
		g_exit_status = status;
		exit(status);
	}
}

char	*exec_envset(char **env, char *cmd)
{
	int		i;
	char	**path;

	if (!cmd || cmd[0] == '\0')
		return (cmd);
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (cmd);
	path = ft_split(&env[i][5], ':');
	if (!path)
		return (cmd);
	return (exec_envset_part2(path, cmd));
}

char	*exec_envset_part2(char **path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*cmd_path;

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

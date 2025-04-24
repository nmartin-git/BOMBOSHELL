/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:10:28 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/21 16:38:23 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_wait(t_exec *exec)
{
	int		status;
	t_exec	*first;

	first = exec;
	while (exec)
	{
		if (exec->pid > 0)
		{
			waitpid(exec->pid, &status, 0);
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
	free_exec_lst(first);
	return (g_exit_status);
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

void	exec_cmd_part1(t_input *arg_lst, t_env *env_chained, t_exec *exec)
{
	char	**env;
	char	**cmd;

	cmd = ft_split(arg_lst->arg, ' ');
	if (!cmd)
	{
		ft_printf_fd(2, "bomboshell: memory allocation failed\n");
		exit(1);
	}
	if (!cmd[0] || cmd[0][0] == '\0')
	{
		// ft_printf_fd(2, "bomboshell: command not found\n");
		exit(0);
	}
	env = env_to_array(env_chained);
	if (!env)
	{
		ft_printf_fd(2, "bomboshell: memory allocation failed\n");
		ft_free_tab(cmd);
		exit(1);
	}
	exec_cmd_part2(cmd, env, exec);
}

void	exec_cmd_part2(char **cmd, char **env, t_exec *exec)
{
	if (exec->next && exec->next->input > 2)
		close(exec->next->input);
	if (exec->input != STDIN_FILENO)
	{
		dup2(exec->input, STDIN_FILENO);
		close(exec->input);
	}
	if (exec->output != STDOUT_FILENO)
	{
		dup2(exec->output, STDOUT_FILENO);
		close(exec->output);
	}
	exec_cmd_part3(cmd, env);
}

void	exec_cmd_part3(char **cmd, char **env)
{
	char	*env_set;

	if (!cmd[0] || cmd[0][0] == '\0')
	{
		ft_printf_fd(2, "bomboshell: command not found\n");
		exit(127);
	}
	env_set = exec_envset(env, cmd[0]);
	exec_cmd_part4(cmd, env, env_set);
}

void	exec_cmd_part4(char **cmd, char **env, char *env_set)
{
	struct stat	file_stat;

	if (stat(env_set, &file_stat) == 0 && S_ISDIR(file_stat.st_mode))
	{
		ft_printf_fd(2, "bomboshell: %s: Is a directory\n", cmd[0]);
		exit(126);
	}
	if (ft_strchr(cmd[0], '/') && access(env_set, F_OK) == 0 && access(env_set,
			X_OK) != 0)
	{
		ft_printf_fd(2, "bomboshell: %s: Permission denied\n", cmd[0]);
		exit(126);
	}
	if (cmd && cmd[0])
	{
		execve(env_set, cmd, env);
		if (env_set[0] == '/' || (env_set[0] == '.' && env_set[1] == '/'))
		{
			ft_printf_fd(2, "bomboshell: %s: No such file or directory\n",
				cmd[0]);
		}
		else
		{
			ft_printf_fd(2, "bomboshell: %s: command not found\n", cmd[0]);
		}
	}
	g_exit_status = 127;
	exit(g_exit_status);
}

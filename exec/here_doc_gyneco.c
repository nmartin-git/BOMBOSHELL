/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_gyneco.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:39:36 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/28 15:07:31 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	suicide_squad(t_exec *exec, t_input **files, t_input *arg, t_input *tmp)
{
	t_input	*check;

	check = arg;
	while (check
		&& check->token != CMD && check->token != PIPE && check->token != BOOL)
		check = check->next;
	if (check && check->token != CMD)
	{
		exec->empty = 1;
		*files = check;
	}
	if (!exec)
		return (0);
	if (*files && *files != arg)
		*files = (*files)->next;
	tmp->first = arg;
	(*files)->first = arg;
	return (1);
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

int	here_doc_exit(int pid, int fd_pipe[2])
{
	int	status;

	signal(SIGINT, SIG_IGN);
	close(fd_pipe[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		g_exit_status = 130;
		close(fd_pipe[0]);
		restore_signals();
		return (-1);
	}
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_exit_status = 130;
		close(fd_pipe[0]);
		restore_signals();
		return (-1);
	}
	restore_signals();
	return (fd_pipe[0]);
}

int	heredoc_end(char *str, char *arg, int fd, t_env *env)
{
	if (str == NULL)
	{
		close (fd);
		free_env(env);
		printf("bomboshell: ");
		printf("here-document delimited by end-of-file (wanted '%s')\n", arg);
		return (0);
	}
	return (1);
}

int	ppx_here_doc(t_input *arg, t_env *env, int quotes, t_exec *exec)
{
	int		fd_pipe[2];
	char	*str;
	int		pid;

	ppx_exit(pipe(fd_pipe), "Failed opening the pipe", NULL, 1);
	ppx_exit(pid = fork(), "Fork failed", fd_pipe, 1);
	if (pid == 0)
	{
		close(fd_pipe[0]);
		(default_sig(), setup_heredoc(), free_exec_lst(exec), ft_printf("> "));
		str = get_next_line(0);
		while (str != NULL && !ppx_cmp(arg->arg, str))
		{
			if (quotes)
				str = expand_env_vars_in_str(str, env);
			(ft_printf_fd(fd_pipe[1], "%s", str), free(str), ft_printf("> "));
			str = get_next_line(0);
		}
		if (!heredoc_end(str, arg->arg, fd_pipe[1], env))
			exit(130);
		else
			free(str);
		(close(fd_pipe[1]), free_env(env), lsts_free(arg), exit(0));
	}
	return (restore_signals(), here_doc_exit(pid, fd_pipe));
}

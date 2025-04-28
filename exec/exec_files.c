/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:35:53 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/27 18:07:48 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_fds(t_exec *exec_lst)
{
	if (exec_lst->input > 2)
		close(exec_lst->input);
	if (exec_lst->output > 2)
		close(exec_lst->output);
}

void	bool_output(t_exec *exec_tmp, int output, int input)
{
	int	paranthesis;
	int	order;

	order = exec_tmp->prev->paranthesis;
	paranthesis = exec_tmp->prev->paranthesis;
	while (exec_tmp->prev && exec_tmp->prev->paranthesis == paranthesis
		&& exec_tmp->prev->order == order)
	{
		exec_tmp->prev->output = output;
		exec_tmp->prev->close_bool = input;
		exec_tmp = exec_tmp->prev;
	}
}

int	fd_output(t_input *file, t_exec *exec)
{
	int	fd;

	if (exec->output > 2)
		close(exec->output);
	if (access(file->arg, F_OK) == 0 && access(file->arg, W_OK) == -1)
	{
		ft_printf_fd(2, "bomboshell: %s: %s\n", file->arg, strerror(13));
		return (-1);
	}
	if (file->token == OUTFILE)
		fd = open(file->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_printf_fd(2, "bomboshell : Failed oppening file : %s\n", file->arg);
	return (fd);
}

int	fd_input(t_input *file, t_exec *exec, t_env *env)
{
	int	fd;

	if (exec->input > 2)
		close(exec->input);
	if (file->token == HERE_DOC)
		return (ppx_here_doc(file, env, file->here_doc_s_or_d, exec->first));
	if (access(file->arg, F_OK) == -1)
	{
		ft_printf_fd(2, "bomboshell: %s: %s\n", file->arg, strerror(2));
		return (-1);
	}
	if (access(file->arg, R_OK) == -1)
	{
		ft_printf_fd(2, "bomboshell: %s: %s\n", file->arg, strerror(13));
		return (-1);
	}
	fd = open(file->arg, O_RDONLY);
	if (fd == -1)
	{
		ft_printf_fd(2, "bomboshell: Failed oppening file : %s\n", file->arg);
		return (-1);
	}
	return (fd);
}

void	set_fds(t_input *file, t_exec *exec, t_env *env, int *fd_pipe)
{
	while (file && exec->input != -1 && exec->output != -1)
	{
		if (file->token == INFILE || file->token == HERE_DOC)
			exec->input = fd_input(file, exec, env);
		else if (file->token == OUTFILE || file->token == APPEND)
			exec->output = fd_output(file, exec);
		else if ((exec->output == 1 && file->token == PIPE))
		{
			ppx_exit(pipe(fd_pipe), "Failed opening the pipe", NULL, 1);
			exec->next->input = fd_pipe[0];
			exec->output = fd_pipe[1];
		}
		if (!file->next || file->token == BOOL || file->token == PIPE)
		{
			if (exec->input == 0 && ((exec->prev && exec->prev->input == -1)
				|| exec->empty))
			{
				ppx_exit(pipe(fd_pipe), "Failed opening the pipe", NULL, 1);
				(close(fd_pipe[1]), exec->input = fd_pipe[0]);
			}
			return ;
		}
		file = file->next;
	}
}

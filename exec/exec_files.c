/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:35:53 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/18 18:25:42 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ppx_here_doc(t_input *arg)
{
	int		pid;
	int		fd_pipe[2];
	char	*str;

	str = NULL;
	ppx_exit(pipe(fd_pipe), "Failed opening the pipe", NULL, 1);//TODO gerer exit code
	ppx_exit(pid = fork(), "Fork failed", fd_pipe, 1);//TODO gerer exit code
	if (pid == 0)
	{
		close(fd_pipe[0]);
		while (!ppx_cmp(arg->arg, str))
		{
			if (str)
				ft_printf_fd(fd_pipe[1], "%s", str);
			free(str);
			ft_printf("> ");
			str = get_next_line(0);
		}
		free(str);
		close(fd_pipe[1]);
		exit(0);
	}
	close(fd_pipe[1]);
	waitpid(pid, 0, 0);
	return(fd_pipe[0]);
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

int	fd_input(t_input *file, t_exec *exec)
{
	int	fd;

	if (exec->input > 2)
		close(exec->input);
	if (file->token == HERE_DOC)
		return(ppx_here_doc(file));
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

void	set_fds(t_input *file, t_exec *exec)
{
	int	fd_pipe[2];
	
	while (file && exec->input != -1 && exec->output != -1)
	{
		if (file->token == INFILE || file->token == HERE_DOC)
			exec->input = fd_input(file, exec);
		else if (file->token == OUTFILE || file->token == APPEND)
			exec->output = fd_output(file, exec);
		else if (exec->output == STDOUT_FILENO && file->token == PIPE)
		{
			ppx_exit(pipe(fd_pipe), "Failed opening the pipe", NULL, 1);//TODO gerer l'erreur
			exec->next->input = fd_pipe[0];
			exec->output = fd_pipe[1];
		}
		if (!file->next || file->token == BOOL || file->token  == PIPE)
			return ;
		file = file->next;
	}
}

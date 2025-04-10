/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:53:26 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/10 22:02:46 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H
# include "parsing.h"
# include "built-ins.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

# define HERE_DOC 9
# define INFILE 10
# define OUTFILE 11
# define APPEND 12
# define CMD 13

typedef struct s_exec {
	int				pid;
	int				input;
	int				output;
	int				pid_to_wait;
	struct s_exec	*next;
}	t_exec;

void	handle_exec(t_input *cmd, t_input *files, t_exec *exec, t_env **env);
char	*get_env_var(char *arg, t_env *env, int *y);
void	replace_env_var(t_input *arg_lst, t_env *env, int i);
void	expand_env_var(t_input *arg_lst, t_env *env);
int		exec(t_input **arg_lst, t_env **env);


void	files_tokenisation(t_input **arg_lst, t_input *prev);
void	export_parsing_utils(t_input* arg_lst);
void	export_parsing(t_input *arg_lst);
void	cmd_tokenisation(t_input *arg_lst);

t_input	*del_redir(t_input **arg_lst, t_input *tmp, t_input *prev);
void	del_spaces(t_input *tmp);
char 	**env_to_array(t_env *env_list);
t_exec	*exec_init(t_input *arg_lst, t_exec *exec_lst, t_exec *tmp);

void	exec_wait(t_exec *exec);
void	ppx_exit(int err, const char *str, int *fd_pipe, int status);
int		ppx_cmp(const char *s1, const char *s2);
char	*exec_envset(char **env, char *cmd);
void    exec_cmd(t_input *arg_lst, t_env *env, t_exec *exec);

int		ppx_here_doc(t_input *arg);
int		fd_output(t_input *file);
int		fd_input(t_input *file);
void	set_fds(t_input *file, t_exec *exec);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:53:26 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/16 21:11:04 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H
# include "parsing.h"
# include "builtins.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

# define HERE_DOC 9
# define INFILE 10
# define OUTFILE 11
# define APPEND 12
# define CMD 13

void print_tokens(t_input *arg_lst); //TODO supp

void	handle_exec(t_input *cmd, t_input *files, t_exec *exec, t_env **env);
char	*get_env_var(char *arg, t_env *env, int *y);
void	replace_env_var(t_input *arg_lst, t_env *env, int i);
void	expand_env_var(t_input *arg_lst, t_env *env);
int		exec(t_input **arg_lst, t_env **env, t_exec *exec_lst);

t_input	*del_redir(t_input **arg_lst, t_input *tmp, t_input *prev);
void	del_spaces(t_input *tmp);
void	files_tokenisation(t_input **arg_lst, t_input *prev);
void	cmd_word_order(t_input *arg, t_input *del, t_input *cmd, t_input *pre);
void	cmd_tokenisation(t_input *arg_lst);

void	next_cmd(t_input **files, t_exec **exec_tmp);
char 	**env_to_array(t_env *env_list);
t_exec	*exec_init(t_input *arg_lst, t_exec *exec_lst, t_exec *tmp);

int		exec_wait(t_exec *exec);
void	ppx_exit(int err, const char *str, int *fd_pipe, int status);
int		ppx_cmp(const char *s1, const char *s2);
char	*exec_envset(char **env, char *cmd);
void    exec_cmd(t_input *arg_lst, t_env *env, t_exec *exec);

int		export_parsing_utils(t_input *arg_lst, t_input *first);
void	export_quotes(t_input *arg_lst, int i);
void	export_get_arg(t_input *arg_lst, int i, int	quotes);
void	export_parsing(t_input *arg_lst);

int		ppx_here_doc(t_input *arg);
int		fd_output(t_input *file, t_exec *exec);
int		fd_input(t_input *file, t_exec *exec);
void	set_fds(t_input *file, t_exec *exec);

void	free_exec_lst(t_exec *exec_lst);
void	close_one_cmd(int dup_stdout);
int		one_cmd_fds(t_exec *exec);
int		exec_one_cmd(t_env **env, char *cmd, t_exec *exec);
int		one_cmd(t_input *arg_lst, t_env **env, t_exec *exec_lst);

#endif
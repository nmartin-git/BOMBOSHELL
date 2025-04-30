/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:53:26 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/30 15:19:43 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H
# include "bombosignal.h"
# include "builtins.h"
# include "parsing.h"
# include "wildcard.h"
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

# define HERE_DOC 9
# define INFILE 10
# define OUTFILE 11
# define APPEND 12
# define CMD 13
# define CMD_BOOL 14

void	exec_nbr(t_exec *exec);//TODO supp

void	skip_bool(t_input **files, t_exec **exec_tmp, t_input **tmp, int *ord);
void	free_cmd_fail(char **env, char **cmd, char *env_set, int error_exit);
void	bool_output(t_exec *exec_tmp, int output, int input);

void	skip_paranthesis_utils(t_input **files, t_exec **exec_tmp, int p);

void	handle_exec(t_input *cmd, t_input *files, t_exec *exec, t_env **env);
char	*get_env_var(char *arg, t_env *env, int *y);
void	replace_env_var(t_input *arg_lst, t_env *env, int i);
void	expand_env_var(t_input *arg_lst, t_env *env, int i);
int		exec_preliminaires(t_input **a, t_env **ev, t_exec **ex, int *order);
int		exec(t_input **arg_lst, t_env **env, t_exec *exec_lst, t_input *files);

t_input	*del_redir(t_input **arg_lst, t_input *tmp, t_input *prev);
void	del_spaces(t_input *tmp);
void	files_tokenisation(t_input **arg_lst, t_input *prev);
void	cmd_word_order(t_input *arg, t_input *del, t_input *cmd, t_input *pre);
void	cmd_tokenisation(t_input *arg_lst);

void	del_paranthesis(t_input **arg_lst, t_input *del, t_input *prev);
int		paranthesis_bool(t_input **arg_lst, t_input *tmp, t_input *pre, int i);
int		paranthesis_parsing(t_input **arg_lst, t_input *tmp, t_input *prev);

void	next_cmd(t_input **files, t_exec **exec_tmp, t_input **tmp, int *ordr);
char	**env_to_array(t_env *env_list);
t_exec	*exec_init(t_input *arg_lst, t_exec *exec_lst, t_exec *tmp);

int		exec_wait(t_exec *exec, t_exec *first);
void	ppx_exit(int err, const char *str, int *fd_pipe, int status);
int		ppx_cmp(const char *s1, const char *s2);
char	*exec_envset(char **env, char *cmd);
char	*exec_envset_part2(char **path, char *cmd);

void	exec_cmd_part1(t_input *arg_lst, t_env *env_chained, t_exec *exec);
void	exec_cmd_part2(char **cmd, char **env, t_exec *exec);
void	exec_cmd_part3(char **cmd, char **env);
void	exec_cmd_part4(char **cmd, char **env, char *env_set);
void	exec_cmd_part5(char **cmd, char **env, char *env_set);

int		export_parsing_utils(t_input *arg_lst, t_input *first);
void	export_quotes(t_input *arg_lst, int i);
void	export_get_arg(t_input *arg_lst, int i, int quotes);
void	export_parsing(t_input *arg_lst);

int		here_doc_exit(int pid, int fd_pipe[2]);
int		ppx_here_doc(t_input *arg, t_env *env, int quotes, t_exec *exec);
int		fd_output(t_input *file, t_exec *exec);
int		fd_input(t_input *file, t_exec *exec, t_env *env);
void	set_fds(t_input *file, t_exec *exec, t_env *env, int *fd_pipe);

void	free_exec_lst(t_exec *exec_lst);
void	close_one_cmd(int dup_stdout);
int		one_cmd_fds(t_exec *exec);
int		exec_one_cmd(t_env **env, char *cmd, t_exec *exec, t_input *arg_lst);
int		one_cmd(t_input *arg_lst, t_env **env, t_exec *exec_lst);

void	close_fds(t_exec *exec_lst);
int		count_valid_env_entries(t_env *env_list);
char	*create_env_string(char *key, char *value);
void	free_env_array(char **env_array, int count);

char	*expand_env_vars_in_str(char *str, t_env *env);
t_input	*diddy_shortcut(t_input **arg_lst);
int		suicide_squad(t_exec *exec, t_input **files, t_input *arg, t_input *t);

void	skip_paranthesis(t_input **files, t_exec **exec_tmp, int p, int order);

void	close_bool(t_exec **exec_lst);
void	skip_boolgauche(t_input **files, t_exec **exec_tmp);
int		skip_booldroite(t_input **files, t_exec **exec_tmp, t_input **tmp);

void	expand_wildcards_in_tokens(t_input *arg_lst);
void	replace_token_arg(t_input *tmp, char **expanded);
void	free_expanded_array(char **expanded);
t_input	*add_remaining_tokens(t_input *tmp, char **expanded, int token);

void	next_bool(t_exec **exec_lst, t_input **files, int paranthesis, int ex);
void	handle_bool_exec(t_input *cmd, t_input *file, t_exec *ex, t_env **env);
void	exec_bool(t_exec *exec_lst, t_input *files, t_env **env, t_input *tmp);

#endif
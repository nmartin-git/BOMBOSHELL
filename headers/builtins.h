/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:57:14 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/28 15:08:07 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minisignal.h"
# include "parsing.h"
# include "libft.h"
# include <limits.h>
# include <stdio.h>
# include <sys/wait.h>

# define PATH_MAX_ANANAS 4096

// liste env
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

// list all
typedef struct s_shell
{
	t_env			*env_vars;
	char			*current_dir;
	int				last_exit_status;
	char			**command;
}					t_shell;

typedef struct s_exec
{
	int				pid;
	int				input;
	int				output;
	int				close_bool;
	int				exec_both;
	int				paranthesis;
	int				order;
	int				empty;
	struct s_exec	*prev;
	struct s_exec	*next;
	struct s_exec	*first;
}					t_exec;

void				free_exec_lst(t_exec *exec_lst);
void				free_t_shell(t_shell *command);
void				fd_builtin(t_exec *exec);
t_shell				*set_t_shell(t_env *env, char *cmd);
void				execute_builtin(t_env **e, char *c, t_exec *x, t_input *a);
t_env				*init_env(char **envp);

// builtin
int					ft_cd(t_shell *shell);
int					ft_pwd(t_shell *shell);
int					ft_exit(t_shell *s, t_env *env, t_input *arg, t_exec *exe);
int					ft_env(t_env *list);
int					ft_unset(t_shell *shell);
int					ft_export(t_shell *shell, char *str);
int					ft_echo(t_shell *shell, char *s);
void				shlvl(t_env *env);
int					size_six(char *cmd, int i);

// builtin utils
char				*get_env_value(t_env *env, char *key);
void				set_env_value(t_env *env, char *key, char *value);
t_env				*new_env(char *key, char *value);
void				add_env(t_env **env_list, t_env *new);
void				free_env(t_env *env);
void				unset_env_value(t_env *env, char *key);
int					ft_strcmp(const char *s1, const char *s2);
void				print_echo(char **av, int i, t_shell *shell);
int					is_valid_identifier(char *str);
char				*handle_shell_var(t_env *env, char *var, char *cmd);
char				*trim_quotes(char *value);
int					print_invalid_id_error(char *arg, char *var);
char				**split_boosted(char **command);
long				ft_atol(const char *str);
int					is_built_in(char *cmd, int i);
int					handle_export_arg(t_env *env, char *cmd);
int					handle_export_with_value(t_env *env, char *cmd,
						char *equals);
int					handle_export_no_equals(t_env *env, char *cmd);

#endif
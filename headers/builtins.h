/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:57:14 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/16 22:04:58 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <limits.h>
# include <sys/wait.h>
# include "libft.h"

# define PATH_MAX_ANANAS 4096

// liste env
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

// list all
typedef struct s_shell
{
	t_env				*env_vars;
	char				*current_dir;
	int					last_exit_status;
	char				**command;
}						t_shell;

typedef struct s_exec {
	int				pid;
	int				input;
	int				output;
	int				pid_to_wait;
	int				exec_both;
	struct s_exec	*first;
	struct s_exec	*next;
}	t_exec;

void					free_exec_lst(t_exec *exec_lst);
void					fd_builtin(t_exec *exec);
t_shell					*set_t_shell(t_env *env, char *cmd);
void					execute_builtin(t_env **env, char *cmd, t_exec *exec);
t_env					*init_env(char **envp);

// builtin
int						ft_cd(t_shell *shell);
int						ft_pwd(t_shell *shell);
int						ft_exit(t_shell *shell);
int						ft_env(t_env *list);
int						ft_unset(t_shell *shell);
int						ft_export(t_shell *shell, char *str);
int						ft_echo(t_shell *shell);

// builtin utils
char					*get_env_value(t_env *env, char *key);
void					set_env_value(t_env *env, char *key, char *value);
t_env					*new_env(char *key, char *value);
void					add_env(t_env **env_list, t_env *new);
void					free_env(t_env *env);
void					unset_env_value(t_env *env, char *key);
int						is_built_in(char *cmd, int i);
int						ft_strcmp(const char *s1, const char *s2);
void					print_echo(char **av, int i, t_shell *shell);
int						is_valid_identifier(char *str);
char					*handle_shell_var(t_env *env, char *var, char *cmd);

#endif
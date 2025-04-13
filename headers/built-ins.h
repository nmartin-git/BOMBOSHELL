/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomboshell.h                                       :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   */
/*   Created: 2025/03/13 19:10:53 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/13 19:22:46 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_INS_H
# define BUILT_INS_H

# include "libft.h"
# include <limits.h>
# include <stdio.h>

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

void				execute_builtin(t_env **env, char *cmd);
t_env				*init_env(char **envp);

// builtin
int						ft_cd(t_shell *shell);
int						ft_pwd(t_shell *shell);
int						ft_exit(t_shell *shell);
int						ft_env(t_env *list);
int						ft_unset(t_shell *shell);
int						ft_export(t_shell *shell, char *str);
int						ft_echo(t_shell *shell);

// builtin utils
char				*get_env_value(t_env *env, char *key);
void				set_env_value(t_env *env, char *key, char *value);
t_env				*new_env(char *key, char *value);
void				add_env(t_env **env_list, t_env *new);
void				free_env(t_env *env);
int					unset_env_value(t_env *env, char *key);
int					is_built_in(char *cmd, int i);
int					ft_strcmp(const char *s1, const char *s2);
void				print_echo(char **av, int i, t_shell *shell);
int					is_valid_identifier(char *str);
char				*handle_shell_var(t_env *env, char *var, char *cmd);
int					print_invalid_id_error(char *arg, char *var);

#endif
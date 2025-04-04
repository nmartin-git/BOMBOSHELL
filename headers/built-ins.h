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

#ifndef BUILT-INS_H
# define BUILT-INS_H
# define PATH_MAX 5000
# define MAX_ARGS 20

# include "libft.h"

// liste env
typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;
// list cmd
typedef struct s_command
{
	char				*argv[MAX_ARGS];
	int					argc;
	struct s_command	*next;
}						t_command;
// list all
typedef struct s_shell
{
	t_env				*env_vars;
	char				*current_dir;
	int					last_exit_status;
	int					in_child;
	t_command			*command;
}						t_shell;

// builtin
int						ft_pwd(t_shell *shell);
int						ft_exit(char **av, t_shell *shell);
int						ft_env(t_env *list);
int						ft_cd(t_command *cmd, t_shell *shell);
int						ft_unset(t_shell *shell, t_command *cmd);
int						ft_export(t_shell *shell, t_command *cmd);
int						ft_echo(char **av, t_shell *shell);

// builtin utils
char					*get_env_value(t_env *env, char *key);
void					set_env_value(t_env *env, char *key, char *value);
t_env					*new_env(char *key, char *value);
void					add_env(t_env **env_list, t_env *new);
void					free_env(t_env *env);
void					unset_env_value(t_env *env, char *key);
int						is_built_in(char **av);
int						ft_strcmp(const char *s1, const char *s2);
void					print_echo(char **av, int i, t_shell *shell);
int						is_valid_identifier(char *str);
char					*handle_shell_var(t_env *env, char *var, char *cmd);

#endif
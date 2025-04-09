/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:53:26 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/09 15:34:36 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H
# include "parsing.h"
# include "built-ins.h"
# include <fcntl.h>

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

t_input	*del_redir(t_input **arg_lst, t_input *tmp, t_input *prev);
void	del_spaces(t_input *tmp);
void	files_tokenisation(t_input **arg_lst, t_input *prev);
void	cmd_tokenisation(t_input *arg_lst);

t_exec	*exec_init(t_input *arg_lst, t_exec *exec_lst, t_exec *tmp);
char	*exec_envset(char **env, char *cmd);
void    exec_cmd(t_input *arg_lst, t_env *env, t_exec *exec);

#endif
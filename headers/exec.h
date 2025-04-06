/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:53:26 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/06 14:55:37 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H
# include "parsing.h"
# include "built-ins.h"

# define HERE_DOC 9
# define INFILE 10
# define OUTFILE 11
# define APPEND 12
# define CMD 13

typedef struct s_exec {
	int				pid;
	int				input;
	int				output;
	int				*pipe;
	struct s_exec	*next;
}	t_exec;

int		exec(t_input **arg_lst, t_env **env);

t_input	*del_redir(t_input **arg_lst, t_input *tmp, t_input *prev);
void	del_spaces(t_input *tmp);
void	files_tokenisation(t_input **arg_lst, t_input *prev);
void	cmd_tokenisation(t_input *arg_lst);

t_exec	*exec_init(t_input *arg_lst, t_exec *exec_lst);
char	*exec_envset(char **env, char *cmd);
void    exec_cmd(t_input *arg_lst, int input, int output);

#endif
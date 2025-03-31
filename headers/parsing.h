/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:27:48 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/31 17:51:51 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

# define SPACES 0
# define PIPE 1
# define REDIR 2
# define WORD 3
# define BOOL 4
# define PARANTHESIS 5
# define QUOTE 6
# define WORD_S_QUOTE 7
# define WORD_D_QUOTE 8

typedef struct s_input {
	int				token;
	char			*arg;
	struct s_input	*next;
}	t_input;

int		get_prev_token(t_input *lst, t_input *arg);
int		get_next_token(t_input *arg);
void	token_add(t_input **token_lst, int token);
int		token_get(char *input, int *i);
t_input	*tokenisation(char *input);

int		arg_len(char *input);
char	*arg_get(char *input, int *i);
t_input	*input_set(char *input, t_input **arg_lst);

int		parse_check(int prev, int next, t_input *arg_lst);
void	free_arg(t_input *arg);
int		ignore_spaces(char *str);
void	lsts_free(t_input *arg_lst);
void	parsing_exit(t_input *arg_lst);

void	del_last_quote(int del, t_input **arg_lst);
void	get_last_quote(char quote, t_input **arg_lst);
void	unclosed_check(t_input **arg_lst);
void	del_quotes(t_input *prev, t_input *unified, t_input **arg_lst);
void	unify(char quote, t_input *tmp, t_input *prev, t_input **arg_lst);

int		paranthesis_check(t_input *arg_lst);
int		quotes_unify(t_input *tmp, t_input *prev, t_input **arg_lst);
int		lsts_simplify(t_input **arg_lst);
int		token_parse(t_input *arg_lst);
int		parsing(char *input, t_input **arg_lst);

#endif
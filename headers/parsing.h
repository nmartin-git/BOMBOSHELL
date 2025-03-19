/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:27:48 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/19 16:37:08 by nmartin          ###   ########.fr       */
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

typedef struct s_input {
	int				token;
	char			*arg;
	struct s_input	*next;
}	t_input;

void	token_add(t_input **token_lst, int token);
int		token_get(char *input, int *i);
t_input	*tokenisation(char *input);

int		arg_len(char *input);
char	*arg_get(char *input, int *i);
t_input	*input_set(char *input);

void	ignore_spaces(char *str, int *i);
void	lsts_free(t_input *arg_lst);

void	del_last_quote(char quote, t_input **arg_lst);
int		lsts_simplify(t_input **arg_lst);
int		token_parse(t_input *arg_lst);
int		parsing(char *input);


#endif
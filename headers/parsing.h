/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:27:48 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/16 18:31:58 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include "libft.h"
# define SPACES 0
# define PIPE 1
# define REDIR 2
# define WORD 3
# define BOOL 4
# define PARANTHESIS 5

typedef struct s_token {
	int				token;
	struct s_token	*next;
}	t_token;

typedef struct s_input {
	char			*arg;
	struct s_input	*next;
}	t_input;

void	token_add(t_token **token_lst, int token);
int		token_get(char *input, int *i);
void	token_parse(t_token *token_lst);
t_token	*tokenisation(char *input);

int		arg_len(char *input);
char	*arg_get(char *input, int *i);
void	arg_add(t_input **arg_lst, char *arg);
t_input	*input_set(char *input);

void	ignore_spaces(char *str, int *i);
int		parsing(char *input);

#endif
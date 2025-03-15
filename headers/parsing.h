/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:27:48 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/15 18:05:55 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# define SPACE 0
# define PIPE 1
# define REDIR 2
# define WORD 3
# define BOOL 4
# define PARANTHESIS 5

typedef struct s_token {
	int				token;
	struct s_token	*next;
}	t_token;

void		token_add(t_token *token_lst, int token);
t_token	*tokenisation(char *input);

void	ignore_spaces(char *str, int *i);
int		parsing(char *input);

#endif
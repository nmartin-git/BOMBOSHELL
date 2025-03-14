/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:27:48 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/14 13:55:30 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define WORD 1
# define REDIR 2
# define PIPE 3

typedef struct s_token {
	int				token;
	struct s_token	*next;
}	t_token;

int		parsing(char *input);

#endif
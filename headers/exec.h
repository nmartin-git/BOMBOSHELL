/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:53:26 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/30 18:05:32 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H

# define EXEC_H
# include "parsing.h"

# define HERE_DOC 9
# define INFILE 10
# define OUTFILE 11
# define APPEND 12
# define CMD 13

int		exec(t_input **arg_lst);

void	files_tokenisation(t_input **arg_lst, t_input *prev);

#endif
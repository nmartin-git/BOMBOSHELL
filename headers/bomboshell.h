/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomboshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:10:53 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/14 18:58:48 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOMBOSHELL_H
# define BOMBOSHELL_H

# include "builtins.h"
# include "exec.h"
# include "libft.h"
# include "parsing.h"
# include "wildcard.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <termios.h>
# include <unistd.h>

extern int	g_exit_status;

int			only_space(char *str);
void		default_sig(void);
void		prompt_sig(void);
void		handle_here_doc(int sig);
void		restore_signals(void);

#endif
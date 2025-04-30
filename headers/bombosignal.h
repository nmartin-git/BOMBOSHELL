/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bombosignal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:26:38 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/26 22:07:46 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOMBOSIGNAL_H

# define BOMBOSIGNAL_H
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
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern int	g_exit_status;

void		default_sig(void);
void		handle_here_doc(int sig);
void		restore_signals(void);
void		setup_heredoc(void);
void		handle_sigint(int sig);

#endif
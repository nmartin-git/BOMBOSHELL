/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomboshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:10:53 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/14 13:56:23 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOMBOSHELL_H
# define BOMBOSHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "libft.h"
# include "parsing.h"

int	only_space(char *str);

#endif
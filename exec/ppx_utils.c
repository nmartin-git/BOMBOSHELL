/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:10:28 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/08 19:19:25 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ppx_exit(int err, const char *str, int *fd_pipe, int status)
{
	if (err == -1)
	{
		ft_printf_fd(2, "bomboshell : %s\n", str);
		if (fd_pipe)
		{
			close(fd_pipe[0]);
			close(fd_pipe[1]);
		}
		exit(status);
	}
}

int	ppx_cmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s2)
		return (0);
	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == 0 && (s2[i] == 0 || (s2[i] == '\n' && s2[i + 1] == 0)))
		return (1);
	return (0);
}


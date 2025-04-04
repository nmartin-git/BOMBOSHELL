/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:36:14 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/04 22:42:57 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	ft_pwd(t_shell *shell)
{
	if (getcwd(shell->current_dir, PATH_MAX) == NULL)
	{
		perror("pwd error\n");
		return (0);
	}
	printf("%s\n", shell->current_dir);
	free(shell->current_dir);
	return (1);
}

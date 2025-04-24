/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:36:14 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/20 21:06:43 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_shell *cmd)
{
	if (getcwd(cmd->current_dir, PATH_MAX_ANANAS) == NULL)
	{
		perror("pwd error\n");
		return (1);
	}
	printf("%s\n", cmd->current_dir);
	return (0);
}

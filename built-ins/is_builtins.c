/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atazzit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 11:57:59 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/26 11:58:00 by atazzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	size_four(char *cmd, int i)
{
	return (!cmd[i + 4] || cmd[i + 4] == ' ');
}

int	size_two(char *cmd, int i)
{
	return ((!cmd[i + 2] || cmd[i + 2] == ' '));
}

int	size_three(char *cmd, int i)
{
	return ((!cmd[i + 3] || cmd[i + 3] == ' '));
}

int	size_five(char *cmd, int i)
{
	return ((!cmd[i + 5] || cmd[i + 5] == ' '));
}

int	is_built_in(char *cmd, int i)
{
	while (cmd[i] == ' ')
		i++;
	if (ft_strncmp(&cmd[i], "cd", 2) == 0 && size_two(cmd, i))
		return (1);
	else if (ft_strncmp(&cmd[i], "echo", 4) == 0 && size_four(cmd, i))
		return (1);
	else if (ft_strncmp(&cmd[i], "env", 3) == 0 && size_three(cmd, i))
		return (1);
	else if (ft_strncmp(&cmd[i], "exit", 4) == 0 && size_four(cmd, i))
		return (1);
	else if (ft_strncmp(&cmd[i], "export", 6) == 0 && size_six(cmd, i))
		return (1);
	else if (ft_strncmp(&cmd[i], "pwd", 3) == 0 && size_three(cmd, i))
		return (1);
	else if (ft_strncmp(&cmd[i], "unset", 5) == 0 && size_five(cmd, i))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:17:52 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/20 18:25:00 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	skip_whitespace_and_echo_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	i += 4;
	if (!str[i])
	{
		printf("\n");
		return (0);
	}
	while (str[i] && str[i] == '-')
		i++;
	while (str[i] && str[i] == 'n')
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
	{
		printf("\n");
		return (0);
	}
	return (i);
}

int	ft_echo(t_shell *cmd, char *str)
{
	int	i;
	int	j;
	int	y;
	int	flag;

	y = skip_whitespace_and_echo_check(str);
	if (!y)
		return (0);
	flag = 1;
	i = 1;
	while (cmd->command[i] && cmd->command[i][0] == '-'
		&& cmd->command[i][1] == 'n')
	{
		j = 1;
		while (cmd->command[i][j] == 'n')
			j++;
		if (cmd->command[i++][j] != '\0')
			break ;
		flag = 0;
	}
	printf("%s", &str[y]);
	if (flag)
		printf("\n");
	return (0);
}

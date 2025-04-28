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

// int	ft_echo(t_shell *cmd, char *str)
// {
// 	int	i;
// 	int	flag;
// 	int	j;
// 	int	y;

// 	i = 0;
// 	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
// 		i++;
// 	i += 4;
// 	if (!str[i])
// 	{
// 		printf("\n");
// 		return (0);
// 	}
// 	while (str[i] && str[i] == '-')
// 		i++;
// 	while (str[i] && str[i] == 'n')
// 		i++;
// 	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
// 		i++;
// 	if (!str[i])
// 	{
// 		printf("\n");
// 		return (0);
// 	}
// 	y = i;
// 	flag = 1;
// 	i = 1;
// 	j = 1;
// 	while (cmd->command[i] && cmd->command[i][0] == '-'
// 		&& cmd->command[i][1] == 'n')
// 	{
// 		while (cmd->command[i][j] == 'n')
// 			j++;
// 		if (cmd->command[i++][j] != '\0')
// 			break ;
// 		flag = 0;
// 	}
// 	printf("%s", &str[y]);
// 	if (flag)
// 		printf("\n");
// 	return (0);
// }

int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	tabone(char *str, int flag_count)
{
	int	j;
	int	i;

	j = 0;
	while (str[j] && (str[j] == ' ' || str[j] == '\t'))
		j++;
	j += 4;
	while (str[j] && (str[j] == ' ' || str[j] == '\t'))
		j++;
	i = 0;
	while (i < flag_count)
	{
		while (str[j] && str[j] != ' ' && str[j] != '\t')
			j++;
		while (str[j] && (str[j] == ' ' || str[j] == '\t'))
			j++;
		i++;
	}
	return (j);
}

int	ft_echo(t_shell *cmd, char *str)
{
	int	i;
	int	flag;
	int	str_pos;

	i = 1;
	flag = 1;
	while (cmd->command[i] && is_n_flag(cmd->command[i]))
	{
		flag = 0;
		i++;
	}
	str_pos = tabone(str, i - 1);
	if (str[str_pos])
		write(1, &str[str_pos], ft_strlen(&str[str_pos]));
	if (flag)
		write(1, "\n", 1);
	return (0);
}

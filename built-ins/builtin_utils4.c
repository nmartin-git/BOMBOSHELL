/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atazzit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:56:05 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/26 17:57:23 by atazzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	print_invalid_id_error(char *arg, char *var)
{
	if (!var)
		ft_printf_fd(2, "export: '%s': not a valid identifier\n", arg);
	else
		ft_printf_fd(2, "%s: '%s': not a valid identifier\n", arg, var);
	return (1);
}

char	*trim_quotes(char *value)
{
	size_t	len;
	char	*new_value;

	len = ft_strlen(value);
	if (len >= 2 && ((value[0] == '"' && value[len - 1] == '"')
			|| (value[0] == '\'' && value[len - 1] == '\'')))
	{
		new_value = ft_substr(value, 1, len - 2);
		return (new_value);
	}
	else if ((value[0] == '"' || value[0] == '\'') && value[len
			- 1] != value[0])
		return (NULL);
	return (ft_strdup(value));
}

void	free_t_shell(t_shell *command)
{
	int	i;

	if (!command)
		return ;
	if (command->current_dir)
		free(command->current_dir);
	if (command->command)
	{
		i = 0;
		while (command->command[i])
		{
			free(command->command[i]);
			i++;
		}
		free(command->command);
	}
	free(command);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	size_six(char *cmd, int i)
{
	return (!cmd[i + 6] || cmd[i + 6] == ' ');
}

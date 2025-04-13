/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atazzit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:30:09 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/11 17:42:46 by atazzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

int	match_pattern(const char *pattern, const char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (1);
	if (*pattern == '*')
	{
		while (*(pattern + 1) == '\0')
			pattern++;
		if (*(pattern + 1) == '\0')
			return (1);
		while (*str)
		{
			if (match_pattern(pattern + 1, str))
				return (1);
			str++;
		}
		return (match_pattern(pattern + 1, str));
	}
	if (*pattern == *str || (*pattern == '?' && *str != '\0'))
		return (match_pattern(pattern + 1, str + 1));
	return (0);
}

void	free_wildcard(char **args)
{
	char	**expanded;
	int		i;

	expanded = expand_args_wildcards(args);
	i = 0;
	if (expanded)
	{
		while (expanded[i])
			free(expanded[i++]);
		free(expanded);
	}
}

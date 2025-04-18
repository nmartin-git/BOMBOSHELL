/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:40:55 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/18 19:48:47 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

static void	quotes_flags(char **command, int *in_quotes, char *quote_char)
{
	if ((**command == '"' || **command == '\'') && (*in_quotes == 0
			|| **command == *quote_char))
	{
		*in_quotes = !(*in_quotes);
		*quote_char = **command;
	}
}

static char	*process_word(char **command, char *start, int *count,
		char **result)
{
	if (*command != start)
		result[(*count)++] = ft_substr(start, 0, *command - start);
	while (**command == ' ')
		(*command)++;
	return (*command);
}

static void	iter_cmd(char **command, int *in_quotes, char *quote_char)
{
	quotes_flags(command, in_quotes, quote_char);
	(*command)++;
}

static int	malloc_t_muscle(char ***result, char **command)
{
	*result = malloc(sizeof(char *) * (ft_strlen(*command) + 1));
	if (!(*result))
		return (0);
	return (1);
}

char	**split_sous_stero(char **command)
{
	char	**result;
	char	*start;
	int		count;
	int		in_quotes;
	char	quote_char;

	if (!malloc_t_muscle(&result, command))
		return (NULL);
	count = 0;
	in_quotes = 0;
	start = *command;
	while (**command)
	{
		if (**command == ' ' && !in_quotes)
		{
			result[count++] = ft_substr(start, 0, *command - start);
			start = process_word(command, start, &count, result);
			continue ;
		}
		iter_cmd(command, &in_quotes, &quote_char);
	}
	if (start != *command)
		result[count++] = ft_substr(start, 0, *command - start);
	result[count] = NULL;
	return (result);
}

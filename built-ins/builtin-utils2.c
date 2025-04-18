/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin-utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atazzit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 04:40:55 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/17 04:40:56 by atazzit          ###   ########.fr       */
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

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	unset_env_value(t_env *env, char *key)
{
	t_env	*current;
	t_env	*prev;
	char	*expanded_key;

	expanded_key = handle_shell_var(env, key, "unset");
	if (!expanded_key)
		return ;
	prev = NULL;
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, expanded_key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				env = current->next;
			if (current->value)
				free(current->value);
			return (free(current->key), free(current), free(expanded_key));
		}
		prev = current;
		current = current->next;
	}
	free(expanded_key);
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

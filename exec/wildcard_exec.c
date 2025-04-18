/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atazzit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:13:36 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/11 18:13:38 by atazzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "wildcard.h"

void	expand_wildcards_in_tokens(t_input *arg_lst)
{
	t_input	*tmp;
	char	*original;
	char	**expanded;
	char	*args[2];

	tmp = arg_lst;
	while (tmp)
	{
		if ((tmp->token == WORD || tmp->token == WORD_D_QUOTE)
			&& has_wildcards(tmp->arg))
		{
			original = tmp->arg;
			args[0] = tmp->arg;
			args[1] = NULL;
			expanded = expand_args_wildcards(args);
			if (expanded && expanded[0])
			{
				tmp->arg = ft_strdup(expanded[0]);
				if (!tmp->arg)
					tmp->arg = original;
				else
				{
					free(original);
					tmp = add_remaining_tokens(tmp, expanded, tmp->token);
				}
				free_expanded_array(expanded);
			}
		}
		tmp = tmp->next;
	}
}

void	replace_token_arg(t_input *tmp, char **expanded)
{
	char	*new_arg;

	new_arg = ft_strdup(expanded[0]);
	if (!new_arg)
		return ;
	free(tmp->arg);
	tmp->arg = new_arg;
}

void	free_expanded_array(char **expanded)
{
	int	j;

	j = 0;
	while (expanded[j])
	{
		free(expanded[j]);
		j++;
	}
	free(expanded);
}

t_input	*add_remaining_tokens(t_input *tmp, char **expanded, int token)
{
	int		i;
	t_input	*new_token;
	t_input	*last_added;

	i = 1;
	last_added = tmp;
	while (expanded[i])
	{
		new_token = malloc(sizeof(t_input));
		if (!new_token)
			break ;
		new_token->arg = ft_strdup(expanded[i]);
		new_token->token = token;
		new_token->next = last_added->next;
		last_added->next = new_token;
		last_added = new_token;
		i++;
	}
	return (last_added);
}

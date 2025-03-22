/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 17:05:39 by nmartin           #+#    #+#             */
/*   Updated: 2025/03/22 18:44:25 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	arg_len(char *input)
{
	int	i;

	i = 0;
	if (!input[0])
		return (0);
	if ((input[0] == '|' && input[1] == '|') || (input[0] == '&'
		&& input[1] == '&') || (input[0] == '>' && input[1] == '>')
		|| (input[0] == '<' && input[1] == '<'))
		return (2);
	else if (input[0] == '|' || input[0] == '>' || input[0] == '<'
		|| input[0] == '(' || input[0] == ')' || input[0] == '\''
		|| input[0] == '"')
		return (1);
	else if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n'
		|| input[i] == '\v' || input[i] == '\f' || input[i] == '\r')
		return (ignore_spaces(input));
	while (input[i] && input[i] != '|' && input[i] != '>' && input[i] != '<'
		&& input[i] != '(' && input[i] != ')' && input[i] != '\''
		&& input[i] != '"' && !(input[i] == '&' && input[i + 1] == '&')
		&& input[i] != ' ' && input[i] != '\t' && input[i] != '\n'
		&& input[i] != '\v' && input[i] != '\f' && input[i] != '\r')
		i++;
	return (i);
}

char	*arg_get(char *input, int *i)
{
	int		len;
	int		y;
	char	*arg;

	len = arg_len(input);
	y = 0;
	arg = malloc(sizeof(char) * (len + 1));
	if (!arg)
		exit (127);//TODO mieux gerer l'erreur
	while (y < len)
	{
		arg[y] = input[y];
		y++;
	}
	arg[y] = '\0';
	*i += y;
	return (arg);
}

t_input	*input_set(char *input)
{
	t_input	*arg_lst;
	t_input *tmp;//TODO supp
	int		i;

	arg_lst = tokenisation(input);
	i = 0;
	tmp = arg_lst;
	while (input[i])
	{
		tmp->arg = arg_get(&input[i], &i);
		tmp = tmp->next;
	}
	//TODO supp 
	tmp = arg_lst;
	while (tmp)
	{
		printf("%s -> ", tmp->arg);
		tmp = tmp->next;
	}
	printf("null\n");
	//TODO supp ^^^^^^^^^^^^^^^^
	return (arg_lst);
}

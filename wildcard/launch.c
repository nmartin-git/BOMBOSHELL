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

#include "wildcard.h"

int	wildcards(char **arg)
{
	char	**expanded_args;
	int		i;

	expanded_args = expand_args_wildcards(&arg[1]);
	if (!expanded_args)
	{
		printf("Error: Failed to expand wildcards.\n");
		return (1);
	}
	i = 0;
	while (expanded_args[i])
	{
		printf("%s\n", expanded_args[i]);
		free(expanded_args[i]);
		i++;
	}
	free(expanded_args);
	return (0);
}

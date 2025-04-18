/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:19:13 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/12 16:42:51 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_quotes(char *str, char start, char end)
{
	char	*result;
	int		len;
	int		i;

	i = -1;
	if (!str)
		return (NULL);
	len = ft_strlen(str) + 3;
	result = malloc(sizeof(char) * len);
	if (!result)
		return (NULL);
	result[0] = start;
	while (str[++i])
		result[i + 1] = str[i];
	result[i + 1] = end;
	result [i + 2] = '\0';
	free(str);
	return (result);
}

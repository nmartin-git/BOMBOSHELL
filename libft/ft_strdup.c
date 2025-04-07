/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:48:32 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/07 18:45:18 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

char	*ft_strdup(const char *s)
{
	int		i;
	char	*ptr;

	if (!s)
		return (NULL);
	i = 0;
	ptr = malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (ptr == NULL)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

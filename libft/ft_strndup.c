/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:48:32 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/07 20:26:34 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int size)
{
	int		i;
	char	*ptr;

	i = 0;
	if (size < 1)
		return (NULL);
	if (size > (int)ft_strlen(s))
		size = ft_strlen(s);
	ptr = malloc(sizeof(char) * (size + 1));
	if (ptr == NULL)
		return (NULL);
	while (s[i] && i < size)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

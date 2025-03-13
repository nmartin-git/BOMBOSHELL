/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:04:52 by nmartin           #+#    #+#             */
/*   Updated: 2025/01/27 20:11:37 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_fd(int fd, const char *str, ...)
{
	int		len;
	va_list	lst;
	t_list	*first;
	t_list	*rlst;

	rlst = ft_lstnew("");
	if (!rlst)
		return (0);
	first = rlst;
	va_start(lst, str);
	ftp_check_char(str, lst, &rlst);
	va_end(lst);
	rlst = first;
	len = ftp_print_result(rlst, fd);
	ft_lstclear(&first, ftp_del);
	return (len);
}

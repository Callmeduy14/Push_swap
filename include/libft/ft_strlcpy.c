/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyudi <yyudi@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:17:15 by yyudi             #+#    #+#             */
/*   Updated: 2025/07/08 11:47:00 by yyudi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	n;

	len = ft_strlen(src);
	if (size == 0)
		return (len);
	n = 0;
	while (src[n] != '\0' && n < size - 1)
	{
		dst[n] = src[n];
		n++;
	}
	dst[n] = '\0';
	return (len);
}

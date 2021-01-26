/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 10:29:20 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/06 19:00:59 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t dlen;
	size_t slen;
	size_t i;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (size <= dlen)
		return (dlen + slen - (dlen - size));
	i = 0;
	while (i < size - dlen - 1 && src[i] != 0)
	{
		*(dst + dlen + i) = *(src + i);
		i++;
	}
	*(dst + dlen + i) = '\0';
	return (dlen + slen);
}

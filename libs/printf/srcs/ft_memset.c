/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:20:50 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/10 13:51:49 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buf, int ch, size_t count)
{
	unsigned char *tmp;

	tmp = (unsigned char*)buf;
	while (count-- > 0)
	{
		*tmp++ = (unsigned char)ch;
	}
	return (buf);
}

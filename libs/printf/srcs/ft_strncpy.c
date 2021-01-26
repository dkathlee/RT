/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:35:13 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/17 11:30:30 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t counter;

	counter = 0;
	while (counter < len)
	{
		if (*src != '\0')
			*(dest + counter) = *src++;
		else
			*(dest + counter) = '\0';
		counter++;
	}
	return (dest);
}

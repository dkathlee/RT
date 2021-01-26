/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:25:24 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/17 11:28:31 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int counter;

	counter = 0;
	while (*src != '\0')
	{
		*(dest + counter) = *src;
		src++;
		counter++;
	}
	*(dest + counter) = '\0';
	return (dest);
}

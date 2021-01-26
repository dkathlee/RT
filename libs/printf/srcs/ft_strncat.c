/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:12:16 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/06 15:05:26 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int		counter;
	size_t	i;

	counter = 0;
	i = 0;
	while (*s1 != 0)
	{
		counter++;
		s1++;
	}
	while (*s2 != 0 && i < n)
	{
		*s1 = *s2;
		s1++;
		s2++;
		counter++;
		i++;
	}
	if (*(s1 - 1) != 0)
		*s1 = '\0';
	return (s1 - counter);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:06:22 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/06 15:02:39 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int counter;

	counter = 0;
	while (*s1 != 0)
	{
		counter++;
		s1++;
	}
	while (*s2 != 0)
	{
		*s1 = *s2;
		s1++;
		s2++;
		counter++;
	}
	*s1 = '\0';
	return (s1 - counter);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 16:02:33 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/06 17:00:49 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		res;
	size_t	counter;

	res = 0;
	counter = 0;
	while (counter++ < n && (*s1 != '\0' || *s2 != '\0'))
	{
		res = (unsigned char)*s1++ - (unsigned char)*s2++;
		if (res != 0)
			return (res);
	}
	return (res);
}

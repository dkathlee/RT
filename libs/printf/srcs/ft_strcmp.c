/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:52:55 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/06 17:01:26 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int res;

	res = 0;
	while (*s1 != '\0' || *s2 != '\0')
	{
		res = (unsigned char)*s1++ - (unsigned char)*s2++;
		if (res != 0)
			return (res);
	}
	return (res);
}

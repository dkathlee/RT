/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:14:54 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/06 15:07:37 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *res;

	res = NULL;
	while (*s != 0)
	{
		if (*s == (char)c)
			res = (char*)s;
		s++;
	}
	if ((char)c == 0)
		return ((char*)s);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:47:45 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/10 13:18:36 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int count;
	int i;

	count = 0;
	while (*(to_find + count) != '\0')
		count++;
	if (count == 0)
		return ((char*)str);
	while (*str != '\0')
	{
		i = 0;
		while (i < count)
		{
			if (*(str + i) != *(to_find + i))
				break ;
			if (i == count - 1)
				return ((char*)str);
			i++;
		}
		str++;
	}
	return (NULL);
}

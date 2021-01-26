/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:19:36 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/06 17:10:09 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t to_f_len;
	size_t i;
	size_t count;

	if ((to_f_len = ft_strlen(to_find)) == 0)
		return ((char*)str);
	count = to_f_len - 1;
	while (*str != '\0' && count < len)
	{
		i = 0;
		while (i < to_f_len)
		{
			if (*(str + i) != *(to_find + i))
				break ;
			if (i == to_f_len - 1)
				return ((char*)str);
			i++;
		}
		count++;
		str++;
	}
	return (NULL);
}

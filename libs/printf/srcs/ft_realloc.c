/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 16:23:21 by dkathlee          #+#    #+#             */
/*   Updated: 2020/01/28 10:53:41 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *src, size_t old_size, size_t new_size)
{
	unsigned char	*res;
	size_t			i;

	if ((res = (unsigned char*)ft_memalloc(new_size)) == NULL)
		return (NULL);
	if (old_size == 0 || src == NULL)
		return ((void*)res);
	i = 0;
	while (i < old_size && i < new_size)
	{
		res[i] = ((unsigned char*)src)[i];
		i++;
	}
	free(src);
	return ((void*)res);
}

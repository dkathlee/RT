/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_create_elemc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:44:26 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/09 13:52:57 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_dlist	*ft_dlst_create_elemc(void *data, size_t n)
{
	t_dlist	*res;

	if (data == NULL || (res = ft_memalloc(sizeof(t_dlist))) == NULL)
		return (NULL);
	if ((res->content = ft_memalloc(n)) == NULL)
	{
		ft_memdel((void **)&res);
		return (NULL);
	}
	res->content = ft_memcpy(res->content, data, n);
	res->content_size = n;
	res->next = NULL;
	res->prev = NULL;
	return (res);
}

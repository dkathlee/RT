/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_create_elem.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:44:26 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/09 13:52:08 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlst_create_elem(void *data)
{
	t_dlist	*res;

	if (data == NULL || (res = ft_memalloc(sizeof(t_dlist))) == NULL)
		return (NULL);
	res->content = data;
	res->content_size = 0;
	res->next = NULL;
	res->prev = NULL;
	return (res);
}

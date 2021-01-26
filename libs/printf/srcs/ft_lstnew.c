/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:16:15 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/10 10:39:01 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*res;
	void	*data;

	if ((res = (t_list*)ft_memalloc(sizeof(t_list))) == NULL)
		return (NULL);
	res->next = NULL;
	if (content == NULL)
	{
		res->content = NULL;
		res->content_size = 0;
	}
	else if ((data = ft_memalloc(content_size)) != NULL)
	{
		data = ft_memcpy(data, content, content_size);
		res->content = data;
		res->content_size = content_size;
	}
	else
	{
		free(res);
		return (NULL);
	}
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_popi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:25:15 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/09 14:17:16 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlst_popi(t_dlist **dlst, size_t i)
{
	t_dlist	*tmp;

	if (dlst == NULL || *dlst == NULL)
		return (NULL);
	tmp = *dlst;
	if (i == 0)
	{
		*dlst = (*dlst)->next;
		if (*dlst != NULL)
			(*dlst)->prev = NULL;
	}
	while (i-- > 0)
	{
		if (tmp == NULL)
			return (NULL);
		tmp = tmp->next;
	}
	if (tmp->prev != NULL)
		tmp->prev->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = tmp->prev;
	tmp->prev = NULL;
	tmp->next = NULL;
	return (tmp);
}

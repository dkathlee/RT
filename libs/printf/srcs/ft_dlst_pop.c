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

t_dlist	*ft_dlst_pop(t_dlist **dlst, t_dlist *el)
{
	if (dlst == NULL || *dlst == NULL || el == NULL)
		return (NULL);
	if (el == *dlst)
		*dlst = (*dlst)->next;
	if (el->prev != NULL)
		el->prev->next = el->next;
	if (el->next != NULL)
		el->next->prev = el->prev;
	el->prev = NULL;
	el->next = NULL;
	return (el);
}

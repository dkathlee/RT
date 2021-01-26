/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_push_front.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:51:27 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/09 15:34:15 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlst_push_front(t_dlist **dlst, t_dlist *el)
{
	if (el == NULL || dlst == NULL)
		return ;
	if (*dlst == NULL)
	{
		*dlst = el;
		el->next = NULL;
		el->prev = NULL;
		return ;
	}
	el->next = *dlst;
	el->prev = NULL;
	(*dlst)->prev = el;
	*dlst = el;
}

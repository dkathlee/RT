/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 13:57:27 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/17 13:10:35 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlst_push_back(t_dlist **dlst, t_dlist *el)
{
	t_dlist	*tmp;

	if (el == NULL || dlst == NULL)
		return ;
	if (*dlst == NULL)
	{
		*dlst = el;
		el->next = NULL;
		el->prev = NULL;
		return ;
	}
	tmp = *dlst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = el;
	el->prev = tmp;
	el->next = NULL;
}

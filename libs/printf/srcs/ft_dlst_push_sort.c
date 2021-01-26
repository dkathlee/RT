/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_deli.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:25:15 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/05 13:04:20 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	insert_el(t_dlist **lst, t_dlist *el, int (*f)(t_dlist*, t_dlist*))
{
	if (f(*lst, el) == 1)
	{
		el->next = *lst;
		el->prev = (*lst)->prev;
		if ((*lst)->prev != NULL)
			(*lst)->prev->next = el;
		(*lst)->prev = el;
		*lst = el;
	}
	else
	{
		(*lst)->next = el;
		el->prev = *lst;
		el->next = NULL;
	}
}

void		ft_dlst_push_sort(t_dlist **dl, t_dlist *el,
								int (*f)(t_dlist*, t_dlist*))
{
	t_dlist	*tmp;

	if (dl == NULL || el == NULL || f == NULL)
		return ;
	if (*dl == NULL)
	{
		*dl = el;
		el->prev = NULL;
		el->next = NULL;
		return ;
	}
	tmp = *dl;
	while (tmp->next != NULL)
	{
		if (f(tmp, el) == 1)
			break ;
		tmp = tmp->next;
	}
	if (tmp == *dl)
		insert_el(dl, el, f);
	else
		insert_el(&tmp, el, f);
}

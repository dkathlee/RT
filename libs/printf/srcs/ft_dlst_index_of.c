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

int	ft_dlst_index_of(t_dlist *dl, t_dlist *el)
{
	int	i;

	i = 0;
	if (dl == NULL || el == NULL)
		return (-1);
	while (dl != NULL)
	{
		if (dl == el)
			break ;
		i++;
		dl = dl->next;
	}
	return (i);
}

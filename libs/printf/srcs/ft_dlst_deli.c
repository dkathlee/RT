/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_deli.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:25:15 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/09 14:16:02 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dlst_deli(t_dlist **dlst, size_t i)
{
	t_dlist	*tmp;

	tmp = ft_dlst_popi(dlst, i);
	if (tmp == NULL)
		return (-1);
	ft_memdel((void **)&(tmp->content));
	ft_memdel((void **)&tmp);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:25:15 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/10 12:58:12 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dlst_len(t_dlist *dlst)
{
	size_t	res;

	res = 0;
	while (dlst != NULL)
	{
		res++;
		dlst = dlst->next;
	}
	return (res);
}

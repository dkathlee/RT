/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_powr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 10:02:48 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/11 10:12:05 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_powr(int nb, int power)
{
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	nb *= ft_powr(nb, power - 1);
	return (nb);
}

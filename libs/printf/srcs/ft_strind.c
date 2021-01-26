/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strind.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 10:47:50 by dkathlee          #+#    #+#             */
/*   Updated: 2019/12/25 10:49:32 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strind(char *str, char c)
{
	int	ind;

	ind = 0;
	while (str[ind])
	{
		if (str[ind] == c)
			return (ind);
		ind++;
	}
	return (-1);
}

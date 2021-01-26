/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 13:10:40 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/10 13:49:18 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		sign;
	int		i;
	char	buf[11];

	if (fd < 0)
		return ;
	sign = n;
	i = 0;
	if (n == 0)
		buf[i++] = '0';
	while (n != 0)
	{
		buf[i++] = n > 0 ? n % 10 + '0' : (n % 10) * -1 + '0';
		n /= 10;
	}
	if (sign < 0)
		buf[i++] = '-';
	while (--i >= 0)
		ft_putchar_fd(buf[i], fd);
}

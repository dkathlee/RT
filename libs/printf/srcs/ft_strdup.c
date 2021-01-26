/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 13:54:55 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/10 11:31:34 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		i;
	int		len;

	len = ft_strlen(s1);
	if ((res = ft_strnew(len)) == NULL)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		res[i] = s1[i];
		i++;
	}
	return (res);
}

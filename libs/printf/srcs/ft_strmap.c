/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:49:45 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/10 12:27:50 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char			*res;
	unsigned int	i;

	if (s == NULL || f == NULL || (res = ft_strnew(ft_strlen(s))) == NULL)
		return (NULL);
	i = 0;
	while (*(s + i) != 0)
	{
		res[i] = f(s[i]);
		i++;
	}
	return (res);
}

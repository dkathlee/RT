/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:13:56 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/10 12:28:03 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	i;

	if (s == NULL || f == NULL || (res = ft_strnew(ft_strlen(s))) == NULL)
		return (NULL);
	i = 0;
	while (*(s + i) != 0)
	{
		res[i] = f(i, s[i]);
		i++;
	}
	return (res);
}

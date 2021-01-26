/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:42:20 by dkathlee          #+#    #+#             */
/*   Updated: 2019/11/18 20:03:28 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin2(char const *s1, char const *s2, const char *s3)
{
	char *res;

	if (s1 == NULL || s2 == NULL || s3 == NULL ||
		(res = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) +
												ft_strlen(s3) + 1)) == NULL)
		return (NULL);
	ft_strcpy(res, (char*)s1);
	ft_strcat(res, s2);
	ft_strcat(res, s3);
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 17:58:57 by dkathlee          #+#    #+#             */
/*   Updated: 2019/10/31 16:44:58 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_len(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] != c && s[i] != 0)
		i++;
	return (i);
}

static void	free_mem(char **mem, int c)
{
	while (--c >= 0)
		free(mem[c]);
	free(mem);
}

static int	str_split(char **res, const char *s, char c)
{
	int		counter;
	int		i;
	int		j;

	counter = 0;
	i = 0;
	while (s[i] != 0)
	{
		if (s[i] == c)
		{
			i++;
			continue;
		}
		if ((res[counter] = ft_strnew(word_len(s + i, c))) == NULL)
		{
			free_mem(res, counter);
			return (1);
		}
		j = 0;
		while (s[i] != c && s[i] != 0)
			res[counter][j++] = s[i++];
		counter++;
	}
	res[counter] = NULL;
	return (0);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**res;

	if (s == NULL ||
	(res = (char**)malloc(sizeof(char**) * ft_word_count(s, c) + 1)) == NULL)
		return (NULL);
	if (str_split(res, s, c) == 1)
		return (NULL);
	return (res);
}

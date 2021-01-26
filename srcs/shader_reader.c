/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:07:59 by dkathlee          #+#    #+#             */
/*   Updated: 2020/08/25 12:42:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static size_t	read_shader_file(char *fname, char **shader)
{
	int		fd;
	size_t	r;
	size_t	nor;
	char	line[16];

	if ((fd = open(fname, O_RDONLY | O_BINARY)) == -1)
		return (0);
	nor = 0;
	while ((r = read(fd, line, 16)) != 0)
	{
		*shader = ft_realloc(*shader, nor, nor + r);
		ft_memcpy(*shader + nor, line, r);
		nor += r;
	}
	close(fd);
	return (nor);
}

size_t			load_shader_file(char *fname, char **shader)
{
	int	code_len;

	*shader = NULL;
	if ((code_len = read_shader_file(fname, shader)) == 0)
		return (0);
	return (code_len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 11:45:54 by dkathlee          #+#    #+#             */
/*   Updated: 2020/04/22 20:47:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list_fds	*get_fds(const int fd)
{
	static t_list_fds	*fds;
	t_list_fds			*el;

	el = fds;
	while (el != NULL && el->fd != fd)
		el = el->next;
	if (el == NULL)
	{
		if ((el = malloc(sizeof(t_list_fds))) == NULL)
			return (NULL);
		el->fd = fd;
		el->buff = NULL;
		el->next = fds;
		fds = el;
	}
	return (el);
}

static int			read_to_buf(const int fd, t_list_fds *curr)
{
	unsigned int	nor;
	char			buf[BUFF_SIZE + 1];
	char			*end;

	if (ft_strchr(curr->buff, '\n') == NULL)
	{
		while ((nor = read(fd, buf, BUFF_SIZE)) > 0)
		{
			buf[nor] = 0;
			end = curr->buff;
			if ((curr->buff = ft_strjoin(curr->buff, buf)) == NULL)
				return (-1);
			ft_memdel((void**)&end);
			if (ft_strrchr(buf, '\n') != NULL)
				break ;
		}
		if (nor < BUFF_SIZE && ft_strlen(curr->buff) == 0)
		{
			return (0);
		}
	}
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	t_list_fds			*curr;
	char				*end;
	int					ret;

	if (fd < 0 || line == NULL || read(fd, NULL, 0) < 0)
		return (-1);
	*line = NULL;
	if ((curr = get_fds(fd))->buff == NULL)
		curr->buff = ft_strnew(0);
	ret = read_to_buf(fd, curr);
	if (ret != 1)
		return (ret);
	end = ft_strchr(curr->buff, '\n') == NULL ? ft_strchr(curr->buff, '\0')
												: ft_strchr(curr->buff, '\n');
	if ((*line = ft_strsub(curr->buff, 0, end - curr->buff)) == NULL)
		return (-1);
	if (*end == 0)
		end = NULL;
	else if ((end = ft_strdup(end + 1)) == NULL)
		return (-1);
	ft_memdel((void**)&(curr->buff));
	curr->buff = end;
	return (1);
}

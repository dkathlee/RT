/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_create_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:06:16 by dkathlee          #+#    #+#             */
/*   Updated: 2020/09/16 20:02:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree	*ft_btree_create_node(void *item)
{
	t_btree *node;

	if ((node = ft_memalloc(sizeof(t_btree))) == NULL)
		return (NULL);
	node->item = item;
	node->left = 0;
	node->right = 0;
	return (node);
}

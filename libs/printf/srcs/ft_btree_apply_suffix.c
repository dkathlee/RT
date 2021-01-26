/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_suffix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:10:00 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/11 10:19:16 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_apply_suffix(t_btree *root, void (*applyf)(void *))
{
	if (root == 0)
		return ;
	if (root->left != 0)
		ft_btree_apply_suffix(root->left, applyf);
	if (root->right != 0)
		ft_btree_apply_suffix(root->right, applyf);
	applyf(root->item);
}

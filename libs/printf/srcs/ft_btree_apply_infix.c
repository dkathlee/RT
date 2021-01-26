/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_infix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:09:30 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/17 12:29:48 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	if (root == 0)
		return ;
	if (root->left != 0)
		ft_btree_apply_infix(root->left, applyf);
	applyf(root->item);
	if (root->right != 0)
		ft_btree_apply_infix(root->right, applyf);
}

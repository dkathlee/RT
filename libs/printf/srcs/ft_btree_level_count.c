/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_level_count.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:12:10 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/11 10:19:29 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_btree_level_count(t_btree *root)
{
	int count1;
	int count2;

	if (root == 0)
		return (0);
	count1 = 1;
	count2 = 1;
	count1 += ft_btree_level_count(root->left);
	count2 += ft_btree_level_count(root->right);
	if (count1 > count2)
		return (count1);
	return (count2);
}

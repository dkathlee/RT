/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkathlee <dkathlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 20:53:34 by dkathlee          #+#    #+#             */
/*   Updated: 2019/09/10 09:50:14 by dkathlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_del_all_list(t_list **lst)
{
	if ((*lst)->next != NULL)
		ft_del_all_list(&((*lst)->next));
	free((*lst)->content);
	free(*lst);
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*res;
	t_list	*cur;

	if (lst == NULL)
		return (NULL);
	res = f(lst);
	cur = res;
	while (lst->next != NULL)
	{
		lst = lst->next;
		if ((cur->next = f(lst)) == NULL)
		{
			ft_del_all_list(&res);
			return (NULL);
		}
		cur = cur->next;
	}
	return (res);
}

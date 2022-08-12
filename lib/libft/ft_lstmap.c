/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 20:03:46 by lholdo            #+#    #+#             */
/*   Updated: 2022/01/24 20:03:47 by lholdo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*util;
	t_list	*res;

	if (!lst)
		return (0);
	res = 0;
	while (lst)
	{
		util = ft_lstnew(f(lst->content));
		if (!util)
		{
			ft_lstclear(&res, del);
			return (0);
		}
		ft_lstadd_back(&res, util);
		lst = lst->next;
	}
	return (res);
}

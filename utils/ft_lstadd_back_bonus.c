/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:11:43 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/24 11:59:27 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (lst)
	{
		if (!*lst)
		{
			*lst = new;
		}
		else
		{
			last_node = ft_lstlast(*lst);
			last_node->next = new;
		}
	}
}

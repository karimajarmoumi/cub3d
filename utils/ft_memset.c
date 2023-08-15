/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:37:17 by kjarmoum          #+#    #+#             */
/*   Updated: 2023/08/12 12:45:40 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;


	while (i < len)
		((unsigned char *)b)[i++] = (unsigned char)c;

	return (b);
}

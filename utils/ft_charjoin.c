/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:49:41 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/09 13:49:43 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

char	*ft_charjoin(char const *s1, char character)
{
	int		i;
	char	*p;

	i = 0;
	if (!s1 )
		return (NULL);
	p = (char *)malloc((ft_strlen(s1) + 1 + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i]=character;
	i++;
	p[i] = '\0';
	return (p);
}

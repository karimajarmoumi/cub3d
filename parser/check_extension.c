/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:54 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/05 18:59:27 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

bool	check_extension(char *fileName)
{
	int		len;
	int		extension_len;
	char	*extension;

	extension = ft_strdup(".cub");
	extension_len = 3;
	len = ft_strlen(fileName) - 1;
	while (extension_len >= 0)
	{
		if (fileName[len] != extension[extension_len])
		{
			ft_free(extension);
			return (false);
		}
		extension_len--;
		len--;
	}
	ft_free(extension);
	return (true);
}

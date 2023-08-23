/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:54 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/23 10:56:08 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

bool check_extension(char *fileName)
{
    int len;
    int extensionLen;
    char *extension;

    extension = ft_strdup(".cub");
    extensionLen = 3;
    len = ft_strlen(fileName ) - 1;
    while (extensionLen >= 0)
    {
        if (fileName[len] != extension[extensionLen])
            return false;
        extensionLen--;
        len--;
    }
    free(extension);
    return true;
}

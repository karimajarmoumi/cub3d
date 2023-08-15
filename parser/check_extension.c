/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:54 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/12 09:22:31 by kjarmoum         ###   ########.fr       */
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

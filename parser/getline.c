/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:46:17 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/15 15:46:20 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

char *getLine(int fd)
{
    char character;
    int nbyt;
    int i = 0;
    char *tmp;
    char *line;

    line = NULL;
    nbyt = read(fd,&character,1);
    while(nbyt > 0)
    {
        if(i == 0)
            line = ft_strdup("");
        if(character =='\n' || character=='\0')
             return line;
        tmp = line;
        line = ft_charjoin(line,character);
        ft_free(tmp);
        nbyt = read(fd,&character,1);
        i = 1;
    }
    return line;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-baam <kel-baam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:50:04 by kel-baam          #+#    #+#             */
/*   Updated: 2023/09/06 20:44:04 by kel-baam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

 char *copyString(char *src,char *des)
{
    int i =0;
    char *tmp;
    tmp = des;
    while(src[i])
    {
        tmp[i]=src[i];
        i++;
    }
    tmp[i]='\0';
    return tmp;
}

void print_error(char *msg_error)
{
    int len;
    len =ft_strlen(msg_error);
    write(2,msg_error,len);
    write(2,"\n",1);
    exit(1);
}

int  count_words(char **str)
{
    int i;
    
    i = 0;
    while(str && str[i])
        i++; 
    return i;   
}

int	close_win()
{
    print_error("you exit the game!!!");
	exit(0);
	return (0);
}

float normalize(float angle)
{
    if (angle >= 2 * M_PI)
        angle = remainder(angle, 2 * M_PI);
    if (angle <= 0)
        angle += 2 * M_PI;
    return (angle);
}
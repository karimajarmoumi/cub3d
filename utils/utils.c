/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:50:04 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/12 13:35:51 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

void displayArray(char **str)
{
    int i =0;
    int j;

    while(str[i])
    {
        j =0;
        printf("|");
        while(str[i][j])
        {
            printf("%c",str[i][j]);
            j++;
        }
        printf("|\n");
        i++;
    }
}
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
void ft_free(char *str)
{
    if(str)
        free(str);
}

void print_error(char *msg_error)
{
    int len;
    len =ft_strlen(msg_error);
    write(2,msg_error,len);
    write(2,"\n",1);
    exit(1);
}
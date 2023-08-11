/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:14:26 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/11 17:36:51 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "parse.h"

void fillArray(char **map,char *fileName)
{
    char *line;
    int i = 0;
    char **tmp_map;
    line = ft_strdup("");
    int fd = open (fileName,O_RDONLY);
    tmp_map = map;
    while(line)
    {
       ft_free(line);
       line = getLine(fd);
       if(line)
       {
           tmp_map[i]=ft_strdup(line);
           i++;
       }
   }
   tmp_map[i] =  NULL;
}


int main(int ac, char **av)
{

    if(ac == 2)
    {
        t_map map;

       if(check_extension(av[1])==true)
            readMap(av[1],&map);
        printf("woooow\n");
    }
    else
        write(1,"Please enter a file name\n",25);
}

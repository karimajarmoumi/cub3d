/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:50:27 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/11 18:05:47 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include<stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#define WALL '1'
#define EMPTY '0'
#define SPACE ' '
#define PLAYER_W 'W'
#define PLAYER_E 'E'
#define PLAYER_S 'S'
#define PLAYER_N 'N'

typedef struct s_position
{
    int player_x;
    int player_y;
}t_position;

typedef struct  s_player
{
    char player_symbol;
    int flag_on;
    int count_player;
    t_position player_pos;
}t_player;

typedef struct  s_map
{

    int height;
    char **map;
} t_map;

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int ft_strlen(const char *str);
bool check_extension(char *fileName);
void readMap(char *fileName,t_map *map);
void displayArray(char **str);
char *getLine(int fd);
 char *copyString(char *src,char *des);
 void fillArray(char **map,char *fileName);
 void ft_free(char *str);
char	*ft_charjoin(char const *s1, char character);
void print_error(char *msg_error);
void check_player(t_player *player,char *line, int height);
#endif

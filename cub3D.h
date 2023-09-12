/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ../cube.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjarmoum <kjarmoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:50:27 by kel-baam          #+#    #+#             */
/*   Updated: 2023/08/15 15:45:34 by kjarmoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H

#include <mlx.h>
#include <stdio.h>
#include<stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

#define WALL '1'
#define EMPTY '0'
#define SPACE ' '
#define X 60
#define PLAYER_W 'W'
#define PLAYER_E 'E'
#define PLAYER_S 'S'
#define PLAYER_N 'N'
#define MIN_RANGE 0
#define MAX_RANGE 255
#define LEFT  97
#define RIGHT 100
#define UP 119
#define DOWN 115
#define RIGHT_ROTATE  65363
#define LEFT_ROTATE  65361
#define ESC  65307
#define FRAME_WIDTH  30
#define FRAME_HEIGHT 30
#define NORD_ANGLE  (M_PI / 2) * 3
#define EAST_ANGLE 0
#define SOUTH_ANGLE M_PI/2
#define ROTATION_SPEED M_PI/36 
#define WEST_ANGLE M_PI
#define FOV        (M_PI/3)
#define ANGLE_FOV M_PI/3 
#define  FACTOR    0.1
#define   MAP_WIDTH 1800
#define   MAP_HEIGHT 700
#define NUM_RAYS ANGLE_FOV/(map->max_width * 60)
#define WINDOW_HEIGHT  780
#define WINDOW_WIDTH  1080
#define  MAP_CENTER WINDOW_HEIGHT/2
#define RIGHT_CLICK 3
#define LEFT_CLICK 1
#define PLAYER_COLOR  0x0000FF
#define FLOOR_COLOR  0xFFFFFF
#define WALL_COLOR 0xA0A0A0
#define SPACE_COLOR  0x000000
#define MINIMAP_WIDTH 200 
#define MINIMAP_HEIGHT 200

typedef struct t_list
{
	void			*content;
	struct t_list	*next;

}					t_list;
typedef struct s_ray
{
    float x;
    float y;
    float distance;
    float projection_wall;
    float angle;
    int hit_wall_v;
    int hit_wall_h;
}t_ray;

typedef struct s_mlx_data
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}t_data;

typedef struct  s_player
{
    int     flag_on;
    int     count_player;
    char    **map_cpy;
    int      map_begin;
    t_list *store_map;
}t_player;

typedef struct s_coord
{
    float x;
    float y;
    float distance;
    int hit_wall;
}t_coord;

typedef struct s_position
{
    float x;
    float y;
    char  player_symbol;
    int player_rotation;
    int player_moves;
    float rotation_angle;
    int move_speed;
    int half_fov;
}t_position;

typedef struct s_args
{
    char    *key;
    char    *value;
    int     flag;
}t_args;

typedef struct  s_map
{
    int         map_height;
    int         max_width;
    int         floor_color;
    int         ceiling_color;
    char        **map;
    t_args      **args;
    t_position  player_pos;
	t_data     *data;
    t_list     *rays;
    t_data      *textures;
} t_map;

void	read_map(int fd, t_map *map, t_player *player);
unsigned int  get_pixel_color(t_data *t, double x, double y);
double calculate_offset_x(t_ray *ray, int hit_wall_flag, t_data *texture);
int get_texture_color(t_ray *ray, t_map *map, double *offsetY);
void    init_textures(t_map *map);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
bool    check_extension(char *fileName);
void    parse(char *fileName,t_map *map);
void    displayArray(char **str);
char    *get_line(int fd);
char    *copyString(char *src,char *des);
void    fill_map(t_map *map,t_player *player);
void    ft_free(char *str);
char    *ft_charjoin(char const *s1, char character);
void    print_error(char *msg_error);
void    check_player(t_player *player,char *line, t_map *map);
size_t  ft_strlcpy(char *dst, const char *src, size_t dstsize);
void    *ft_memset(void *b, int c, size_t len);
void    flood_fill(t_player *player, int pos_y, int pos_x);
char    *ft_substr(char const *s, unsigned int start, size_t len);
int     ft_isalpha(int c);
int     ft_strlen(const char *str);
int     ft_strchr_str(char *str, char *c);
char    *ft_strchr(const char *s, int c);
char	**ft_split(char const *s, char c);
int	    ft_strcmp(char *s1, char *s2);
int     ft_atoi(const char *str);
int     count_words(char **str);
int		ft_isdigit(int c);
int     is_identifier(char *key_value);
void    affect_value(t_args **arg,char *key,char *value);
void    check_identifier(char *line, t_map *map,int *count);
void    dda(t_map *map,t_coord *pos , t_coord *target, int color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    init_data_mlx(t_map *map);
int	    close_win();
int	    key_pressed(int code,t_map *map);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
int	    ft_lstsize(t_list *lst);
void    draw_3d_view(t_map *map);
void    draw_3d_map(t_map *map);
void    draw_mini_map(t_map *map, t_data *data);
bool    is_wall(t_map map,float  x, float  y, int flag);
int     is_up(float angle);
int     is_right(float angle);
void    get_fov(t_map *map, float start_angle, float end_angle);
float   normalize(float angle);
t_ray*  ray_data (t_map *map,float angle, int flag, t_coord inter_type);
float   calculate_distance(float x1, float y1, float x2, float y2);
int     update_player_position(t_map *map, float turn_angle);
void    free_rays(t_list **rays);
void	free_double_ptr(char **ptr);
void	free_struct_args(t_args **ptr);
t_coord horizontal_intersection(t_map map, float angle);
void ft_free_list(t_list *list);
void set_wall_texture(t_map *map, t_ray *ray, int i, int top_pixel, int bottom_pixel);
void    set_textures(t_map *map, t_ray *ray, int i);
void	calculate_wall_top_bottom_pixel(int wall_slice_height, int *top, int *bottom);
void separate_two_words(char *str,char **arg1,char **arg2);
int check_commas(char *str);
void store_color_value(int *store_color, char *red, char *green, char *blue);
void    affect_value(t_args **arg,char *key,char *value);
int is_identifier(char *key_value);
bool    check_map(char **map);
#endif

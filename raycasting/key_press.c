
#include "../cube.h"

int	key_pressed(int code,t_map *map)
{
    if (code == LEFT)
        map->player_pos.x-=1;
    if(code == RIGHT)
        map->player_pos.x+=1;
    if(code == UP)
        map->player_pos.y-=1;
    if(code == DOWN)
        map->player_pos.y+=1;
    if(code == ESC)
        print_error("you exit the program");
    mlx_clear_window (map->data->mlx, map->data->win);
    draw_map(map, map->data);
	return (code);
}

int	close_win(t_map *data)
{
    (void)*data;
    
    print_error("you exit the game!!!");
	exit(0);
	return (0);
}
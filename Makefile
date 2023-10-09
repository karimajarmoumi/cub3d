NAME = cub3D

NAME_BONUS = cub3D_Bonus

CC = clang

CFLAGS = -Wall -Wextra -Werror

SUB = ./mandatory/*.c ./mandatory/utils/*.c ./mandatory/parser/*.c ./mandatory/raycasting/*.c

OBJ =  ./mandatory/*.o ./mandatory/utils/*.o ./mandatory/parser/*.o ./mandatory/raycasting/*.o

SUB_BONUS = ./bonus/*.c ./bonus/utils/*.c ./bonus/parser/*.c ./bonus/raycasting/*.c

OBJ_BONUS = ./bonus/*.o ./bonus/utils/*.o ./bonus/parser/*.o ./bonus/raycasting/*.o

all : $(NAME)
bonus : $(NAME_BONUS)

$(NAME) :$(SUB)
	$(CC) ${CFLAGS} $(SUB) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o ${NAME} 


$(NAME_BONUS) :$(SUB_BONUS)
	$(CC) ${CFLAGS} $(SUB_BONUS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o ${NAME_BONUS} 

clean :
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)

fclean : clean
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re : fclean all




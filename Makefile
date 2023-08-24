NAME = cube

CC = clang

CFLAGS = -Wall -Wextra -Werror -fsanitize=address
SUB = *.c ./utils/*.c ./parser/*.c ./raycasting/*.c

OBJ =  *.o ./utils/*.o ./parser/*.o ./raycasting/*.o

all : $(NAME)

$(NAME) :$(SUB)
	$(CC) ${CFLAGS} $(SUB) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o ${NAME} 

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all




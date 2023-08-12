NAME =cube

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SUB = *.c ./utils/*.c ./parser/*.c

OBJ =  *.o ./utils/*.o ./parser/*.o

all : $(NAME)

$(NAME) :$(SUB)
	${CC} ${SUB} ${CFLAGS} -o ${NAME}

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all




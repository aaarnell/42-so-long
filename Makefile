NAME 	= 	so_long

HD		=	so_long.h

FLAGS	= 	-Wall -Werror -Wextra -g
FLAGS_O =	-Imlx

SRS		= 	main.c

OBJS	=	$(SRS:.c=.o)

all : 		$(NAME)

%.o :		%.c
			gcc $(FLAGS) $(FLAGS_O) -c $< -o $@ -I $(HD)

$(NAME)	: 	$(OBJS)
			gcc $(FLAGS) $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean :
			rm -f $(OBJS)

fclean : 	clean
			rm -f $(NAME)

re :		fclean all

.PHONY: all clean fclean re

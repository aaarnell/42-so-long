SRC_LIB		=	./libft
LIBFT		=	libft.a

NAME 	= 	so_long

HD		=	so_long.h

FLAGS	= 	-Wall -Werror -Wextra -g
FLAGS_O =	-Imlx

SRS		= 	check_count.c		gnl.c		hooks.c		\
			load_put_img.c		main.c		parc_map.c

OBJS	=	$(SRS:.c=.o)

all : 		$(NAME)

%.o :		%.c $(HD)
			gcc $(FLAGS) $(FLAGS_O) -c $< -o $@ -I $(HD)

$(NAME)	: 	$(OBJS)
			$(MAKE) -C $(SRC_LIB)
			gcc $(FLAGS) $(OBJS) $(SRC_LIB)/$(LIBFT) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean :
			rm -f $(OBJS)

fclean : 	clean
			rm -f $(NAME)

re :		fclean all

.PHONY: all clean fclean re

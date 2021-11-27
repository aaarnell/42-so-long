#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"

# define GNL_BUF_SIZE 32
# define ITER_IN_LOOP 5

//Количество и последовательность элементов в переменных
//g_str_sym, g_pict_path, e_pict должны соответствовать друг другу
//Символы карты допустимые
static char	*g_str_sym = "0eECP1";

//Картинки для вывода символов карты на экран
static char	*g_pict_path[] = {
	"./pict/empty.xpm",
	"./pict/enemy.xpm",
	"./pict/exit.xpm",
	"./pict/item.xpm",
	"./pict/player.xpm",
	"./pict/wall.xpm",
	"./pict/item_1.xpm",
	"./pict/item_2.xpm",
	"./pict/item_3.xpm",
	NULL
};

//Нумерованный список эдля символов и картинок
enum	e_pict {
	EMPTY,
	ENEMY,
	EXIT,
	ITEM,
	PLAYER,
	WALL
};

typedef struct s_vars{
	void	*mlx;
	void	*win;
	void	*img;
	//char	*addr;
	char	**map_mx;
	int		wd;
	int		hg;
	int		wdi;
	int		hgi;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	//int		x;
	//int		y;
	void	**imgs;
	int		ppx;
	int		ppy;
	int		*cn;
	int		cnt_stp;
	int		ex_num;
	int		timer;
}	t_vars;

int		load_imgs(t_vars *vars);
int		get_next_line(int fd, char **line);
int		check_length_get_width(char *line, int *wd);
int		cnt_chk_sym(char *line, t_vars *vars);
int		fnl_chk_sym_map(t_vars *vars);
int		read_file(char *file, t_vars *vars);
int		render_next_frame(t_vars *vars);
int		key_hook(int keycode, t_vars *vars);
int		mouse_hook(int button, int x, int y, t_vars *vars);
int		close_prog(t_vars *vars, int ex_num);

#endif

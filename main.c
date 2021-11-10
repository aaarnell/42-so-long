#include "so_long.h"

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		wd;
	int		hg;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}				t_vars;

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int mouse_move(int x, int y, t_vars *vars)
{
	int i;
	int j;

	printf("Hello from mouse_move! %d\t%d\t%p\n", x, y, vars);
	i = x - 2;
	j = y - 2;

	while (j <= y + 2)
	{
		i = x - 4;
		while (i <= x + 2)
		{
			my_mlx_pixel_put(vars, i, j, 0x00FF0000);
			i++;
		}
		j++;
	}
	//my_mlx_pixel_put(vars, x, y, 0x00FF0000);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

int	render_next_frame(t_vars *vars)
{
	my_mlx_pixel_put(vars, vars->x, vars->y, 0x00FF0000);
	if (vars->x < vars->wd)
		vars->x++;
	else
	{
		vars->x = 0;
		vars->y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	//sleep(2);
	//mlx_destroy_image(vars->mlx, vars->img);
	//mlx_clear_window(vars->mlx, vars->win);
	return (0);
}

int main(void)
{
	t_vars	vars;
	char *map[5];
	char map0[14] = "1111111111111";
	char map1[14] = "10010000000C1";
	char map2[14] = "1000011111001";
	char map3[14] = "1P0011E000001";
	char map4[14] = "1111111111111";
	//int i = 0;
	//char *relative_path = "./pacman.xpm";
	//int		img_width;
	//int		img_height;
	map[0] = map0;
	map[1] = map1;
	map[2] = map2;
	map[3] = map3;
	map[4] = map4;

	vars.wd = 10;
	vars.hg = 10;
	vars.img = NULL;
	vars.addr = NULL;
	vars.win = NULL;
	vars.x = 0;
	vars.y = 0;

	/*
	while (i < 5)
	{
		write(1, map[i], 14);
		write(1, "\n", 1);
		i++;
	}
	*/
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.wd, vars.hg, "SO_LONG!");
	vars.img = mlx_new_image(vars.mlx, vars.wd, vars.hg);
	//vars.img = mlx_xpm_file_to_image(vars.mlx, relative_path, &img_width, &img_height);
	vars.addr = mlx_get_data_addr(vars.img, &(vars.bits_per_pixel), &(vars.line_length), &(vars.endian));
	//mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	//mlx_hook (vars.win, 6, 0L, mouse_move, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
}

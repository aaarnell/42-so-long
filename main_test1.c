#include <mlx.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

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
}				t_vars;

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int	get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int	get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	key_hook(int keycode, t_vars *vars)
{
	t_vars *d;

	d = vars;
	printf("Hello from key_hook! %d\n", keycode);
	return (0);
}

int mouse_hook(int button, int x, int y, t_vars *vars)
{
	printf("Hello from mouse_hook! %d\t%d\t%d\t%p\n", button, x, y, vars);
	return (0);
}

int mouse_move(int x, int y, t_vars *vars)
{
	printf("Hello from mouse_move! %d\t%d\t%p\n", x, y, vars);
	return (0);
}

int	render_next_frame(t_vars *vars)
{
	int i;
	int j;

	i = 0;
	j = 0;

	//vars->win = mlx_new_window(vars->mlx, vars->wd, vars->hg, "SO_LONG!");
	vars->img = mlx_new_image(vars->mlx, vars->wd, vars->hg);
	vars->addr = mlx_get_data_addr(vars->img, &(vars->bits_per_pixel), &(vars->line_length), &(vars->endian));
	while (j < vars->hg)
	{
		i = 0;
		while (i < vars->wd)
		{
			if (j < 540 && i < 960)
				my_mlx_pixel_put(vars, i, j, 0x00FF0000);
			else if (j >= 540 && i >= 960)
				my_mlx_pixel_put(vars, i, j, 0x00FFFF00);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	//sleep(2);
	//mlx_destroy_image(vars->mlx, vars->img);
	//mlx_clear_window(vars->mlx, vars->win);
	return (0);
}

int	render_next_frame2(t_vars *vars)
{
	int i;
	int j;

	i = 0;
	j = 0;

	//vars->win = mlx_new_window(vars->mlx, vars->wd, vars->hg, "SO_LONG!");
	vars->img = mlx_new_image(vars->mlx, vars->wd, vars->hg);
	vars->addr = mlx_get_data_addr(vars->img, &(vars->bits_per_pixel), &(vars->line_length), &(vars->endian));
	while (j < vars->hg)
	{
		i = 0;
		while (i < vars->wd)
		{
			if (j < 540 && i >= 960)
				my_mlx_pixel_put(vars, i, j, 0x00FF0000);
			else if (j >= 540 && i < 960)
				my_mlx_pixel_put(vars, i, j, 0x00FFFF00);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	//sleep(2);
	//mlx_destroy_image(vars->mlx, vars->img);
	//mlx_clear_window(vars->mlx, vars->win);
	return (0);
}

int	key_hook2(int keycode, t_vars *vars)
{
	t_vars *d;

	d = vars;
	printf("Hello from key_hook! %d\n", keycode);
	if (!keycode)
		render_next_frame(vars);
	else
		render_next_frame2(vars);
	return (0);
}

int	main(void)
{
	// void	*mlx;
	// void	*mlx_win;
	// t_data	img;
	t_vars	vars;
	vars.wd = 1920;
	vars.hg = 1080;
	vars.img = NULL;
	vars.addr = NULL;
	vars.win = NULL;
	// int hg;
	// int i;
	// int j;
	// char c;

	// wd = 1920;
	// hg = 1080;
	// i = 0;
	// j = 0;

	//printf("%i", get_r(create_trgb(0, 255, 255, 255)));
	vars.mlx = mlx_init();
	if (!vars.mlx)
	{
		printf(" !! KO !!\n");
		exit(1);
	}

	//vars->win = mlx_new_window(vars->mlx, vars.wd, vars.hg, "SO_LONG!");
	vars.win = mlx_new_window(vars.mlx, vars.wd, vars.hg, "SO_LONG!");
	//vars.img = mlx_new_image(vars.mlx, vars.wd, vars.hg);
	mlx_key_hook(vars.win, key_hook2, &vars);
	//mlx_mouse_hook (vars.win, mouse_hook, &vars);
	//mlx_hook (vars.win, 6, 0L, mouse_move, &vars);
	//write(1, "a\n", 2);
	//mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	//sleep(2);
	//write(1, "b\n", 2);
	//mlx_loop_hook(vars.mlx, render_next_frame2, &vars);
	//write(1, "c\n", 2);
	//mlx_clear_window(vars.mlx, vars.win);
	//mlx_destroy_image(vars.mlx, vars.img);
	mlx_loop(vars.mlx);
/*
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, wd, hg, "SO_LONG!");
	img.img = mlx_new_image(mlx, wd, hg);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	// c = 48;
	// while (1)
	// {
	// 	img.img = mlx_new_image(mlx, wd, hg);
	// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	// 	j = 0;
		while (j < hg)
		{
			i = 0;
			while (i < wd)
			{
				if (j < 540 && i < 960)
					my_mlx_pixel_put(&img, i, j, 0x00FF0000);
				else if (j >= 540 && i >= 960)
					my_mlx_pixel_put(&img, i, j, 0x00FFFF00);
				i++;
			}
			j++;
		}
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		// sleep(2);
		//write(1, &c, 1);
		mlx_loop(mlx);
		// mlx_clear_window(mlx, mlx_win);
		// sleep(2);
	// }*/
}

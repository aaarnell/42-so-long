/*
void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_vars *vars)
{
	t_vars *d;

	d = vars;
	if ((keycode >= 0 && keycode <= 2) || keycode == 13)
		printf("Hello from key_hook! %d\n", keycode);
	return (0);
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
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}
*/

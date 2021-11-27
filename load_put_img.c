#include "so_long.h"

static int load_check_img(t_vars *vars, int *pct)
{
	int wdi;
	int hgi;

	vars->imgs[*pct] = mlx_xpm_file_to_image(vars->mlx, g_pict_path[*pct], &wdi, &hgi);
	if (!vars->imgs[*pct])
		return (0);						//Возможно здесь стоит добавить функцию, что будет чистить память тех картинок, что ранее успешно загружены
	if (wdi == hgi && (vars->wdi == 0 || vars->hgi == 0))
	{
		vars->wdi = wdi;
		vars->hgi = hgi;
	}
	else if(wdi != hgi || vars->wdi != wdi || vars->hgi != hgi)
		return (0);
	return (1);
}

int load_imgs(t_vars *vars)
{
	int pct;

	pct = 0;
	while (g_pict_path[pct])
	{
		if(!load_check_img(vars, &pct))
			return (0);					//Прописать выход из программы
		pct++;
	}
	return (1);
}

static void put_img_map(t_vars *vars)
{
	char	*ch;
	int		i;
	int		j;
	int		nb;
	int		ln;

	ln = ft_strlen(g_str_sym);
	//ft_putnbr_fd(ln, 1);
	//write(1, "\t", 1);
	i = 0;
	while (vars->map_mx[i])
	{
		j = 0;
		while (vars->map_mx[i][j])
		{
			ch = ft_strchr(g_str_sym, vars->map_mx[i][j]);
			nb = ch - g_str_sym;
			if (vars->map_mx[i][j] == g_str_sym[ITEM] && vars->cn[ln])
				nb = ln - 1 + vars->cn[ln];
			mlx_put_image_to_window(vars->mlx, vars->win, \
			vars->imgs[nb], (vars->wdi * j), (vars->hgi * i));
			j++;
		}
		i++;
	}
	if(!(vars->timer % ITER_IN_LOOP))
		vars->cn[ln] += 1;
	if(vars->cn[ln] > 3)
		vars->cn[ln] = 0;
}

int	render_next_frame(t_vars *vars)
{
	put_img_map(vars);
	if (vars->ex_num != 0 && (vars->timer / ITER_IN_LOOP) > 15)
		close_prog(vars, vars->ex_num);
	vars->timer++;
	return (0);
}

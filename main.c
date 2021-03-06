/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarnell <aarnell@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 22:10:36 by aarnell           #+#    #+#             */
/*   Updated: 2021/12/11 18:22:59 by aarnell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_prog(t_vars *vars, enum e_err	ernum)
{
	if (vars && vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (ernum)
		printf("Error\n%s\n", g_err_str[ernum]);
	else if (errno && errno != 60)
		printf("Error\n%s\n", strerror(errno));
	exit(errno);
	return (0);
}

static int	cross_exit(t_vars *vars)
{
	close_prog(vars, NONE);
	return (0);
}

static int	alloc_init(t_vars *vars)
{
	int	ln;
	int	i;

	i = 0;
	ln = ft_strlen(g_str_sym);
	vars->imgs = (void **)malloc(sizeof(void *) * (ln + 1));
	if (!vars->imgs)
		return (0);
	vars->imgs[ln] = NULL;
	vars->cn = (int *)malloc(sizeof(int) * ln);
	if (!vars->cn)
		return (0);
	while (i < ln)
		vars->cn[i++] = 0;
	return (1);
}

static void	struct_init(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = NULL;
	vars->img = NULL;
	vars->wd = 0;
	vars->hg = 0;
	vars->wdi = 0;
	vars->hgi = 0;
	vars->ppx = 0;
	vars->ppy = 0;
	vars->cnt_stp = 0;
	vars->sgn_scr = 0;
	vars->timer = 0;
	if (!alloc_init(vars))
		close_prog(NULL, ERR_ALLOC);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		close_prog(NULL, ERR_ARGNUM);
	struct_init(&vars);
	load_imgs(&vars, vars.imgs, g_pict_path);
	read_file(argv[1], &vars);
	vars.win = mlx_new_window(vars.mlx, vars.wd, vars.hg, "SO_LONG!");
	vars.img = mlx_new_image(vars.mlx, vars.wd, vars.hg);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_hook (vars.win, 2, 0L, key_hook, &vars);
	mlx_hook (vars.win, 17, 0L, cross_exit, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

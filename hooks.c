#include "so_long.h"

int close_prog(t_vars *vars, int ex_num)
{
	// int i, j;
	// i = 0;
	// while(vars->map_mx[i])
	// {
	// 	j = 0;
	// 	while(vars->map_mx[i][j])
	// 		write(1, &vars->map_mx[i][j++], 1);
	// 	write(1, "\n", 1);
	// 	i++;
	// }
	//mlx_clear_window(vars->mlx, vars->win);
	//render_next_frame(vars);
	printf("ЗАКРЫТЬ %p %d\n", vars, ex_num);
	//sleep(3);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

static void check_and_move(t_vars *vars, int tx, int ty)
{
	char *trg;
	char *plr;

	trg = &vars->map_mx[ty][tx];
	plr = &vars->map_mx[vars->ppy][vars->ppx];
	if ((*trg == g_str_sym[EXIT] && !vars->cn[ITEM]) || \
	(*trg != g_str_sym[EXIT] && *trg != g_str_sym[WALL]))
	{
		vars->ppx = tx;
		vars->ppy = ty;
		vars->cnt_stp++;
		if (*trg == g_str_sym[ITEM])
			vars->cn[ITEM]--;
		//if (*plr != g_str_sym[EXIT])
		*plr = g_str_sym[EMPTY];
		if (*trg == g_str_sym[EXIT] || *trg == g_str_sym[ENEMY])
		{
			vars->ex_num = 3;
			vars->timer = 0;
		}
			//close_prog(vars, 0); //отдельные выходы или передачу номера элемента в err_num
		if (*trg != g_str_sym[EXIT] && *trg != g_str_sym[ENEMY])
			*trg = g_str_sym[PLAYER];

		//прописать показ заставки и выход из программы EXIT
	}
}

static void address_definition(t_vars *vars, int keycode, int *tx, int *ty)
{
	if (keycode == 13)
	{
		*tx = vars->ppx;
		*ty = vars->ppy - 1;
	}
	if (keycode == 1)
	{
		*tx = vars->ppx;
		*ty = vars->ppy + 1;
	}
	if (keycode == 0)
	{
		*tx = vars->ppx - 1;
		*ty = vars->ppy;
	}
	if (keycode == 2)
	{
		*tx = vars->ppx + 1;
		*ty = vars->ppy;
	}
}

int	key_hook(int keycode, t_vars *vars)
{
	int tx;
	int ty;

	// int i = 0;
	// int j;
	if (vars->ex_num != 0)
		return (0);
	if (keycode < 3 || keycode == 13)
	{
		address_definition(vars, keycode, &tx, &ty);
		check_and_move(vars, tx, ty);
	}
	// while(vars->map_mx[i])
	// {
	// 	j = 0;
	// 	while(vars->map_mx[i][j])
	// 		write(1, &vars->map_mx[i][j++], 1);
	// 	write(1, "\n", 1);
	// 	i++;
	// }
	if (keycode == 53)
		close_prog(vars, 0);
	return (0);
}

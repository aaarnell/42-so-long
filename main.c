#include "so_long.h"

static int alloc_init(t_vars *vars)
{
	int ln;
	int i;

	i = 0;
	ln = ft_strlen(g_str_sym) + 3;
	vars->imgs = (void **)malloc(sizeof(void *) * (ln + 1));
	if(!vars->imgs)
		return (0);
	vars->imgs[ln] = NULL;
	vars->cn = (int *)malloc(sizeof(int) * ln);
	if(!vars->cn)
		return (0);
	while (i < ln)
		vars->cn[i++] = 0;
	return (1);
}

static int struct_init(t_vars *vars)//, t_cntrs *cnt)
{
	vars->mlx = mlx_init();
	vars->win = NULL;
	vars->img = NULL;
	//vars->addr = NULL;
	vars->wd = 0;
	vars->hg = 0;
	vars->wdi = 0;
	vars->hgi = 0;
	//vars->x = 0;
	//vars->y = 0;
	vars->ppx = 0;
	vars->ppy = 0;
	vars->cnt_stp = 0;
	vars->ex_num = 0;
	vars->timer = 0;
	if (!alloc_init(vars))
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2 || !struct_init(&vars) || \
	!load_imgs(&vars) || !read_file(argv[1], &vars))
		return (0); //сделать выход из проги с сообщением

	//Есть проверка на символы - чтобы не было недопустимых. НО нет проверки на наличие необходимых и отсутствие дубликатов, а также нет проверки, что карта ограничена стенами и нужнеа ли
	//printf("ppx = %d\tppy = %d\n", vars.ppx, vars.ppy);
	vars.win = mlx_new_window(vars.mlx, vars.wd, vars.hg, "SO_LONG!");
	vars.img = mlx_new_image(vars.mlx, vars.wd, vars.hg);
	//vars.addr = mlx_get_data_addr(vars.img, &(vars.bits_per_pixel), &(vars.line_length), &(vars.endian));
	//render_next_frame(&vars);
	//vars.img = mlx_xpm_file_to_image(vars.mlx, relative_path, &img_width, &img_height);
	//mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	//mlx_hook (vars.win, 6, 0L, mouse_move, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_hook (vars.win, 2, 0L, key_hook, &vars);
	mlx_hook (vars.win, 17, 0L, close_prog, &vars);
	//mlx_mouse_hook (vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);
	//прописать показ счетчика шагов
	return (0);
}

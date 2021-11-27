#include "so_long.h"

static int get_width_height(char *file, t_vars *vars)
{
	int fd;
	char *line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	while(get_next_line(fd, &line))
	{
		if(!check_length_get_width(line, &vars->wd) || !cnt_chk_sym(line, vars))//!check_sym(line, vars))
		{
			free(line); //возможно следует закрыть файл при ошибке
			return (0);
		}
		free(line);
		vars->hg++;
	}
	free(line);
	close(fd);
	return (1);
}

int read_file(char *file, t_vars *vars)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1 || !get_width_height(file, vars))
		return (0);
	vars->map_mx = (char **)malloc(sizeof(char *) * (vars->hg + 1));
	if (!vars->map_mx)
		return (0);
	i = 0;
	while(get_next_line(fd, &line))
		vars->map_mx[i++] = line;
	free(line);
	vars->map_mx[i] = NULL;
	if (!fnl_chk_sym_map(vars))
		return (0);		//Вероятно следует добавить очистку ранее аллоцированной памяти и закрытие файла
	vars->wd = vars->wd * vars->wdi;
	vars->hg = vars->hg * vars->hgi;
	close(fd);
	return (1);
}

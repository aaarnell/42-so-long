#include <stdio.h>
#include <stdlib.h>

static char *g_str_sym = "0eECP1";

static char	*g_ErrorNames[] = {
	"Index Out Of Bounds",
	"Stack Overflow",
	"Stack Underflow",
	"Out of Memory"
};

enum	e_Errors
{
	INDEX_OUT_OF_BOUNDS = 1,
	STACK_OVERFLOW,
	STACK_UNDERFLOW,
	OUT_OF_MEMORY
};

void put_img(t_vars *vars, int c)
{
	char	*ch;
	int		i;

	ch = ft_strchr(g_str_sym, c);
	i = &ch - &g_str_sym;
}

int	main(void)
{
	enum e_Errors put;
	put = 1;

	while(g_ErrorNames[put - 1])
	{
		printf("%s", g_ErrorNames[put - 1]);
		put++;
	}
	//exit(INDEX_OUT_OF_BOUNDS);

	char *str = "0eECP1";
	int i = &str[0] - &str[0];
	printf("\n%d\n", i);
	return (0);
}

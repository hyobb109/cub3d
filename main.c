#include "cub3d.h"

static void	check_args(int ac, char **av)
{
	char	*tmp;

	if (ac != 2)
		print_error_exit("You need an argument");
	tmp = ft_strnstr(av[1], ".cub", ft_strlen(av[1]));
	if (ft_strncmp(tmp, ".cub", 5))
		print_error_exit("Not a valid extension");
}

void leaks(void)
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_vars	vars;

	// atexit(leaks);
	check_args(ac, av);
	init_vars(&vars, av[1]);
	check_mapfile(&vars);
	validate_map(&vars);
	init_player(&vars);
	vars.win = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!vars.win)
		print_error_exit(0);
	vars.img.ptr = mlx_new_image(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.ptr, &vars.img.bpp, \
	&vars.img.len, &vars.img.endian);
	mlx_hook(vars.win, KEY_EVT, 0, key_hook, &vars);
	mlx_hook(vars.win, EXIT_EVT, 0, ft_exit, 0);
	mlx_loop_hook(vars.mlx, paint_map, &vars);
	mlx_loop(vars.mlx);
	exit(0);
}
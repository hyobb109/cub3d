#include "cub3d.h"

static void	check_args(int ac, char **av)
{
	char	*tmp;

	if (ac != 2)
		print_error_exit("You need an argument");
	tmp = ft_strnstr(av[1], ".cub", ft_strlen(av[1]));
	if (ft_strncmp(tmp, ".cub", 5))
	{
		printf("%s\n", av[1]);
		print_error_exit("Not a valid extension");
	}
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
	check_element(&vars);
	measure_map_size(&vars);
	validate_map(&vars);
	printf("valid\n");
	vars.win = mlx_new_window(vars.mlx, BLOCK_SIZE * vars.map_x,
			BLOCK_SIZE * vars.map_y, "cub3D");
	// if (!vars.win)
	// 	print_error_exit(0);
	vars.img.ptr = mlx_new_image(vars.mlx, BLOCK_SIZE * vars.map_x, BLOCK_SIZE * vars.map_y);
	vars.img.addr = mlx_get_data_addr(vars.img.ptr, &vars.img.bpp, &vars.img.len, &vars.img.endian);
	// paint_map(&vars);
	mlx_hook(vars.win, KEY_EVT, 0, key_hook, &vars);
	mlx_hook(vars.win, EXIT_EVT, 0, ft_exit, 0);
	mlx_loop_hook(vars.mlx, paint_map, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
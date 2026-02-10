#include "minirt.h"

int	main(int argc, char **argv)
{
	t_scene	scene;
	mlx_t	*mlx;

	if (argc != 2)
		error_exit("Error: Usage: ./miniRT <scene.rt>");
	ft_memset(&scene, 0, sizeof(t_scene));
	init_parser(argv[1], &scene);
	mlx = mlx_init(800, 600, "miniRT", false);
	if (!mlx)
		return (1);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

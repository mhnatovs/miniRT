#include <MLX42/MLX42.h>
#include <stdlib.h>

int	main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(800, 600, "miniRT", false);
	if (!mlx)
		return (1);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

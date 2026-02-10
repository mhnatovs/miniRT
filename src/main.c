#include "minirt.h"

#define WIDTH 800
#define HEIGHT 600

// int	main(int argc, char **argv)
// {
// 	t_scene	scene;
// 	mlx_t	*mlx;

// 	if (argc != 2)
// 		error_exit("Error: Usage: ./miniRT <scene.rt>");
// 	ft_memset(&scene, 0, sizeof(t_scene));
// 	init_parser(argv[1], &scene);
// 	mlx = mlx_init(800, 600, "miniRT", false);
// 	if (!mlx)
// 		return (1);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (0);
// }
void	put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (x < 0 || x >= (int)img->width || y < 0 || y >= (int)img->height)
		return;
	mlx_put_pixel(img, x, y, color);
}

int main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (!mlx)
		return (1);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		return (1);
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			uint32_t color = ((x * 255 / WIDTH) << 24)
			   				 | ((y * 255 / HEIGHT) << 16)
			   				 | (0 << 8)
			   				 | 255;
			put_pixel(img, x, y, color);
		}
	}
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
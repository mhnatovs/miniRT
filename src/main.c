/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 21:18:42 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/15 21:06:38 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

static void	resize_hook(int32_t width, int32_t height, void *param)
{
	mlx_image_t	*img;

	img = param;
	mlx_resize_image(img, width, height);
}

int	main(int argc, char **argv)
{
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*img;

	if (argc != 2)
		error_exit("Usage: ./miniRT <scene.rt>");
	ft_memset(&scene, 0, sizeof(t_scene));
	init_parser(argv[1], &scene);
	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		return (ft_lstclear(&scene.objects, free), 1);
	mlx_key_hook(mlx, &key_hook, mlx);
	img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!img)
		return (mlx_terminate(mlx), ft_lstclear(&scene.objects, free), 1);
	render_scene(img, scene);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_resize_hook(mlx, &resize_hook, img);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	ft_lstclear(&scene.objects, free);
	return (0);
}

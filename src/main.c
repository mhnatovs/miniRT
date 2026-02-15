/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 21:18:42 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/15 13:12:52 by mhnatovs         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*img;

	if (argc != 2)
		error_exit("Usage: ./miniRT <scene.rt>");
	ft_memset(&scene, 0, sizeof(t_scene));
	init_parser(argv[1], &scene);
	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (!mlx)
	{
		free_scene(&scene);
		return (1);
	}
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
	{
		mlx_terminate(mlx);
		free_scene(&scene);
		return (1);
	}
	mlx_key_hook(mlx, &key_hook, mlx);
	render_scene(img, scene);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	free_scene(&scene);
	return (0);
}

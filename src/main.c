/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 21:18:42 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/12 21:19:02 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_scene		scene;
	mlx_t		*mlx;
	mlx_image_t	*img;

	if (argc != 2)
		error_exit("Error: Usage: ./miniRT <scene.rt>");
	ft_memset(&scene, 0, sizeof(t_scene));
	init_parser(argv[1], &scene);
	mlx = mlx_init(800, 600, "miniRT", false);
	if (!mlx)
		return (1);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

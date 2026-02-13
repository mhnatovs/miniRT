/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 21:18:42 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/13 16:34:48 by mhnatovs         ###   ########.fr       */
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

// will change this function later
void	render_scene(mlx_image_t *img, t_scene scene)
{
	int			x;
	int			y;
	t_viewport	vp;
	t_ray		ray;
	float		t;
	uint32_t	color;

	vp = init_viewport(scene.camera);
	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			t = -1.0;
			ray = generate_ray(scene.camera, vp, x, y);
			t_list	*obj_node = scene.objects;
			if (obj_node)
			{
				t_object	*obj = (t_object *)obj_node->content;
				if (obj->type == OBJ_SPHERE)
				{
					t_sphere	sphere = obj->data.sphere;
					t = intersect_sphere(ray, sphere);
				}
			}
			if (t > 0)
				color = 0x0F0000FF;
			else
				color = 0x00000000;
			mlx_put_pixel(img, x, y, color);
		}
	}
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
		return (1);
	mlx_key_hook(mlx, &key_hook, mlx);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		return (1);
	render_scene(img, scene);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}

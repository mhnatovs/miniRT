/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 12:06:41 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/04/13 16:20:37 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	horizontal_movement(t_context *cont, float speed)
{
	t_vector	move;

	move = vector_scale(cont->scene.camera.dir, speed);
	cont->scene.camera.pos = vector_add(cont->scene.camera.pos, move);
	re_render(cont);
}

static void	left_right_movement(t_context *cont, float speed)
{
	t_vector	move;
	t_viewport	vp;

	vp = init_viewport(cont->scene.camera);
	move = vector_scale(vp.right, speed);
	cont->scene.camera.pos = vector_add(cont->scene.camera.pos, move);
	re_render(cont);
}

static void	vertical_movement(t_context *cont, float speed)
{
	t_viewport	vp;
	t_vector	move;

	vp = init_viewport(cont->scene.camera);
	move = vector_scale(vp.up, speed);
	cont->scene.camera.pos = vector_add(cont->scene.camera.pos, move);
	re_render(cont);
}

void	move_camera(t_context *cont, mlx_key_data_t key)
{
	float	speed;

	speed = 4.0;
	if (key.key == MLX_KEY_W && (key.action == MLX_PRESS
			|| key.action == MLX_REPEAT))
		horizontal_movement(cont, speed);
	else if (key.key == MLX_KEY_S && (key.action == MLX_PRESS
			|| key.action == MLX_REPEAT))
		horizontal_movement(cont, -speed);
	if (key.key == MLX_KEY_A && (key.action == MLX_PRESS
			|| key.action == MLX_REPEAT))
		left_right_movement(cont, -speed);
	else if (key.key == MLX_KEY_D && (key.action == MLX_PRESS
			|| key.action == MLX_REPEAT))
		left_right_movement(cont, speed);
	if (key.key == MLX_KEY_Q && (key.action == MLX_PRESS
			|| key.action == MLX_REPEAT))
		vertical_movement(cont, speed);
	else if (key.key == MLX_KEY_E && (key.action == MLX_PRESS
			|| key.action == MLX_REPEAT))
		vertical_movement(cont, -speed);
}

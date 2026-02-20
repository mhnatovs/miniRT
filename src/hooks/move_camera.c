/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:34:17 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/20 16:30:10 by mhnatovs         ###   ########.fr       */
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
	t_vector	move;

	move = (t_vector){0, speed, 0};
	cont->scene.camera.pos = vector_add(cont->scene.camera.pos, move);
	re_render(cont);
}

void	move_camera(t_context *cont, mlx_key_data_t key)
{
	float		speed;

	speed = 2.0;
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

void	rotate_camera(t_context *cont, mlx_key_data_t key)
{
	float		angle;
	t_vector	new_dir;
	float		cos_a;
	float		sin_a;

	if (cont->selected_obj)
		return ;
	angle = 0.5;
	if (key.key == MLX_KEY_Z && (key.action == MLX_PRESS
			|| key.action == MLX_REPEAT))
	{
		cos_a = cos(angle);
		sin_a = sin(angle);
		new_dir.x = cont->scene.camera.dir.x * cos_a
			+ cont->scene.camera.dir.z * sin_a;
		new_dir.y = cont->scene.camera.dir.y;
		new_dir.z = -cont->scene.camera.dir.x * sin_a
			+ cont->scene.camera.dir.z * cos_a;
		cont->scene.camera.dir = vector_normalize(new_dir);
		re_render(cont);
	}
	else if (key.key == MLX_KEY_X && (key.action == MLX_PRESS
			|| key.action == MLX_REPEAT))
	{
		angle = -angle;
		cos_a = cos(angle);
		sin_a = sin(angle);
		new_dir.x = cont->scene.camera.dir.x * cos_a
			+ cont->scene.camera.dir.z * sin_a;
		new_dir.y = cont->scene.camera.dir.y;
		new_dir.z = -cont->scene.camera.dir.x * sin_a
			+ cont->scene.camera.dir.z * cos_a;
		cont->scene.camera.dir = vector_normalize(new_dir);
		re_render(cont);
	}
}

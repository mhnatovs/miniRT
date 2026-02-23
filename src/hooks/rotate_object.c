/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:00:00 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/22 19:00:00 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	rotate_yaw(t_vector v, float angle)
{
	float		cos_a;
	float		sin_a;
	t_vector	result;

	cos_a = cos(angle);
	sin_a = sin(angle);
	result.x = v.x * cos_a + v.z * sin_a;
	result.y = v.y;
	result.z = -v.x * sin_a + v.z * cos_a;
	return (vector_normalize(result));
}

static t_vector	rotate_pitch(t_vector v, float angle)
{
	float		cos_a;
	float		sin_a;
	t_vector	result;

	cos_a = cos(angle);
	sin_a = sin(angle);
	result.x = v.x;
	result.y = v.y * cos_a - v.z * sin_a;
	result.z = v.y * sin_a + v.z * cos_a;
	return (vector_normalize(result));
}

static void	apply_rotation(t_object *o, int key, float angle)
{
	t_vector	*dir;

	if (o->type == OBJ_SPHERE)
		return ;
	if (o->type == OBJ_PLANE)
		dir = &o->data.plane.normal;
	else
		dir = &o->data.cylinder.dir;
	if (key == MLX_KEY_R)
		*dir = rotate_yaw(*dir, angle);
	else if (key == MLX_KEY_F)
		*dir = rotate_yaw(*dir, -angle);
	else if (key == MLX_KEY_T)
		*dir = rotate_pitch(*dir, angle);
	else if (key == MLX_KEY_G)
		*dir = rotate_pitch(*dir, -angle);
}

void	rotate_object(t_context *ctx, mlx_key_data_t key)
{
	t_object	*o;
	float		angle;

	o = ctx->selected_obj;
	if (!o || (key.action != MLX_PRESS && key.action != MLX_REPEAT))
		return ;
	if (key.key != MLX_KEY_R && key.key != MLX_KEY_F
		&& key.key != MLX_KEY_T && key.key != MLX_KEY_G)
		return ;
	angle = 0.1f;
	apply_rotation(o, key.key, angle);
	re_render(ctx);
}

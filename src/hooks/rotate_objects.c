/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:09:50 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/27 18:11:32 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
**  Rotate a vector `v` about an arbitrary unit axis using Rodrigues'
**  rotation formula.  This gives us the freedom to spin cylinders and
**  planes around any axis we choose rather than being locked to the
**  world Y axis.  The old `rotate_y` helper lived here and only worked
**  when the axis was (0,1,0).  When an object's orientation is
**  parallel to the rotation axis the result is identical to the input
**  vector; this is why a vertical cylinder or horizontal plane seemed to
**  "not rotate" when you pressed R/T in your original implementation.
*/

static t_vector	rotate_vector(t_vector v, t_vector axis, float angle)
{
	float		cos_a;
	float		sin_a;
	t_vector	cross;
	t_vector	scaled_axis;

	cos_a = cos(angle);
	sin_a = sin(angle);
	cross = vector_cross(axis, v);
	scaled_axis = vector_scale(axis, vector_dot(axis, v) * (1 - cos_a));
	return (vector_add(
			vector_scale(v, cos_a),
			vector_add(vector_scale(cross, sin_a), scaled_axis)));
}

static void	rotate_cylinder_axis(t_object *o, t_vector axis, float angle)
{
	if (o->type != OBJ_CYLINDER)
		return ;
	o->data.cylinder.dir = vector_normalize(
			rotate_vector(o->data.cylinder.dir, axis, angle));
}

static void	rotate_plane_axis(t_object *o, t_vector axis, float angle)
{
	if (o->type != OBJ_PLANE)
		return ;
	o->data.plane.normal = vector_normalize(
			rotate_vector(o->data.plane.normal, axis, angle));
}

static int	get_rotation_from_key(mlx_key_data_t key,
		t_vector *axis, float *angle)
{
	*angle = 0.1f;
	if (key.key == MLX_KEY_R)
		*axis = (t_vector){0, 1, 0};
	else if (key.key == MLX_KEY_T)
	{
		*axis = (t_vector){0, 1, 0};
		*angle = -*angle;
	}
	else if (key.key == MLX_KEY_Y)
		*axis = (t_vector){0, 0, 1};
	else if (key.key == MLX_KEY_U)
	{
		*axis = (t_vector){0, 0, 1};
		*angle = -*angle;
	}
	else
		return (0);
	return (1);
}

// keys U,Z to pitch/roll the object
// keys R,T to yaw the object
void	rotate_object(t_context *ctx, mlx_key_data_t key)
{
	float		angle;
	t_vector	axis;
	t_object	*obj;

	obj = ctx->selected_obj;
	if (!obj || (key.action != MLX_PRESS && key.action != MLX_REPEAT))
		return ;
	if (!get_rotation_from_key(key, &axis, &angle))
		return ;
	if (obj->type == OBJ_CYLINDER || obj->type == OBJ_PLANE)
	{
		rotate_cylinder_axis(obj, axis, angle);
		rotate_plane_axis(obj, axis, angle);
		re_render(ctx);
	}
}

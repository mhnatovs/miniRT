/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 10:57:28 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/02 14:31:25 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	get_move_vector(t_context *ctx, double dx, double dy)
{
	t_viewport	vp;
	float		dist;
	float		sx;
	float		sy;

	vp = init_viewport(ctx->scene.camera);
	dist = vector_length(vector_substract(get_obj_pos(ctx->selected_obj),
				ctx->scene.camera.pos));
	sx = (2.0f * vp.fov_scale * vp.aspect_ratio * dist) / WIDTH;
	sy = (2.0f * vp.fov_scale * dist) / HEIGHT;
	return (vector_add(vector_scale(vp.right, dx * sx), vector_scale(vp.up, -dy
				* sy)));
}

static float	sphere_plane_depth(t_sphere sp, t_plane pl)
{
	return (vector_dot(vector_substract(sp.center, pl.point), pl.normal)
		- sp.radius);
}

// compute penetration depth of a cylinder against a plane
static float	cylinder_plane_depth(t_cylinder cyl, t_vector pos, t_plane pl)
{
	float		dist0;
	float		dist1;
	float		offset;
	t_vector	top;
	float		dot_dn;

	top = vector_add(pos, vector_scale(cyl.dir, cyl.height));
	dist0 = vector_dot(vector_substract(pos, pl.point), pl.normal);
	dist1 = vector_dot(vector_substract(top, pl.point), pl.normal);
	dot_dn = vector_dot(cyl.dir, pl.normal);
	offset = cyl.radius * sqrtf(1.0f - dot_dn * dot_dn);
	return (fminf(dist0, dist1) - offset);
}

void	move_object_drag(t_context *ctx, double dx, double dy)
{
	t_vector	move;
	t_vector	next_pos;
	t_vector	cur_pos;
	t_list		*node;
	t_object	*other;

	if (!ctx->selected_obj || ctx->selected_obj->type == OBJ_PLANE)
		return ;
	move = get_move_vector(ctx, dx, dy);
	cur_pos = get_obj_pos(ctx->selected_obj);
	next_pos = vector_add(cur_pos, move);
	if (!is_colliding(ctx, ctx->selected_obj, next_pos))
	{
		update_pos(ctx->selected_obj, move);
		ctx->intended_pos = get_obj_pos(ctx->selected_obj);
		re_render(ctx);
		return ;
	}
	node = ctx->scene.objects;
	while (node)
	{
		other = node->content;
		if (other != ctx->selected_obj && other->type == OBJ_PLANE)
		{
			float depth;
			if (ctx->selected_obj->type == OBJ_SPHERE)
				depth = sphere_plane_depth(ctx->selected_obj->data.sphere,
					other->data.plane);
			else
				depth = cylinder_plane_depth(ctx->selected_obj->data.cylinder,
					cur_pos, other->data.plane);
			if (depth < 0.0f)
			{
				float dotm = vector_dot(move, other->data.plane.normal);
				t_vector move_proj = vector_substract(move,
					vector_scale(other->data.plane.normal, dotm));
				t_vector try_pos = vector_add(cur_pos, move_proj);
				if (!is_colliding(ctx, ctx->selected_obj, try_pos))
				{
					update_pos(ctx->selected_obj, move_proj);
					ctx->intended_pos = get_obj_pos(ctx->selected_obj);
					re_render(ctx);
					return ;
				}
			}
		}
		node = node->next;
	}
}

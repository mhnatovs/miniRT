/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 10:57:28 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/21 11:07:09 by jiyawang         ###   ########.fr       */
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

void	move_object_drag(t_context *ctx, double dx, double dy)
{
	t_vector	move;
	t_vector	next_pos;

	if (!ctx->selected_obj || ctx->selected_obj->type == OBJ_PLANE)
		return ;
	move = get_move_vector(ctx, dx, dy);
	next_pos = vector_add(get_obj_pos(ctx->selected_obj), move);
	if (!is_colliding(ctx, ctx->selected_obj, next_pos))
	{
		update_pos(ctx->selected_obj, move);
		ctx->intended_pos = get_obj_pos(ctx->selected_obj);
		re_render(ctx);
	}
}

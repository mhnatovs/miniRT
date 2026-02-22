/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_scroll.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 10:56:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/21 10:56:02 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	fov_zoom(t_context *ctx, double ydelta)
{
	ctx->scene.camera.fov -= (int)ydelta * 2;
	if (ctx->scene.camera.fov < 1)
		ctx->scene.camera.fov = 1;
	if (ctx->scene.camera.fov > 179)
		ctx->scene.camera.fov = 179;
	re_render(ctx);
}

static void	object_scale(t_context *ctx, double ydelta)
{
	float	scale;

	if (ydelta > 0)
		scale = 1.05f;
	else
		scale = 0.95f;
	if (ctx->selected_obj->type == OBJ_SPHERE)
		ctx->selected_obj->data.sphere.radius *= scale;
	else if (ctx->selected_obj->type == OBJ_CYLINDER)
	{
		ctx->selected_obj->data.cylinder.radius *= scale;
		ctx->selected_obj->data.cylinder.height *= scale;
	}
	update_pos(ctx->selected_obj, vector_substract(ctx->intended_pos,
			get_obj_pos(ctx->selected_obj)));
	resolve_scaling_collision(ctx, ctx->selected_obj);
	re_render(ctx);
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_context	*ctx;

	(void)xdelta;
	ctx = (t_context *)param;
	if (!ctx)
		return ;
	if (!ctx->selected_obj)
		fov_zoom(ctx, ydelta);
	else
		object_scale(ctx, ydelta);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:11:09 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/20 15:37:42 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	re_render(t_context *ctx)
{
	render_scene(ctx->img, ctx->scene);
}

void	modify_object(t_context *ctx, mlx_key_data_t keydata)
{
	if (!ctx->selected_obj)
		return ;
	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		if (ctx->selected_obj->type == OBJ_SPHERE)
			ctx->selected_obj->data.sphere.radius += 0.5;
		else if (ctx->selected_obj->type == OBJ_CYLINDER)
			ctx->selected_obj->data.cylinder.height += 0.5;
		re_render(ctx);
	}
	else if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		if (ctx->selected_obj->type == OBJ_SPHERE)
			ctx->selected_obj->data.sphere.radius -= 0.5;
		else if (ctx->selected_obj->type == OBJ_CYLINDER)
			ctx->selected_obj->data.cylinder.height -= 0.5;
		if (ctx->selected_obj->type == OBJ_SPHERE
			&& ctx->selected_obj->data.sphere.radius < 0.1)
			ctx->selected_obj->data.sphere.radius = 0.1;
		else if (ctx->selected_obj->type == OBJ_CYLINDER
			&& ctx->selected_obj->data.cylinder.radius < 0.1)
			ctx->selected_obj->data.cylinder.height = 0.1;
		re_render(ctx);
	}
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		if (ctx->selected_obj->type == OBJ_CYLINDER)
		{
			ctx->selected_obj->data.cylinder.radius += 0.5;
			re_render(ctx);
		}
	}
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		if (ctx->selected_obj->type == OBJ_CYLINDER)
		{
			ctx->selected_obj->data.cylinder.radius -= 0.5;
			if (ctx->selected_obj->data.cylinder.radius < 0.1)
				ctx->selected_obj->data.cylinder.radius = 0.1;
			re_render(ctx);
		}
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_context	*ctx;

	ctx = (t_context *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(ctx->mlx);
	move_camera(ctx, keydata);
	rotate_camera(ctx, keydata);
	modify_object(ctx, keydata);
}

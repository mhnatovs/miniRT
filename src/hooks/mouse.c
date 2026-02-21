/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 10:55:48 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/21 10:56:42 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	handle_left_press(t_context *ctx)
{
	int32_t	pos[2];
	t_hit	hit;

	mlx_get_mouse_pos(ctx->mlx, &pos[0], &pos[1]);
	if (pos[0] < 0 || pos[0] >= WIDTH || pos[1] < 0 || pos[1] >= HEIGHT)
		return ;
	hit = trace_ray_selection(generate_ray(ctx->scene.camera,
				init_viewport(ctx->scene.camera), pos[0], pos[1]),
			ctx->scene);
	ctx->selected_obj = hit.obj;
	ctx->prev_mouse[0] = (double)pos[0];
	ctx->prev_mouse[1] = (double)pos[1];
	if (hit.obj)
	{
		ctx->intended_pos = get_obj_pos(hit.obj);
		ctx->is_dragging = true;
		ft_putstr_fd("Object selected & Dragging started\n", 1);
	}
	else
		ft_putstr_fd("Selection cleared\n", 1);
}

static void	handle_left_click(t_context *ctx, action_t action)
{
	if (action == MLX_PRESS)
		handle_left_press(ctx);
	else if (action == MLX_RELEASE)
	{
		if (ctx->is_dragging)
			ft_putstr_fd("Dragging stopped\n", 1);
		ctx->is_dragging = false;
	}
}

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_context	*ctx;

	(void)mods;
	ctx = (t_context *)param;
	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
	{
		ctx->selected_obj = NULL;
		ctx->is_dragging = false;
		ft_putstr_fd("Selection cleared\n", 1);
		return ;
	}
	if (button == MLX_MOUSE_BUTTON_LEFT)
		handle_left_click(ctx, action);
}

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_context	*ctx;
	double		dx;
	double		dy;

	ctx = (t_context *)param;
	if (ctx->is_dragging && ctx->selected_obj)
	{
		dx = xpos - ctx->prev_mouse[0];
		dy = ypos - ctx->prev_mouse[1];
		move_object_drag(ctx, dx, dy);
	}
	ctx->prev_mouse[0] = xpos;
	ctx->prev_mouse[1] = ypos;
}

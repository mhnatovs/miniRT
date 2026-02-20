/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 09:11:18 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/20 14:33:13 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_context	*ctx;
	int			pos[2];
	t_hit		hit;

	(void)mods;
	ctx = (t_context *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx_get_mouse_pos(ctx->mlx, &pos[0], &pos[1]);
		if (pos[0] < 0 || pos[0] >= WIDTH || pos[1] < 0 || pos[1] >= HEIGHT)
			return ;
		hit = trace_ray(generate_ray(ctx->scene.camera,
					init_viewport(ctx->scene.camera), pos[0], pos[1]),
				ctx->scene);
		ctx->selected_obj = hit.obj;
		if (hit.obj)
			ft_putstr_fd("Object selected\n", 1);
		else
			ft_putstr_fd("Selection cleared\n", 1);
	}
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_context	*ctx;
	float		scale;

	(void)xdelta;
	ctx = (t_context *)param;
	if (!ctx || !ctx->selected_obj)
		return ;
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
	render_scene(ctx->img, ctx->scene);
}

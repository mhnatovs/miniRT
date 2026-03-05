/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 20:49:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/03 20:49:02 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	re_render(t_context *ctx)
{
	int	step;

	step = 1;
	if (ctx->needs_rerender)
		step = 4;
	render_scene(ctx->img, ctx->scene, step);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_context	*ctx;

	ctx = (t_context *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(ctx->mlx);
	move_camera(ctx, keydata);
	rotate_camera(ctx, keydata);
}

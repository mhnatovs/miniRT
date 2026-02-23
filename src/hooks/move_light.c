/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:00:00 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/22 19:00:00 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move_light(t_context *ctx, mlx_key_data_t key)
{
	float	speed;

	speed = 2.0f;
	if (key.action != MLX_PRESS && key.action != MLX_REPEAT)
		return ;
	if (key.key == MLX_KEY_I)
		ctx->scene.light.pos.y += speed;
	else if (key.key == MLX_KEY_K)
		ctx->scene.light.pos.y -= speed;
	else if (key.key == MLX_KEY_J)
		ctx->scene.light.pos.x -= speed;
	else if (key.key == MLX_KEY_L)
		ctx->scene.light.pos.x += speed;
	else if (key.key == MLX_KEY_U)
		ctx->scene.light.pos.z -= speed;
	else if (key.key == MLX_KEY_O)
		ctx->scene.light.pos.z += speed;
	else
		return ;
	re_render(ctx);
}

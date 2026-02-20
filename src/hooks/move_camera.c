/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 14:34:17 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/20 14:57:28 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minirt.h"

// void	move_camera(t_context *cont, mlx_key_data_t key)
// {
// 	t_vector	move;
// 	t_viewport	vp;
// 	float		speed;

// 	speed = 2.0;
// 	if (key.key == MLX_KEY_W && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
// 	{
// 		move = vector_scale(cont->scene.camera.dir, speed);
// 		cont->scene.camera.pos = vector_add(cont->scene.camera.pos, move);
// 		re_trender(cont);
// 	}
// 	else if (key.key == MLX_KEY_S && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
// 	{
// 		move = vector_scale(cont->scene.camera.dir, -speed);
// 		cont->scene.camera.pos = vector_add(cont->scene.camera.pos, move);
// 		re_render(cont);
// 	}
// 	if (key.key == MLX_KEY_A && (key.action == MLX_PRESS || key.action == MLX_REPEAT))
// 	{
		
// 	}
// 	}
// }

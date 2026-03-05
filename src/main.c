/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 20:48:17 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/03 20:48:18 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_context	*ctx;

	ctx = param;
	mlx_resize_image(ctx->img, width, height);
}

static void	render_loop(void *param)
{
	t_context	*ctx;

	ctx = (t_context *)param;
	if (ctx->needs_rerender && (mlx_get_time() - ctx->last_input_time > 0.15))
	{
		render_scene(ctx->img, ctx->scene, 1);
		ctx->needs_rerender = false;
	}
}

static void	setup_hooks(t_context *ctx)
{
	mlx_key_hook(ctx->mlx, &key_hook, ctx);
	mlx_scroll_hook(ctx->mlx, &scroll_hook, ctx);
	mlx_resize_hook(ctx->mlx, &resize_hook, ctx);
	mlx_loop_hook(ctx->mlx, &render_loop, ctx);
}

int	main(int argc, char **argv)
{
	t_context	ctx;

	if (argc != 2)
		error_exit("Usage: ./miniRT <scene.rt>\n");
	ft_memset(&ctx, 0, sizeof(t_context));
	init_parser(argv[1], &ctx.scene);
	ctx.mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!ctx.mlx)
		return (free_bvh(ctx.scene.objects), 1);
	ctx.img = mlx_new_image(ctx.mlx, WIDTH, HEIGHT);
	if (!ctx.img)
		return (mlx_terminate(ctx.mlx), free_bvh(ctx.scene.objects), 1);
	render_scene(ctx.img, ctx.scene, 1);
	mlx_image_to_window(ctx.mlx, ctx.img, 0, 0);
	setup_hooks(&ctx);
	mlx_loop(ctx.mlx);
	mlx_delete_image(ctx.mlx, ctx.img);
	mlx_terminate(ctx.mlx);
	return (0);
}

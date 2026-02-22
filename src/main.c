/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 10:53:41 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/21 12:03:47 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_context	*ctx;

	ctx = param;
	mlx_resize_image(ctx->img, width, height);
}

int	main(int argc, char **argv)
{
	t_context	ctx;

	if (argc != 2)
		error_exit("Usage: ./miniRT <scene.rt>");
	ft_memset(&ctx, 0, sizeof(t_context));
	init_parser(argv[1], &ctx.scene);
	ctx.mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!ctx.mlx)
		return (ft_lstclear(&ctx.scene.objects, free), 1);
	ctx.img = mlx_new_image(ctx.mlx, WIDTH, HEIGHT);
	if (!ctx.img)
		return (mlx_terminate(ctx.mlx), ft_lstclear(&ctx.scene.objects, free),
			1);
	render_scene(ctx.img, ctx.scene);
	mlx_image_to_window(ctx.mlx, ctx.img, 0, 0);
	mlx_key_hook(ctx.mlx, &key_hook, &ctx);
	mlx_mouse_hook(ctx.mlx, &mouse_hook, &ctx);
	mlx_cursor_hook(ctx.mlx, &cursor_hook, &ctx);
	mlx_scroll_hook(ctx.mlx, &scroll_hook, &ctx);
	mlx_resize_hook(ctx.mlx, &resize_hook, &ctx);
	mlx_loop(ctx.mlx);
	mlx_delete_image(ctx.mlx, ctx.img);
	mlx_terminate(ctx.mlx);
	ft_lstclear(&ctx.scene.objects, free);
	return (0);
}

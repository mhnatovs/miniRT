
#include "minirt.h"

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_context	*ctx;
	int			x;
	int			y;
	t_viewport	vp;
	t_ray		ray;
	t_hit		hit;

	(void)mods;
	ctx = (t_context *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx_get_mouse_pos(ctx->mlx, &x, &y);
		if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
			return ;
		vp = init_viewport(ctx->scene.camera);
		ray = generate_ray(ctx->scene.camera, vp, x, y);
		hit = trace_ray(ray, ctx->scene);
		if (hit.obj)
		{
			ctx->selected_obj = hit.obj;
			ft_putstr_fd("Object selected\n", 1);
		}
		else
		{
			ctx->selected_obj = NULL;
			ft_putstr_fd("Selection cleared\n", 1);
		}
	}
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_context		*ctx;
	mlx_key_data_t	fake_key;

	(void)xdelta;
	ctx = (t_context *)param;
	if (!ctx->selected_obj)
		return ;
	ft_memset(&fake_key, 0, sizeof(mlx_key_data_t));
	fake_key.action = MLX_PRESS;
	if (ydelta > 0)
		fake_key.key = MLX_KEY_UP;
	else if (ydelta < 0)
		fake_key.key = MLX_KEY_DOWN;
	else
		return ;
	modify_object(ctx, fake_key);
}

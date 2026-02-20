
#include "minirt.h"

void	mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_context	*ctx;
	int32_t		pos[2];
	t_hit		hit;

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

	{
		if (action == MLX_PRESS)
		{
			mlx_get_mouse_pos(ctx->mlx, &pos[0], &pos[1]);
			if (pos[0] < 0 || pos[0] >= WIDTH || pos[1] < 0 || pos[1] >= HEIGHT)
				return ;
			hit = trace_ray(generate_ray(ctx->scene.camera,
						init_viewport(ctx->scene.camera), pos[0], pos[1]),
					ctx->scene);
			ctx->selected_obj = hit.obj;
			ctx->prev_mouse[0] = (double)pos[0];
			ctx->prev_mouse[1] = (double)pos[1];
			if (hit.obj)
			{
				ctx->is_dragging = true;
				ft_putstr_fd("Object selected & Dragging started\n", 1);
			}
			else
				ft_putstr_fd("Selection cleared\n", 1);
		}
		else if (action == MLX_RELEASE)
		{
			if (ctx->is_dragging)
				ft_putstr_fd("Dragging stopped\n", 1);
			ctx->is_dragging = false;
		}

	}
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

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_context	*ctx;
	float		scale;

	(void)xdelta;
	ctx = (t_context *)param;
	if (!ctx)
		return ;
	if (!ctx->selected_obj)
	{
		ctx->scene.camera.fov -= (int)ydelta * 2;
		if (ctx->scene.camera.fov < 1)
			ctx->scene.camera.fov = 1;
		if (ctx->scene.camera.fov > 179)
			ctx->scene.camera.fov = 179;
	}
	else
	{
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
	}
	render_scene(ctx->img, ctx->scene);
}


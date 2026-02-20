
#include "minirt.h"

void	re_render(t_context *ctx)
{
	render_scene(ctx->img, ctx->scene);
}

static void	update_object_params(t_object *o, int key, float d)
{
	if (key == MLX_KEY_UP || key == MLX_KEY_DOWN)
	{
		if (o->type == OBJ_SPHERE)
			o->data.sphere.radius += d;
		else if (o->type == OBJ_CYLINDER)
			o->data.cylinder.height += d;
	}
	else if ((key == MLX_KEY_RIGHT || key == MLX_KEY_LEFT)
		&& o->type == OBJ_CYLINDER)
		o->data.cylinder.radius += d;
	if (o->type == OBJ_SPHERE && o->data.sphere.radius < 0.1f)
		o->data.sphere.radius = 0.1f;
	if (o->type == OBJ_CYLINDER && o->data.cylinder.height < 0.1f)
		o->data.cylinder.height = 0.1f;
	if (o->type == OBJ_CYLINDER && o->data.cylinder.radius < 0.1f)
		o->data.cylinder.radius = 0.1f;
}

void	modify_object(t_context *ctx, mlx_key_data_t key)
{
	t_object	*o;
	float		d;

	o = ctx->selected_obj;
	if (!o || (key.action != MLX_PRESS && key.action != MLX_REPEAT))
		return ;
	d = -0.5f;
	if (key.key == MLX_KEY_UP || key.key == MLX_KEY_RIGHT)
		d = 0.5f;
	if (key.key != MLX_KEY_UP && key.key != MLX_KEY_DOWN
		&& key.key != MLX_KEY_LEFT && key.key != MLX_KEY_RIGHT)
		return ;
	update_object_params(o, key.key, d);
	re_render(ctx);
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


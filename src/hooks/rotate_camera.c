
#include "minirt.h"

static void	yaw_rotation(float angle, t_context *cont)
{
	float		cos_a;
	float		sin_a;
	t_vector	new_dir;

	cos_a = cos(angle);
	sin_a = sin(angle);
	new_dir.x = cont->scene.camera.dir.x * cos_a
		+ cont->scene.camera.dir.z * sin_a;
	new_dir.y = cont->scene.camera.dir.y;
	new_dir.z = -cont->scene.camera.dir.x * sin_a
		+ cont->scene.camera.dir.z * cos_a;
	cont->scene.camera.dir = vector_normalize(new_dir);
	cont->needs_rerender = true;
	cont->last_input_time = mlx_get_time();
	re_render(cont);
}

void	rotate_camera(t_context *cont, mlx_key_data_t key)
{
	float		angle;

	angle = 0.2;
	if (key.key == MLX_KEY_Z && (key.action == MLX_PRESS
			|| key.action == MLX_REPEAT))
		yaw_rotation(angle, cont);
	else if (key.key == MLX_KEY_X && (key.action == MLX_PRESS
			|| key.action == MLX_REPEAT))
		yaw_rotation(-angle, cont);
}

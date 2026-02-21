
#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 100
# define HEIGHT 80

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# include "../libft/libft.h"
# include "MLX42/MLX42.h"
# include "vector.h"
# include "parser.h"
# include "render.h"
# include "intersection.h"

typedef struct s_context
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		scene;
	t_object	*selected_obj;
	double		prev_mouse[2];
	bool		is_dragging;
	t_vector	intended_pos;
}				t_context;

void			error_exit(char *msg);
void			re_render(t_context *ctx);
void			modify_object(t_context *ctx, mlx_key_data_t keydata);
void			key_hook(mlx_key_data_t keydata, void *param);
void			mouse_hook(mouse_key_t button, action_t action,
					modifier_key_t mods, void *param);
void			scroll_hook(double xdelta, double ydelta, void *param);
void			cursor_hook(double xpos, double ypos, void *param);
void			move_camera(t_context *cont, mlx_key_data_t key);
void			rotate_camera(t_context *cont, mlx_key_data_t key);
void			move_object_drag(t_context *ctx, double dx, double dy);
bool			is_colliding(t_context *ctx, t_object *o, t_vector next_pos);
t_vector		get_obj_pos(t_object *o);
void			update_pos(t_object *o, t_vector move);
void			resolve_scaling_collision(t_context *ctx, t_object *o);
t_hit			trace_ray_selection(t_ray ray, t_scene scene);

#endif
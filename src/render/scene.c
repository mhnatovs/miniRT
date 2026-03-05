
#include "minirt.h"

uint32_t	get_pixel_color(t_scene scene, t_viewport vp, t_point p)
{
	t_ray		ray;
	t_hit		hit;
	uint32_t	color;

	ray = generate_ray(scene.camera, vp, p.x, p.y);
	hit = trace_ray(ray, scene);
	if (hit.t > 0.001f)
		color = color_to_int(calc_color(hit, scene, ray.direction));
	else
		color = 0x000000FF;
	return (color);
}

static void	put_block(mlx_image_t *img, t_point p, int step, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < step && (p.y + i) < HEIGHT)
	{
		j = 0;
		while (j < step && (p.x + j) < WIDTH)
		{
			if (step > 1)
				mlx_put_pixel(img, p.x + j, p.y + i, color);
			else
				mlx_put_pixel(img, p.x, p.y, color);
			j++;
		}
		i++;
	}
}

void	render_scene(mlx_image_t *img, t_scene scene, int step)
{
	t_viewport	vp;
	t_point		p;

	p.y = 0;
	vp = init_viewport(scene.camera);
	while (p.y < HEIGHT)
	{
		p.x = 0;
		while (p.x < WIDTH)
		{
			put_block(img, p, step, get_pixel_color(scene, vp, p));
			p.x += step;
		}
		p.y += step;
	}
}

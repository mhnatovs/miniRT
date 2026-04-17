/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:03:37 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/04/13 15:55:37 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define WIDTH 800
# define HEIGHT 600

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
}				t_context;

void			error_exit(char *msg);
void			re_render(t_context *ctx);
void			key_hook(mlx_key_data_t keydata, void *param);
void			scroll_hook(double xdelta, double ydelta, void *param);
void			move_camera(t_context *cont, mlx_key_data_t key);
void			rotate_camera(t_context *cont, mlx_key_data_t key);

#endif

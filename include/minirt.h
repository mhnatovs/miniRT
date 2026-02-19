/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:05:14 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/19 16:00:54 by jiyawang         ###   ########.fr       */
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
	t_object	*selected_obj;
}				t_context;

void			error_exit(char *msg);
void			key_hook(mlx_key_data_t keydata, void *param);
void			mouse_hook(mouse_key_t button, action_t action,
					modifier_key_t mods, void *param);

#endif
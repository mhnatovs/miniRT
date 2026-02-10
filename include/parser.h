/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:05:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/10 12:33:19 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "vector.h"
# include "../libft/libft.h"

typedef struct s_color
{
	float			r;
	float			g;
	float			b;
}					t_color;

typedef struct s_ambient
{
	float			ratio;
	t_color			color;
}					t_ambient;

typedef struct s_camera
{
	t_vector		pos;
	t_vector		dir;
	int				fov;
}					t_camera;

typedef struct s_light
{
	t_vector		pos;
	float			ratio;
	t_color			color;
}					t_light;

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_list			*objects;
}					t_scene;

t_color				parse_color(char *str);
t_vector			parse_vector(char *str);
void				ft_free_tab(char **tab);
float				ft_atof(const char *str);
int					init_parser(char *file, t_scene *scene);

#endif
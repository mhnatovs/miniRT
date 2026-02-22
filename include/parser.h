/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 11:58:20 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/21 11:58:23 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "vector.h"

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
	int				has_ambient;
	int				has_camera;
	int				has_light;
}					t_scene;

typedef struct s_sphere
{
	t_vector		center;
	float			radius;
	t_color			color;
}					t_sphere;

typedef struct s_plane
{
	t_vector		point;
	t_vector		normal;
	t_color			color;
	float			opacity;
}					t_plane;

typedef struct s_cylinder
{
	t_vector		base;
	t_vector		dir;
	float			radius;
	float			height;
	t_color			color;
}					t_cylinder;

typedef enum e_object_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}					t_object_type;

typedef struct s_object
{
	int				type;
	t_color			color;
	union			u_data
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	} data;
	struct s_object	*next;
}					t_object;

t_color				parse_color(char *str);
t_vector			parse_vector(char *str);
void				ft_free_tab(char **tab);
float				ft_atof(const char *str);
void				parse_sphere(char **tokens, t_scene *scene);
void				parse_plane(char **tokens, t_scene *scene);
void				parse_cylinder(char **tokens, t_scene *scene);
int					init_parser(char *file, t_scene *scene);

#endif
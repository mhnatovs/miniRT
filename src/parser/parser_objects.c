/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 12:30:55 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/02 13:51:36 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_sphere(char **tokens, t_scene *scene)
{
	t_sphere	sphere;
	t_object	*object;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		error_exit("Invalid Sphere format.\n");
	sphere.center = parse_vector(tokens[1]);
	sphere.radius = ft_atof(tokens[2]) / 2.0;
	if (sphere.radius <= 0)
		error_exit("Sphere radius must be positive.\n");
	sphere.color = parse_color(tokens[3]);
	object = malloc(sizeof(t_object));
	if (!object)
		error_exit("Memory allocation failed.\n");
	object->type = OBJ_SPHERE;
	object->color = sphere.color;
	object->data.sphere = sphere;
	if (!scene->objects)
		scene->objects = ft_calloc(1, sizeof(t_bvh_node));
	if (!scene->objects)
		error_exit("Memory allocation failed.\n");
	ft_lstadd_back(&scene->objects->primitives, ft_lstnew(object));
}

void	parse_plane(char **tokens, t_scene *scene)
{
	t_plane		plane;
	t_object	*object;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		error_exit("Invalid Plane format.\n");
	plane.point = parse_vector(tokens[1]);
	plane.normal = parse_vector(tokens[2]);
	if (plane.normal.x < -1.0 || plane.normal.x > 1.0 || plane.normal.y < -1.0
		|| plane.normal.y > 1.0 || plane.normal.z < -1.0
		|| plane.normal.z > 1.0)
		error_exit("Plane normal vector must be normalized.\n");
	plane.normal = vector_normalize(plane.normal);
	plane.color = parse_color(tokens[3]);
	object = malloc(sizeof(t_object));
	if (!object)
		error_exit("Memory allocation failed.\n");
	object->type = OBJ_PLANE;
	object->color = plane.color;
	object->data.plane = plane;
	if (!scene->objects)
		scene->objects = ft_calloc(1, sizeof(t_bvh_node));
	if (!scene->objects)
		error_exit("Memory allocation failed.\n");
	ft_lstadd_back(&scene->objects->primitives, ft_lstnew(object));
}

// static void	validate_cylinder_params(t_cylinder cyl)
// {
// 	if (cyl.dir.x < -1.0 || cyl.dir.x > 1.0 || cyl.dir.y < -1.0
// 		|| cyl.dir.y > 1.0 || cyl.dir.z < -1.0 || cyl.dir.z > 1.0)
// 		error_exit("Cylinder axis vector must be normalized");
// 	if (cyl.radius <= 0)
// 		error_exit("Cylinder diameter must be positive");
// 	if (cyl.height <= 0)
// 		error_exit("Cylinder height must be positive");
// }

static void	validate_cylinder_params(t_cylinder cyl)
{
	if (cyl.radius <= 0)
		error_exit("Cylinder diameter must be positive.\n");
	if (cyl.height <= 0)
		error_exit("Cylinder height must be positive.\n");
}

static t_cylinder	create_cylinder(char **tokens)
{
	t_cylinder	cyl;

	cyl.base = parse_vector(tokens[1]);
	cyl.dir = parse_vector(tokens[2]);
	cyl.dir = vector_normalize(cyl.dir);
	cyl.radius = ft_atof(tokens[3]) / 2.0;
	cyl.height = ft_atof(tokens[4]);
	cyl.color = parse_color(tokens[5]);
	validate_cylinder_params(cyl);
	return (cyl);
}

void	parse_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	cyl;
	t_object	*object;

	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5]
		|| tokens[6])
		error_exit("Invalid Cylinder format.\n");
	cyl = create_cylinder(tokens);
	object = malloc(sizeof(t_object));
	if (!object)
		error_exit("Memory allocation failed.\n");
	object->type = OBJ_CYLINDER;
	object->color = cyl.color;
	object->data.cylinder = cyl;
	if (!scene->objects)
		scene->objects = ft_calloc(1, sizeof(t_bvh_node));
	if (!scene->objects)
		error_exit("Memory allocation failed.\n");
	ft_lstadd_back(&scene->objects->primitives, ft_lstnew(object));
}

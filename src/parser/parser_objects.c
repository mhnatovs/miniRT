/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 13:34:09 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/17 13:13:07 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_sphere(char **tokens, t_scene *scene)
{
	t_sphere	sphere;
	t_object	*object;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		error_exit("Error: Invalid Sphere format");
	sphere.center = parse_vector(tokens[1]);
	sphere.radius = ft_atof(tokens[2]) / 2.0;
	if (sphere.radius <= 0)
		error_exit("Error: Sphere radius must be positive");
	sphere.color = parse_color(tokens[3]);
	object = malloc(sizeof(t_object));
	if (!object)
		error_exit("Error: Memory allocation failed");
	object->type = OBJ_SPHERE;
	object->color = sphere.color;
	object->data.sphere = sphere;
	ft_lstadd_back(&scene->objects, ft_lstnew(object));
}

void	parse_plane(char **tokens, t_scene *scene)
{
	t_plane		plane;
	t_object	*object;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		error_exit("Error: Invalid Plane format");
	plane.point = parse_vector(tokens[1]);
	plane.normal = parse_vector(tokens[2]);
	if (plane.normal.x < -1.0 || plane.normal.x > 1.0 || plane.normal.y < -1.0
		|| plane.normal.y > 1.0 || plane.normal.z < -1.0
		|| plane.normal.z > 1.0)
		error_exit("Error: Plane normal vector must be normalized");
	plane.normal = vector_normalize(plane.normal);
	plane.color = parse_color(tokens[3]);
	object = malloc(sizeof(t_object));
	if (!object)
		error_exit("Error: Memory allocation failed");
	object->type = OBJ_PLANE;
	object->color = plane.color;
	object->data.plane = plane;
	ft_lstadd_back(&scene->objects, ft_lstnew(object));
}

static void	validate_cylinder_params(t_cylinder cyl)
{
	if (cyl.dir.x < -1.0 || cyl.dir.x > 1.0 || cyl.dir.y < -1.0
		|| cyl.dir.y > 1.0 || cyl.dir.z < -1.0 || cyl.dir.z > 1.0)
		error_exit("Error: Cylinder axis vector must be normalized");
	if (cyl.radius <= 0)
		error_exit("Error: Cylinder diameter must be positive");
	if (cyl.height <= 0)
		error_exit("Error: Cylinder height must be positive");
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
		error_exit("Error: Invalid Cylinder format");
	cyl = create_cylinder(tokens);
	object = malloc(sizeof(t_object));
	if (!object)
		error_exit("Error: Memory allocation failed");
	object->type = OBJ_CYLINDER;
	object->color = cyl.color;
	object->data.cylinder = cyl;
	ft_lstadd_back(&scene->objects, ft_lstnew(object));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 20:47:48 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/03 20:47:50 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	intersect_object(t_ray ray, t_object *obj)
{
	if (obj->type == OBJ_SPHERE)
		return (intersect_sphere(ray, obj->data.sphere));
	if (obj->type == OBJ_PLANE)
		return (intersect_plane(ray, obj->data.plane));
	if (obj->type == OBJ_CYLINDER)
		return (intersect_cylinder(ray, obj->data.cylinder));
	return (-1);
}

void	hit_normal(t_object *obj, t_hit *hit)
{
	if (obj->type == OBJ_SPHERE)
		hit->normal = get_normal_sphere(hit->point, obj->data.sphere);
	if (obj->type == OBJ_PLANE)
		hit->normal = get_normal_plane(obj->data.plane);
	if (obj->type == OBJ_CYLINDER)
		hit->normal = get_normal_cylinder(hit->point, obj->data.cylinder);
}

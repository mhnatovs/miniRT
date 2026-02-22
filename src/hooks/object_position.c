/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 10:55:33 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/21 10:57:07 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_pos(t_object *o, t_vector move)
{
	if (o->type == OBJ_SPHERE)
		o->data.sphere.center = vector_add(o->data.sphere.center, move);
	else if (o->type == OBJ_PLANE)
		o->data.plane.point = vector_add(o->data.plane.point, move);
	else if (o->type == OBJ_CYLINDER)
		o->data.cylinder.base = vector_add(o->data.cylinder.base, move);
}

t_vector	get_obj_pos(t_object *o)
{
	if (o->type == OBJ_SPHERE)
		return (o->data.sphere.center);
	if (o->type == OBJ_PLANE)
		return (o->data.plane.point);
	if (o->type == OBJ_CYLINDER)
		return (o->data.cylinder.base);
	return ((t_vector){0, 0, 0});
}

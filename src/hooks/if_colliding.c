/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_colliding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 10:56:10 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/21 11:23:57 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	cylinder_plane_collision(t_cylinder cyl, t_vector next_pos,
		t_plane plane)
{
	float		dist0;
	float		dist1;
	float		offset;
	t_vector	top;
	float		dot_dn;

	top = vector_add(next_pos, vector_scale(cyl.dir, cyl.height));
	dist0 = vector_dot(vector_substract(next_pos, plane.point), plane.normal);
	dist1 = vector_dot(vector_substract(top, plane.point), plane.normal);
	dot_dn = vector_dot(cyl.dir, plane.normal);
	offset = cyl.radius * sqrt(1.0f - dot_dn * dot_dn);
	if ((dist0 - offset) * (dist0 + offset) <= 0)
		return (true);
	if ((dist1 - offset) * (dist1 + offset) <= 0)
		return (true);
	if (dist0 * dist1 <= 0)
		return (true);
	return (false);
}

static bool	check_collision(t_object *o, t_object *other, t_vector next_pos)
{
	float	dist;

	if (o->type == OBJ_SPHERE)
	{
		dist = vector_dot(vector_substract(next_pos, other->data.plane.point),
				other->data.plane.normal);
		if (fabs(dist) < o->data.sphere.radius)
			return (true);
	}
	else if (o->type == OBJ_CYLINDER)
	{
		if (cylinder_plane_collision(o->data.cylinder, next_pos,
				other->data.plane))
			return (true);
	}
	return (false);
}

bool	is_colliding(t_context *ctx, t_object *o, t_vector next_pos)
{
	t_list		*node;
	t_object	*other;

	node = ctx->scene.objects;
	while (node)
	{
		other = node->content;
		if (other != o && other->type == OBJ_PLANE)
		{
			if (check_collision(o, other, next_pos))
				return (true);
		}
		node = node->next;
	}
	return (false);
}

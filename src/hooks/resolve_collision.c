/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_collision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 11:24:28 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/21 11:06:54 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	solve_sphere_plane(t_object *s, t_object *p)
{
	float	dist;
	float	target;

	dist = vector_dot(vector_substract(s->data.sphere.center,
				p->data.plane.point), p->data.plane.normal);
	if (fabs(dist) < s->data.sphere.radius)
	{
		target = s->data.sphere.radius;
		if (dist < 0)
			target = -target;
		update_pos(s, vector_scale(p->data.plane.normal, target - dist));
	}
}

static void	apply_cyl_col(t_object *c, t_vector normal, float offset, float d)
{
	float	sign;

	sign = -1.0f;
	if (d >= 0)
		sign = 1.0f;
	update_pos(c, vector_scale(normal, (offset * sign) - d));
}

static void	solve_cylinder_plane(t_object *c, t_object *p)
{
	float		d[2];
	float		offset;
	t_vector	top;

	top = vector_add(c->data.cylinder.base, vector_scale(c->data.cylinder.dir,
				c->data.cylinder.height));
	d[0] = vector_dot(vector_substract(c->data.cylinder.base,
				p->data.plane.point), p->data.plane.normal);
	d[1] = vector_dot(vector_substract(top, p->data.plane.point),
			p->data.plane.normal);
	offset = c->data.cylinder.radius * sqrt(1.0f
			- pow(vector_dot(c->data.cylinder.dir, p->data.plane.normal), 2));
	if (fabs(d[0]) < offset)
		apply_cyl_col(c, p->data.plane.normal, offset, d[0]);
	else if (fabs(d[1]) < offset)
		apply_cyl_col(c, p->data.plane.normal, offset, d[1]);
}

void	resolve_scaling_collision(t_context *ctx, t_object *o)
{
	t_list		*node;
	t_object	*other;

	if (!o)
		return ;
	node = ctx->scene.objects;
	while (node)
	{
		other = node->content;
		if (other != o && other->type == OBJ_PLANE)
		{
			if (o->type == OBJ_SPHERE)
				solve_sphere_plane(o, other);
			else if (o->type == OBJ_CYLINDER)
				solve_cylinder_plane(o, other);
		}
		node = node->next;
	}
}

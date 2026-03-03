/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:15:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/03 13:23:13 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Slab method (Kay/Kajiya) for AABB intersection
static float	intersect_aabb_dist(t_ray ray, t_aabb box)
{
	float	tmin;
	float	tmax;
	float	t1;
	float	t2;

	tmin = -1e30f;
	tmax = 1e30f;
	t1 = (box.min.x - ray.origin.x) * ray.inv_direction.x;
	t2 = (box.max.x - ray.origin.x) * ray.inv_direction.x;
	tmin = fmax(tmin, fmin(t1, t2));
	tmax = fmin(tmax, fmax(t1, t2));
	t1 = (box.min.y - ray.origin.y) * ray.inv_direction.y;
	t2 = (box.max.y - ray.origin.y) * ray.inv_direction.y;
	tmin = fmax(tmin, fmin(t1, t2));
	tmax = fmin(tmax, fmax(t1, t2));
	t1 = (box.min.z - ray.origin.z) * ray.inv_direction.z;
	t2 = (box.max.z - ray.origin.z) * ray.inv_direction.z;
	tmin = fmax(tmin, fmin(t1, t2));
	tmax = fmin(tmax, fmax(t1, t2));
	if (tmax >= tmin && tmax > 0)
		return (tmin > 0 ? tmin : 0.0f);
	return (1e30f);
}

static t_hit	intersect_primitives(t_ray ray, t_list *primitives)
{
	t_hit		hit;
	double		t;
	t_list		*curr;
	t_object	*obj;

	hit.t = -1.0;
	hit.obj = NULL;
	curr = primitives;
	while (curr)
	{
		obj = (t_object *)curr->content;
		t = intersect_object(ray, obj);
		if (t > 0 && (hit.t < 0 || t < hit.t))
		{
			hit.t = t;
			hit.obj = obj;
			hit.point = vector_add(ray.origin, vector_scale(ray.direction, t));
			hit_normal(obj, &hit);
		}
		curr = curr->next;
	}
	return (hit);
}

t_hit	traverse_bvh(t_ray ray, t_bvh_node *node)
{
	t_hit		hit;
	t_hit		hit2;
	float		d1;
	float		d2;
	float		temp;
	t_bvh_node	*c1;
	t_bvh_node	*c2;

	hit = (t_hit){-1.0, NULL, {0, 0, 0}, {0, 0, 0}};
	if (!node)
		return (hit);
	if (intersect_aabb_dist(ray, node->node_bounds) == 1e30f)
		return (hit);
	if (node->is_leaf)
		return (intersect_primitives(ray, node->primitives));
	d1 = node->left ? intersect_aabb_dist(ray, node->left->node_bounds) : 1e30f;
	d2 = node->right ? intersect_aabb_dist(ray, node->right->node_bounds) : 1e30f;
	if (d1 > d2)
	{
		c1 = node->right; c2 = node->left;
		temp = d1; d1 = d2; d2 = temp;
	}
	else
	{
		c1 = node->left; c2 = node->right;
	}
	if (d1 < 1e30f)
		hit = traverse_bvh(ray, c1);
	if (hit.obj && hit.t < d2)
		return (hit);
	if (d2 < 1e30f)
	{
		hit2 = traverse_bvh(ray, c2);
		if (hit2.obj && (!hit.obj || hit2.t < hit.t))
			return (hit2);
	}
	return (hit);
}

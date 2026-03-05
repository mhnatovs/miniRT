/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 20:12:58 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/04 10:39:32 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	sort_nodes(float d[2], t_bvh_node *c[2], t_bvh_node *node,
				t_ray ray)
{
	float	tmp_d;

	d[0] = get_node_dist(ray, node->left);
	d[1] = get_node_dist(ray, node->right);
	c[0] = node->left;
	c[1] = node->right;
	if (d[0] > d[1])
	{
		tmp_d = d[0];
		d[0] = d[1];
		d[1] = tmp_d;
		c[0] = node->right;
		c[1] = node->left;
	}
}

static t_hit	intersect_internal(t_ray ray, t_bvh_node *node)
{
	float		d[2];
	t_bvh_node	*c[2];
	t_hit		hit;
	t_hit		hit2;

	sort_nodes(d, c, node, ray);
	hit = (t_hit){-1.0, NULL, {0, 0, 0}, {0, 0, 0}};
	if (d[0] < 1e30)
		hit = traverse_bvh(ray, c[0]);
	if (hit.obj && hit.t < d[1])
		return (hit);
	if (d[1] < 1e30)
	{
		hit2 = traverse_bvh(ray, c[1]);
		if (hit2.obj && (!hit.obj || hit2.t < hit.t))
			return (hit2);
	}
	return (hit);
}

t_hit	traverse_bvh(t_ray ray, t_bvh_node *node)
{
	if (!node || intersect_aabb_dist(ray, node->node_bounds) == 1e30)
		return ((t_hit){-1.0, NULL, {0, 0, 0}, {0, 0, 0}});
	if (node->is_leaf)
		return (intersect_primitives(ray, node->primitives));
	return (intersect_internal(ray, node));
}

t_hit	trace_ray(t_ray ray, t_scene scene)
{
	return (traverse_bvh(ray, scene.objects));
}

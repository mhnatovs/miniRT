/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 20:35:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/04 10:39:40 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_aabb	combine_aabbs(t_aabb box1, t_aabb box2)
{
	t_aabb	box;

	box.min.x = fmin(box1.min.x, box2.min.x);
	box.min.y = fmin(box1.min.y, box2.min.y);
	box.min.z = fmin(box1.min.z, box2.min.z);
	box.max.x = fmax(box1.max.x, box2.max.x);
	box.max.y = fmax(box1.max.y, box2.max.y);
	box.max.z = fmax(box1.max.z, box2.max.z);
	return (box);
}

t_vector	get_aabb_center(t_aabb box)
{
	t_vector	center;

	center.x = (box.min.x + box.max.x) * 0.5f;
	center.y = (box.min.y + box.max.y) * 0.5f;
	center.z = (box.min.z + box.max.z) * 0.5f;
	return (center);
}

static void	update_t(float *min, float *max, float b[2], float r[2])
{
	float	t1;
	float	t2;

	t1 = (b[0] - r[0]) * r[1];
	t2 = (b[1] - r[0]) * r[1];
	*min = fmax(*min, fmin(t1, t2));
	*max = fmin(*max, fmax(t1, t2));
}

float	intersect_aabb_dist(t_ray ray, t_aabb box)
{
	float	tm[2];

	tm[0] = -1e30;
	tm[1] = 1e30;
	update_t(&tm[0], &tm[1], (float []){box.min.x, box.max.x},
		(float []){ray.origin.x, ray.inv_direction.x});
	update_t(&tm[0], &tm[1], (float []){box.min.y, box.max.y},
		(float []){ray.origin.y, ray.inv_direction.y});
	update_t(&tm[0], &tm[1], (float []){box.min.z, box.max.z},
		(float []){ray.origin.z, ray.inv_direction.z});
	if (tm[1] >= tm[0] && tm[1] > 0)
	{
		if (tm[0] > 0)
			return (tm[0]);
		return (0.0f);
	}
	return (1e30);
}

float	get_node_dist(t_ray ray, t_bvh_node *node)
{
	if (!node)
		return (1e30);
	return (intersect_aabb_dist(ray, node->node_bounds));
}

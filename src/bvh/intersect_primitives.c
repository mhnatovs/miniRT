/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_primitives.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyan <jiyan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:47:15 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/04 20:39:33 by jiyan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	intersect_primitives(t_ray ray, t_list *primitives)
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
		if (t > 0.001f && (hit.t < 0 || t < hit.t))
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

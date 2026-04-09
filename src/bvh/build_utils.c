/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:46:54 by jiyawang          #+#    #+#             */
/*   Updated: 2026/04/09 10:04:15 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	compare_x(const void *a, const void *b)
{
	t_vector	ca;
	t_vector	cb;

	ca = get_aabb_center(get_object_aabb(*(t_object **)a));
	cb = get_aabb_center(get_object_aabb(*(t_object **)b));
	if (ca.x > cb.x)
		return (1);
	else if (ca.x < cb.x)
		return (-1);
	return (0);
}

int	compare_y(const void *a, const void *b)
{
	t_vector	ca;
	t_vector	cb;

	ca = get_aabb_center(get_object_aabb(*(t_object **)a));
	cb = get_aabb_center(get_object_aabb(*(t_object **)b));
	if (ca.y > cb.y)
		return (1);
	else if (ca.y < cb.y)
		return (-1);
	return (0);
}

int	get_split_axis(t_object **objects, int count)
{
	t_aabb		cb;
	t_vector	c;
	t_vector	e;
	int			i;

	c = get_aabb_center(get_object_aabb(objects[0]));
	cb = (t_aabb){c, c};
	i = 0;
	while (++i < count)
	{
		c = get_aabb_center(get_object_aabb(objects[i]));
		cb.min.x = fmin(cb.min.x, c.x);
		cb.min.y = fmin(cb.min.y, c.y);
		cb.min.z = fmin(cb.min.z, c.z);
		cb.max.x = fmax(cb.max.x, c.x);
		cb.max.y = fmax(cb.max.y, c.y);
		cb.max.z = fmax(cb.max.z, c.z);
	}
	e = vector_substract(cb.max, cb.min);
	if (e.x > e.y && e.x > e.z)
		return (0);
	if (e.y > e.z)
		return (1);
	return (2);
}

void	sort_objects(t_object **objects, int count, int axis)
{
	int			i;
	int			j;
	t_object	*key;

	i = 1;
	while (i < count)
	{
		key = objects[i];
		j = i - 1;
		while (j >= 0)
		{
			if (axis == 0 && compare_x(&objects[j], &key) > 0)
				objects[j + 1] = objects[j];
			else if (axis == 1 && compare_y(&objects[j], &key) > 0)
				objects[j + 1] = objects[j];
			else if (axis == 2 && compare_z(&objects[j], &key) > 0)
				objects[j + 1] = objects[j];
			else
				break ;
			j--;
		}
		objects[j + 1] = key;
		i++;
	}
}

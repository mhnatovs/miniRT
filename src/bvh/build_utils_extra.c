/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_utils_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:46:45 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/04 10:46:47 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	compare_z(const void *a, const void *b)
{
	t_vector	ca;
	t_vector	cb;

	ca = get_aabb_center(get_object_aabb(*(t_object **)a));
	cb = get_aabb_center(get_object_aabb(*(t_object **)b));
	if (ca.z > cb.z)
		return (1);
	else if (ca.z < cb.z)
		return (-1);
	return (0);
}

void	fill_leaf_primitives(t_bvh_node *node, t_object **objects, int count)
{
	int	i;

	i = 0;
	while (i < count)
		ft_lstadd_back(&node->primitives, ft_lstnew(objects[i++]));
}

t_bvh_node	*init_internal_node(t_bvh_node *l, t_bvh_node *r)
{
	t_bvh_node	*node;

	node = ft_calloc(1, sizeof(t_bvh_node));
	if (!node)
		return (NULL);
	node->left = l;
	node->right = r;
	if (l && r)
		node->node_bounds = combine_aabbs(l->node_bounds, r->node_bounds);
	else if (l)
		node->node_bounds = l->node_bounds;
	else if (r)
		node->node_bounds = r->node_bounds;
	return (node);
}

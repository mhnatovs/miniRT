/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:15:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/03 12:57:27 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	compare_x(const void *a, const void *b)
{
	t_object	*oa;
	t_object	*ob;
	t_vector	ca;
	t_vector	cb;

	oa = *(t_object **)a;
	ob = *(t_object **)b;
	ca = get_aabb_center(get_object_aabb(oa));
	cb = get_aabb_center(get_object_aabb(ob));
	if (ca.x > cb.x)
		return (1);
	else if (ca.x < cb.x)
		return (-1);
	return (0);
}

static int	compare_y(const void *a, const void *b)
{
	t_object	*oa;
	t_object	*ob;
	t_vector	ca;
	t_vector	cb;

	oa = *(t_object **)a;
	ob = *(t_object **)b;
	ca = get_aabb_center(get_object_aabb(oa));
	cb = get_aabb_center(get_object_aabb(ob));
	if (ca.y > cb.y)
		return (1);
	else if (ca.y < cb.y)
		return (-1);
	return (0);
}

static int	compare_z(const void *a, const void *b)
{
	t_object	*oa;
	t_object	*ob;
	t_vector	ca;
	t_vector	cb;

	oa = *(t_object **)a;
	ob = *(t_object **)b;
	ca = get_aabb_center(get_object_aabb(oa));
	cb = get_aabb_center(get_object_aabb(ob));
	if (ca.z > cb.z)
		return (1);
	else if (ca.z < cb.z)
		return (-1);
	return (0);
}

static t_bvh_node	*create_leaf_node(t_object **objects, int count)
{
	t_bvh_node	*node;
	int			i;
	t_aabb		obj_box;

	node = ft_calloc(1, sizeof(t_bvh_node));
	if (!node)
		return (NULL);
	node->is_leaf = 1;
	if (count > 0)
		node->node_bounds = get_object_aabb(objects[0]);
	i = 1;
	while (i < count)
	{
		obj_box = get_object_aabb(objects[i]);
		node->node_bounds = combine_aabbs(node->node_bounds, obj_box);
		i++;
	}
	i = 0;
	while (i < count)
	{
		ft_lstadd_back(&node->primitives, ft_lstnew(objects[i]));
		i++;
	}
	return (node);
}

static t_bvh_node	*build_bvh_recursive(t_object **objects, int count)
{
	t_bvh_node	*node;
	t_aabb		centroid_bounds;
	t_vector	center;
	t_vector	extent;
	int			axis;
	int			mid;
	int			i;

	if (count <= 4)
		return (create_leaf_node(objects, count));
	center = get_aabb_center(get_object_aabb(objects[0]));
	centroid_bounds.min = center;
	centroid_bounds.max = center;
	i = 1;
	while (i < count)
	{
		center = get_aabb_center(get_object_aabb(objects[i]));
		centroid_bounds.min.x = fmin(centroid_bounds.min.x, center.x);
		centroid_bounds.min.y = fmin(centroid_bounds.min.y, center.y);
		centroid_bounds.min.z = fmin(centroid_bounds.min.z, center.z);
		centroid_bounds.max.x = fmax(centroid_bounds.max.x, center.x);
		centroid_bounds.max.y = fmax(centroid_bounds.max.y, center.y);
		centroid_bounds.max.z = fmax(centroid_bounds.max.z, center.z);
		i++;
	}
	extent = vector_substract(centroid_bounds.max, centroid_bounds.min);
	axis = 0;
	if (extent.y > extent.x)
		axis = 1;
	if (extent.z > (axis == 0 ? extent.x : extent.y))
		axis = 2;

	if (axis == 0)
		qsort(objects, count, sizeof(t_object *), compare_x);
	else if (axis == 1)
		qsort(objects, count, sizeof(t_object *), compare_y);
	else
		qsort(objects, count, sizeof(t_object *), compare_z);

	mid = count / 2;
	node = ft_calloc(1, sizeof(t_bvh_node));
	if (!node)
		return (NULL);
	node->left = build_bvh_recursive(objects, mid);
	node->right = build_bvh_recursive(objects + mid, count - mid);
	if (node->left && node->right)
		node->node_bounds = combine_aabbs(node->left->node_bounds,
				node->right->node_bounds);
	else if (node->left)
		node->node_bounds = node->left->node_bounds;
	else if (node->right)
		node->node_bounds = node->right->node_bounds;
	return (node);
}

void	build_bvh(t_scene *scene)
{
	int			count;
	t_object	**obj_array;
	t_list		*curr;
	int			i;
	t_bvh_node	*root;

	if (!scene->objects || !scene->objects->primitives)
		return ;

	count = ft_lstsize(scene->objects->primitives);
	obj_array = malloc(sizeof(t_object *) * count);
	if (!obj_array)
		return ;
	
	curr = scene->objects->primitives;
	i = 0;
	while (curr)
	{
		obj_array[i++] = (t_object *)curr->content;
		curr = curr->next;
	}
	// We don't need the initial flat list node anymore, assumes build_bvh_recursive builds strictly new nodes
	// Correct, create_leaf_node makes new lists.
	// But wait, the original list nodes (t_list) are leaked if we just abandon them.
	// We extracted content (t_object*) which is fine.
	// We need to free the old scene->objects structure.
	ft_lstclear(&scene->objects->primitives, NULL);
	free(scene->objects);
	root = build_bvh_recursive(obj_array, count);
	scene->objects = root;
	free(obj_array);
}

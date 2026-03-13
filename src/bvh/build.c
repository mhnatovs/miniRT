/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:47:06 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/13 15:15:14 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_bvh_node	*create_leaf_node(t_object **objects, int count)
{
	t_bvh_node	*node;
	int			i;

	node = ft_calloc(1, sizeof(t_bvh_node));
	if (!node)
		return (NULL);
	node->is_leaf = 1;
	if (count > 0)
		node->node_bounds = get_object_aabb(objects[0]);
	i = 1;
	while (i < count)
	{
		node->node_bounds = combine_aabbs(node->node_bounds,
				get_object_aabb(objects[i]));
		i++;
	}
	fill_leaf_primitives(node, objects, count);
	return (node);
}

static t_bvh_node	*build_bvh_recursive(t_object **objects, int count)
{
	int	axis;
	int	mid;

	if (count <= 4)
		return (create_leaf_node(objects, count));
	axis = get_split_axis(objects, count);
	sort_objects(objects, count, axis);
	mid = count / 2;
	return (init_internal_node(build_bvh_recursive(objects, mid),
			build_bvh_recursive(objects + mid, count
				- mid)));
}

static void	clear_list_no_free(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
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
	clear_list_no_free(&scene->objects->primitives);
	free(scene->objects);
	root = build_bvh_recursive(obj_array, count);
	scene->objects = root;
	free(obj_array);
}

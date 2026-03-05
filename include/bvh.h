/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 20:50:52 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/03 20:50:53 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "../libft/libft.h"
# include "vector.h"

typedef struct s_object	t_object;

typedef struct s_aabb
{
	t_vector			min;
	t_vector			max;
}						t_aabb;

typedef struct s_bvh_node
{
	t_aabb				node_bounds;
	struct s_bvh_node	*left;
	struct s_bvh_node	*right;
	int					is_leaf;
	t_list				*primitives;
}						t_bvh_node;

typedef struct s_scene	t_scene;

void					free_bvh(t_bvh_node *node);
t_aabb					get_object_aabb(t_object *obj);
t_aabb					combine_aabbs(t_aabb box1, t_aabb box2);
t_vector				get_aabb_center(t_aabb box);
int						compare_x(const void *a, const void *b);
int						compare_y(const void *a, const void *b);
int						compare_z(const void *a, const void *b);
int						get_split_axis(t_object **objects, int count);
void					sort_objects(t_object **objects, int count, int axis);
void					fill_leaf_primitives(t_bvh_node *node,
							t_object **objects, int count);
t_bvh_node				*init_internal_node(t_bvh_node *l, t_bvh_node *r);
void					build_bvh(t_scene *scene);

#endif

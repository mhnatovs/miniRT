/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:00:00 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/03 12:54:53 by jiyawang         ###   ########.fr       */
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
void					build_bvh(t_scene *scene);

#endif

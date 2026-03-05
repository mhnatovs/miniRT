/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bvh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 20:48:09 by jiyawang          #+#    #+#             */
/*   Updated: 2026/03/03 20:48:11 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

void	free_bvh(t_bvh_node *node)
{
	if (!node)
		return ;
	if (node->left)
		free_bvh(node->left);
	if (node->right)
		free_bvh(node->right);
	if (node->primitives)
		ft_lstclear(&node->primitives, free);
	free(node);
}

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

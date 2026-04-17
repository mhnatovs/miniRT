/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 21:19:29 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/04/09 15:34:17 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_exit(char *msg)
{
	if (write(2, "Error\n", 6) == -1)
		(void)0;
	if (msg)
	{
		if (write(2, msg, ft_strlen(msg)) == -1)
			(void)0;
	}
	exit(1);
}

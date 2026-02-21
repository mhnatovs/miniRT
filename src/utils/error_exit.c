/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 21:19:29 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/21 11:33:05 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_exit(char *msg)
{
	if (msg)
	{
		if (write(STDERR_FILENO, msg, ft_strlen(msg)) == -1)
			(void)0;
	}
	if (write(STDERR_FILENO, "\n", 1) == -1)
		(void)0;
	exit(1);
}

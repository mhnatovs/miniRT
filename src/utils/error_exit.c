/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 21:19:29 by mhnatovs          #+#    #+#             */
/*   Updated: 2026/02/12 21:19:46 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_exit(char *msg)
{
	if (msg)
		write (STDERR_FILENO, msg, ft_strlen(msg));
	write (STDERR_FILENO, "\n", 1);
	exit(1);
}

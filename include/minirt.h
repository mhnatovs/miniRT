/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:05:14 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/13 15:01:53 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 800
# define HEIGHT 600

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

# include "MLX42/MLX42.h"
# include "vector.h"
# include "parser.h"
# include "../libft/libft.h"
# include "ray.h"
# include "intersection.h"

void	error_exit(char *msg);

#endif	
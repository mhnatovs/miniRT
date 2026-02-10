/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:04:43 by jiyawang          #+#    #+#             */
/*   Updated: 2026/02/10 12:37:13 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

float	ft_atof(const char *str)
{
	float	res;
	float	decimal;
	int		sign;

	res = 0.0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
		res = res * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		decimal = 0.1;
		str++;
		while (*str >= '0' && *str <= '9')
		{
			res += (*str++ - '0') * decimal;
			decimal /= 10.0;
		}
	}
	return (res * sign);
}

t_color	parse_color(char *str)
{
	char	**rgb;
	t_color	color;

	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		error_exit("Error: Invalid color format (R,G,B)");
	color.r = ft_atoi(rgb[0]);
	color.g = ft_atoi(rgb[1]);
	color.b = ft_atoi(rgb[2]);
	if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
		error_exit("Error: Color values must be in range [0, 255]");
	color.r = color.r / 255.0;
	color.g = color.g / 255.0;
	color.b = color.b / 255.0;
	ft_free_tab(rgb);
	return (color);
}

t_vector	parse_vector(char *str)
{
	char		**xyz;
	t_vector	vec;

	xyz = ft_split(str, ',');
	if (!xyz || !xyz[0] || !xyz[1] || !xyz[2] || xyz[3])
		error_exit("Error: Invalid vector format (x,y,z)");
	vec.x = ft_atof(xyz[0]);
	vec.y = ft_atof(xyz[1]);
	vec.z = ft_atof(xyz[2]);
	ft_free_tab(xyz);
	return (vec);
}

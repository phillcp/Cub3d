/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 21:32:35 by fiheaton          #+#    #+#             */
/*   Updated: 2026/03/12 21:04:03 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# define TEXTURE_SIZE	64
# define MINIMAP_TILE_SIZE 10

typedef struct s_ray
{
	double	rx;
	double	ry;
	double	z;
	t_pos	tex;
	int		**texture;
	double	lh;
	double	lo;
	double	texoff;
	t_pos	off;
}	t_ray;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_img;

#endif

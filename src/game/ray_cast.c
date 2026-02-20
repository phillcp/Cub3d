/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 22:26:14 by fiheaton          #+#    #+#             */
/*   Updated: 2026/02/20 09:04:52 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	dist_3d(float ax, float ay, float bx, float by)
{
	double	ret;

	ret = sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
	return (ret);
}

double	h_check(t_map map, double ang, t_ray *h, t_pos pos)
{
	h->off.x = 0;
	h->off.y = 0;
	if (ang > PI)
	{
		h->ry = ((int)pos.y) + 1.0001;
		h->rx = (pos.y - h->ry) * (-1 / tan(ang)) + pos.x;
		h->off = (t_pos){.x = -1 * (-1 / tan(ang)), .y = 1};
	}
	else if (ang < PI)
	{
		h->ry = ((int)pos.y) - 0.0001;
		h->rx = (pos.y - h->ry) * (-1 / tan(ang)) + pos.x;
		h->off = (t_pos){.x = (-1 / tan(ang)), .y = -1};
	}
	if (ang != 0 && ang != PI)
	{
		while (h->ry >= 0 && h->ry < map.height
			&& h->rx >= 0 && h->rx < map.width)
		{
			if (map.grid[(int)h->ry][(int)h->rx] == '1')
				return (h->z = dist_3d(h->rx, h->ry, pos.x, pos.y));
			(void) (t_pos){(h->rx += h->off.x), (h->ry += h->off.y)};
		}
	}
	return (h->z = -1);
}

double	v_check(t_map map, double ang, t_ray *v, t_pos pos)
{
	v->off.y = 0;
	if (ang < (PI / 2) || ang > (3 * PI / 2))
	{
		v->rx = ((int)pos.x) - 0.0001;
		v->ry = (pos.x - v->rx) * -tan(ang) + pos.y;
		v->off = (t_pos){.x = -1, .y = -tan(ang)};
	}
	else if (ang > (PI / 2) && ang < (3 * PI / 2))
	{
		v->rx = ((int)pos.x) + 1.0001;
		v->ry = (pos.x - v->rx) * (-tan(ang)) + pos.y;
		v->off = (t_pos){.x = 1, .y = tan(ang)};
	}
	if (ang != (PI / 2) && ang != (3 * PI / 2))
	{
		while (v->ry >= 0 && (int)v->ry < map.height
			&& v->rx >= 0 && (int)v->rx < map.width)
		{
			if (map.grid[(int)v->ry][(int)v->rx] == '1')
				return (v->z = dist_3d(v->rx, v->ry, pos.x, pos.y));
			(void) (t_pos){v->rx += v->off.x, v->ry += v->off.y};
		}
	}
	return (v->z = -1);
}

void	aux(double ang, t_ray *hv, t_game *g, t_ray *check)
{
	if ((hv[0].z < hv[1].z && hv[0].z > 0.0) || hv[1].z < 0)
	{
		*check = hv[0];
		check->tex.x = (check->rx - (int)check->rx) * TEXTURE_SIZE;
		check->texture = g->so_tex;
		if (ang > PI)
			check->tex.x = TEXTURE_SIZE - check->tex.x - 1;
		else
			check->texture = g->no_tex;
	}
	else
	{
		*check = hv[1];
		check->tex.x = (check->ry - (int)check->ry) * TEXTURE_SIZE;
		check->texture = g->we_tex;
		if (ang > (PI / 2) && ang < (3 * PI / 2))
			check->texture = g->ea_tex;
		else
			check->tex.x = TEXTURE_SIZE - check->tex.x - 1;
	}
}

t_ray	*check_wall(t_game *g, t_pos pos, double ang, float pa)
{
	t_ray	hv[2];
	t_ray	*check;

	hv[0] = (t_ray){.rx = 0, .ry = 0, .z = 0};
	hv[1] = (t_ray){.rx = 0, .ry = 0, .z = 0};
	check = ft_calloc(1, sizeof(t_ray));
	h_check(g->map, ang, &hv[0], pos);
	v_check(g->map, ang, &hv[1], pos);
	aux(ang, hv, g, check);
	check->z = check->z * cos(fmod(pa - ang + 2 * PI, 2 * PI));
	check->lh = (double)g->screen->height / check->z;
	check->lo = ((double)g->screen->height - check->lh) / 2;
	if (check->lo < 0)
		check->texoff = (check->lh - g->screen->height) / 2.0;
	if (check->lo < 0)
		check->lo = 0;
	check->tex.y = check->texoff * (TEXTURE_SIZE / (double)check->lh);
	return (check);
}

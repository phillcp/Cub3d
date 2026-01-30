/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiheaton <fiheaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 12:59:11 by fiheaton          #+#    #+#             */
/*   Updated: 2026/01/30 12:59:36 by fiheaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# define FD_MAX 4096

# include "libft.h"
# include <unistd.h>
# include <sys/types.h>

int		get_next_line(int fd, char **line);

#endif

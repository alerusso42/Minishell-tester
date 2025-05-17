/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mfile_reset_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:41:16 by alerusso          #+#    #+#             */
/*   Updated: 2025/05/17 13:43:33 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfile_gnl.h"

/*
	reset_fd reimposta read all'inizio del file, e contemporaneamente
	resetta il buffer di get_next_line.
    Se nello stock di fd era presente l'fd, lo aggiorna.
*/
int	reset_fd(int fd, char *name)
{
	int	old_fd;

	get_next_line(fd, RESET);
	old_fd = fd;
	close(fd);
	fd = open(name, O_RDWR);
	if (fd == -1)
		return (1);
	update_filedata(old_fd, fd);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mfile_gnl_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:35:35 by alerusso          #+#    #+#             */
/*   Updated: 2025/02/21 10:40:56 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfile_gnl.h"

void	*calloc_memcpy(int size, void *dest, const void *src, int ft)
{
	int		total_size;
	char	*string_pointer;
	void	*pointer;

	pointer = NULL;
	if (ft == CALLOC)
	{
		total_size = size * sizeof(char);
		pointer = malloc(total_size);
		if (!pointer)
			return (NULL);
		string_pointer = (char *)pointer;
		while (total_size--)
			*string_pointer++ = 0;
	}
	if ((ft == MEMCPY) && ((dest) || (src)))
	{
		pointer = dest;
		while ((size-- > 0) && (dest + 1) && (src + 1))
		{
			*((char *)dest++) = *((char *)src++);
		}
		*((char *)dest) = 0;
	}
	return (pointer);
}

int	find_end_line(size_t *start, char *string)
{
	int	save;
	int	index;

	save = -1;
	index = *start;
	while (index >= 0)
	{
		if ((string[index] == '\n') || (string[index] == '\n'))
			save = index;
		index -= 1;
	}
	if (save == -1)
		return (EOF_OR_NEWLINE_NOT_FOUND);
	*start = (size_t)save;
	return (EOF_OR_NEWLINE_FOUND);
}

int	alloc_ft(void **content, void *new_content, size_t start, int mode)
{
	size_t	nmemb;
	void	*re_content;

	nmemb = (start + 1) * sizeof(char);
	if (mode == MALLOC)
	{
		*content = calloc_memcpy(((nmemb + 1) * 2), NULL, NULL, CALLOC);
		if (!(*content))
			return (FULL_MEMORY);
		return (SUCCESS);
	}
	if (mode == REALLOC)
	{
		re_content = calloc_memcpy((nmemb) * 2, NULL, NULL, CALLOC);
		if (!(re_content))
			return (FULL_MEMORY);
		calloc_memcpy(nmemb, re_content, new_content, MEMCPY);
		free(*content);
		*content = re_content;
		return (SUCCESS);
	}
	if ((mode == FREE) && (*content))
		free(*content);
	*content = NULL;
	return (END_OR_CORRUPTION);
}

void	trim_readbytes(char *buffer)
{
	int	old_index;
	int	new_index;

	if (!buffer)
	{
		return ;
	}
	old_index = 0;
	new_index = 0;
	while (buffer[old_index] != '\0' && buffer[old_index] != '\n')
	{
		++old_index;
	}
	if (buffer[old_index] == '\n')
	{
		++old_index;
	}
	while (buffer[old_index] != '\0')
	{
		buffer[new_index++] = buffer[old_index++];
	}
	buffer[new_index] = '\0';
}

char	*ft_strjoin_custom(char *s1, char *s2)
{
	char	*stringona;
	int		index;
	int		size;

	if ((!s1) || (!s2))
		return (NULL);
	index = 0;
	while (s1[index])
		++index;
	size = index;
	index = 0;
	while (s2[index])
		++index;
	size += index;
	if (alloc_ft((void **)(&stringona), NULL, size + 1, MALLOC) == FULL_MEMORY)
		return (NULL);
	index = -1;
	while (s1[++index])
		stringona[index] = s1[index];
	size = -1;
	while (s2[++size])
		stringona[index++] = s2[size];
	free(s1);
	free(s2);
	return (stringona);
}

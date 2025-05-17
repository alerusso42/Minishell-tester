/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:13:25 by alerusso          #+#    #+#             */
/*   Updated: 2024/11/30 14:44:46 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	index;
	size_t	substring_lenght;
	size_t	size;
	char	*substring;

	substring_lenght = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	while ((s[start + substring_lenght]) && (substring_lenght < len))
		++substring_lenght;
	size = substring_lenght;
	substring = (char *)ft_calloc(size + 1, 1);
	if (!substring)
		return (NULL);
	index = 0;
	while (index < substring_lenght)
	{
		substring[index] = s[start + index];
		++index;
	}
	substring[index] = '\0';
	return (substring);
}

/*
int	main(int argc, char *argv[])
{
	char	*sub_string;
	int		start;
	size_t	len;
	
	if (argc < 4)
	{
		printf("1) STRINGA; 2) START 3) LEN");
		return (42);	
	}
	start = atoi(argv[2]);
	len = (int)atoi(argv[3]);
	sub_string = ft_substr(argv[1], start, len);
	printf("\n%s\n", sub_string),
	free(sub_string);
	return (0);
}*/

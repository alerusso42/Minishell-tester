/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:47:19 by alerusso          #+#    #+#             */
/*   Updated: 2024/11/29 15:36:21 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while ((--n) && (*s1 != '\0') && (*s2 != '\0') && (*s1 == *s2))
	{
		++s1;
		++s2;
	}
	return ((unsigned char)(*s1) - (unsigned char)(*s2));
}

/*
int	main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("Inserisci le 2 stringhe, poi il numero di confronti da fare");
		return (42);
	}
	if (argc == 42)
	{
		printf("Pisa merda");
		return (42);
	}
	int n = argv[3][0] - '0';
	printf("Funzione fake: %d", ft_strncmp(argv[1], argv[2], n));
	return (0);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cut_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:09:57 by alerusso          #+#    #+#             */
/*   Updated: 2025/02/24 11:23:04 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "other.h"

/*
	Cut a string from start to end (included).
	
	Example:

	string = "Hello world!"
	start = 5
	end = 5

	string becomes: "Helloworld!\0"
*/
int	cut_string_realloc(char **string, size_t start, size_t end)
{
	unsigned int	temp;
	unsigned int	temp1;
	unsigned int	string_len;

	end++;
	if (!(string) || !(*string) || (start > end))
		return (1);
	string_len = 0;
	while ((*string)[string_len])
		++string_len;
	temp = start;
	while ((start != end) && ((*string)[start] != 0))
		(*string)[start++] = 0;
	end = start;
	start = temp;
	temp = 0;
	temp1 = string_len - (end - start);
	while (end != string_len--)
	{
		(*string)[start + temp] = (*string)[end + temp];
		++temp;
	}
	(*string)[temp1] = 0;
	return (ft_realloc((void **)string, temp1 + 1, sizeof(char)));
}

/*
	Cut a string from start to end (included).
	
	Example:

	string = "Hello world!"
	start = 5
	end = 5

	string becomes: "Helloworld!\0"
*/
int	cut_string(char *string, size_t start, size_t end)
{
	unsigned int	temp;
	unsigned int	temp1;
	unsigned int	string_len;

	end++;
	if (!(string) || !(*string) || (start > end))
		return (1);
	string_len = 0;
	while (string[string_len])
		++string_len;
	temp = start;
	while ((start != end) && (string[start] != 0))
		string[start++] = 0;
	end = start;
	start = temp;
	temp = 0;
	temp1 = string_len;
	while (end != string_len--)
	{
		string[start + temp] = string[end + temp];
		++temp;
	}
	string[temp1 - (end - start)] = 0;
	return (0);
}

/*
int	main()
{
	char	*temp;

	char	test[20] = "Hello world!";
	temp = ft_strdup(test);
	cut_string(temp, 5, 5);
	l_printf("\n%s\n", temp);
	cut_string(temp, 0, 4);
	l_printf("\n%s\n", temp);
	cut_string(temp, 0, 4);
	l_printf("\n%s\n", temp);
	cut_string(temp, 0, 4);
	l_printf("\n%s\n", temp);
	free(temp);
	temp = NULL;
	char	test1[20] = "del_all";
	temp = ft_strdup(test1);
	l_printf("\n%s\n", temp);
	cut_string(temp, 0, INT_MAX);
	l_printf("\n%s\n", temp);
	free(temp);
	temp = NULL;
	char	test2[20] = "Hello world!";
	temp = ft_strdup(test2);
	cut_string_realloc(&temp, 5, 5);
	l_printf("\n%s\n", temp);
	cut_string_realloc(&temp, 0, 4);
	l_printf("\n%s\n", temp);
	cut_string_realloc(&temp, 0, 4);
	l_printf("\n%s\n", temp);
	cut_string_realloc(&temp, 0, 4);
	l_printf("\n%s\n", temp);
	free(temp);
	temp = NULL;
	char	test3[20] = "del_all";
	temp = ft_strdup(test3);
	l_printf("\n%s\n", temp);
	cut_string_realloc(&temp, 0, INT_MAX);
	l_printf("\n%s\n", temp);
	free(temp);
	temp = NULL;
}*/

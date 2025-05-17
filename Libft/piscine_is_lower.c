/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piscine_is_lower.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:54:35 by alerusso          #+#    #+#             */
/*   Updated: 2025/02/21 10:52:18 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_lowercase(char *str)
{
	int	checker;
	int	i;

	i = -1;
	checker = 1;
	while (str[++i])
	{
		if (!(str[i] >= 97 && str[i] <= 122))
		{
			--checker;
			break ;
		}
	}
	return (checker);
}
/*
int	main(void)
{
	int		checker;
	char	*str;

	str = "";
	checker = ft_str_is_lowercase(str) + '0';
	write(1, "Empty case: ", 12);
	write(1, &checker, 1);
	str = "konodioda";
	checker = ft_str_is_lowercase(str) + '0';
	write(1, "\nRight case: ", 13);
	write(1, &checker, 1);
	str = "KONODIODA";
	checker = ft_str_is_lowercase(str) + '0';
	write(1, "\nWrong case: ", 13);
	write(1, &checker, 1);
	return (0);
}*/

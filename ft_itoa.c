/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 20:24:51 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/03 20:25:13 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lenghtint(int number)
{
	int	size;

	if (number == 0)
		return (1);
	size = 0;
	if (number < 0)
	{
		while (number < 0)
		{
			number = number / 10;
			size++;
		}
		return (size + 1);
	}
	while (number > 0)
	{
		number = number / 10;
		size++;
	}
	return (size);
}

static void	ifhol(long n, int len, char *str)
{
	while (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[len] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char *str;
	int len;
	long nn;

	nn = n;
	len = lenghtint(nn);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len -= 1;
	if (nn == 0)
	{
		str[0] = 48;
		return (str);
	}
	ifhol(nn, len, str);
	return (str);
}
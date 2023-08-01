/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 22:56:43 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/31 19:55:58 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
	{
		return (1);
	}
	return (0);
}

char	*ft_strcpy_before(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '=' && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

char	*ft_strcpy_after(char *dst, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] && src[i] != '=')
		i++;
	if (src[i] && src[i] == '=')
		i++;
	while (src[i])
		dst[j++] = src[i++];
	return (dst);
}

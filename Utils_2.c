/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 15:11:41 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/08 16:34:46 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *b, int c, int len)
{
	int		i;
	char	*str;

	str = (char *)b;
	i = 0;
	while (len > i)
	{
		str[i] = c;
		i++;
	}
	return (b);
}

void	*ft_calloc(unsigned long count, unsigned long size)
{
	void	*ptr;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == 0)
		return (NULL);
	return (ft_memset(ptr, '\0', size * count));
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (s1 && s2)
	{
		while ((s1[i] || s2[i]) && (i < n))
		{
			if (s1[i] != s2[i])
				return (s1[i] - s2[i]);
			i++;
		}
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*finalstr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	finalstr = malloc(((ft_strlen(s1)) + (ft_strlen(s2))) + 1);
	if (!finalstr)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(s1))
	{
		finalstr[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		finalstr[i] = s2[j];
		i++;
		j++;
	}
	finalstr[i] = '\0';
	return (finalstr);
}

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*s2;
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	s2 = (char *)malloc(sizeof(char) * (len + 1));
	if (s2 == NULL)
		return (NULL);
	while (len > i && (int)start < ft_strlen(s))
	{
		s2[i] = s[start + i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

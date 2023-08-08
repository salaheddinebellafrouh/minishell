/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc_before_after.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 20:10:30 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/07 15:44:29 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calloc_after(char *string)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (string[i] != '=' && string[i])
		i++;
	while (string[i])
	{
		j++;
		i++;
	}
	return (j);
}

int	calloc_before(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '=' && string[i])
		i++;
	return (i);
}

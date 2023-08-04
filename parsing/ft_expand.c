/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:15:54 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/04 15:19:04 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*before_after(char **before, char **after, t_vars *vars, char *string)
{
	while (before[vars->l])
	{
		if (strcmp(before[vars->l], vars->id) == 0)
		{
			vars->k = 0;
			while (after[vars->l][vars->k])
			{
				if (after[vars->l][vars->k] != '"' && (after[vars->l][vars->k]))
				{
					string[vars->s] = after[vars->l][vars->k];
					vars->s++;
				}
				vars->k++;
			}
			break ;
		}
		vars->l++;
	}
	return (string);
}

void	init_vars(t_vars *vars)
{
	vars->d = 0;
	vars->j = 0;
	vars->k = 0;
	vars->l = 0;
	vars->i = 0;
	vars->s = 0;
	vars->kk = 0;
	vars->count = 0;
}

void	digit_dollar(t_vars *vars, char *data, char *string)
{
	vars->i++;
	if (ft_isdigit(data[vars->i]))
	{
		while (data[vars->i + 1] && data[vars->i] != '$')
		{
			if (data[vars->i + 1] != '$')
			{
				string[vars->s] = data[vars->i + 1];
				vars->s++;
			}
			vars->i++;
		}
	}
}

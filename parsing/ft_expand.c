/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:15:54 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/01 16:01:52 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*before_after(char **before, char **after, char *id, t_vars *vars,
		char *string)
{
	while (before[vars->l])
	{
		if (strcmp(before[vars->l], id) == 0)
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
void	ft_count_dn(t_vars *d, char *data)
{
	d->i++;
	if (ft_isdigit(data[d->i]))
	{
		while (data[d->i + 1] && data[d->i] != '$')
		{
			if (data[d->i + 1] != '$')
				d->s++;
			d->i++;
		}
		d->s++;
	}
}

int	ft_count_string(char *data, char **before, char **after)
{
	t_vars	d;

	d.s = 0;
	d.i = 0;
	while (data[d.i])
	{
		if (data[d.i] == '\'')
		{
			while (data[d.i] != '\'')
			{
				d.s++;
				d.i++;
			}
		}
		if (data[d.i] == '$' && data[d.i] && ft_isdigit(data[d.i + 1]))
		{
			if (!data[d.i + 1])
				return (strlen(data));
			ft_count_dn(&d, data);
		}
		else if (data[d.i] != '$')
		{
			if (data[d.i] == '$')
				d.s++;
			d.s++;
		}
		if (data[d.i] == '$' && ++d.i && data[d.i]
			&& !ft_isdigit(data[d.i + 1]))
		{
			if (!data[d.i])
				return (0);
			ft_count_dollar(data, before, after, &d);
		}
		if (data[d.i])
			d.i++;
	}
	return (d.s);
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

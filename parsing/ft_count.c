/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:07:20 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/04 17:57:35 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_count_sq(t_vars *d, char *data)
{
	if (data[d->i] == '\'')
	{
		while (data[d->i] != '\'')
		{
			d->s++;
			d->i++;
		}
	}
}

int	digit_count(char *data, t_vars *d, char **before, char **after)
{
	if (data[d->i] == '$' && ++d->i && data[d->i] && !ft_isdigit(data[d->i
			+ 1]))
	{
		if (!data[d->i])
			return (0);
		ft_count_dollar(data, before, after, d);
	}
	return (1);
}

int	ft_count_string(char *data, char **before, char **after)
{
	t_vars	d;

	d.s = 0;
	d.i = 0;
	while (data[d.i])
	{
		ft_count_sq(&d, data);
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
		if (!digit_count(data, &d, before, after))
			return (0);
		if (data[d.i])
			d.i++;
	}
	return (d.s);
}

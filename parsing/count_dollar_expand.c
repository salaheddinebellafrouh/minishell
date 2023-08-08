/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_dollar_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:40:25 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/07 15:21:36 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_dollar(char *data)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (data[i] && ((ft_isalnum(data[i])) || data[i] == '_'
			|| data[i] == '$'))
	{
		if (data[i] == '$')
		{
			k++;
		}
		else if (data[i] != '$')
		{
			break ;
		}
		i++;
	}
	return (k);
}

char	*get_id2(char *data)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	if (data[i] && data[i] == '?')
		return (ft_substr(data, 0, 1));
	while (data[i] && ((ft_isalnum(data[i])) || data[i] == '_'))
		i++;
	return (ft_substr(data, 0, i));
}

void	ft_count_dollar_ex(char **after, char **before, t_vars *d)
{
	while (before[d->l])
	{
		if (ft_strcmp(before[d->l], d->id) == 0)
		{
			d->k = 0;
			while (after[d->l][d->k])
			{
				if (after[d->l][d->k] != '"' && (after[d->l][d->k]))
					d->s++;
				d->k++;
			}
			break ;
		}
		d->l++;
	}
}

void	ft_count_dollar(char *data, char **before, char **after, t_vars *d)
{
	d->kk = count_dollar(&(data[d->i]));
	if (d->kk % 2 == 0)
	{
		while (data[d->i] == '$')
			d->i++;
		d->id = get_id2(&(data[d->i]));
	}
	else
		d->id = ft_strdup(" ");
	d->l = 0;
	ft_count_dollar_ex(after, before, d);
	d->i += ft_strlen(d->id) - 1;
	if (d->id)
	{
		free(d->id);
		d->id = NULL;
	}
}

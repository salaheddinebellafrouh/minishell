/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:46:25 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/01 16:00:26 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_quotes(char *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data[i])
	{
		if (data[i] == '"')
		{
			i++;
			while (data[i] != '"' && data[i])
				i++;
			count = count + 2;
		}
		else if (data[i] == '\'')
		{
			i++;
			while (data[i] != '\'' && data[i])
				i++;
			count = count + 2;
		}
		i++;
	}
	return (count);
}

void	fill_no_quotes(char *data, char *returned, t_vars *var)
{
	while (data[var->i])
	{
		if (data[var->i] != '"' && data[var->i] != '\'')
		{
			returned[var->j] = data[var->i];
			var->j++;
		}
		var->i++;
	}
}

char	*ft_rquotes(char *data)
{
	t_vars	var;
	char	*returned;

	init_vars(&var);
	returned = malloc(ft_strlen(data) + 1 - count_quotes(data));
	while (data[var.i])
	{
		if (data[var.i] && data[var.i] == '"')
		{
			var.i++;
			while (data[var.i] && data[var.i] != '"')
				returned[var.j++] = data[var.i++];
			var.i++;
		}
		if (data[var.i] && data[var.i] == '\'')
		{
			var.i++;
			while (data[var.i] && data[var.i] != '\'')
				returned[var.j++] = data[var.i++];
			var.i++;
		}
		else
			fill_no_quotes(data, returned, &var);
	}
	returned[var.j] = '\0';
	free(data);
	return (returned);
}

t_list	*ft_remove_quotes(t_list *list)
{
	t_list	*copied;
	Node	*arg;

	arg = list->arg;
	copied = list;
	while (copied)
	{
		while (arg)
		{
			arg->data = ft_rquotes(arg->data);
			arg = arg->next;
		}
		copied = copied->next;
	}
	return (list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:46:25 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/05 21:16:05 by sbellafr         ###   ########.fr       */
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

	init_vars(&var);
	var.returned = malloc(ft_strlen(data) + 1 - count_quotes(data));
	while (data[var.i])
	{
		if (data[var.i] && data[var.i] == '"')
		{
			var.i++;
			while (data[var.i] && data[var.i] != '"')
				var.returned[var.j++] = data[var.i++];
			var.i++;
		}
		if (data[var.i] && data[var.i] == '\'')
		{
			var.i++;
			while (data[var.i] && data[var.i] != '\'')
				var.returned[var.j++] = data[var.i++];
			var.i++;
		}
		else
			fill_no_quotes(data, var.returned, &var);
	}
	var.returned[var.j] = '\0';
	return (free(data), var.returned);
}

void	remove_all_q(t_node *arg, t_node *in, t_node *out)
{
	while (arg)
	{
		arg->data = ft_rquotes(arg->data);
		arg = arg->next;
	}
	while (in)
	{
		in->data = ft_rquotes(in->data);
		in = in->next;
	}
	while (out)
	{
		out->data = ft_rquotes(out->data);
		out = out->next;
	}
}

t_list	*ft_remove_quotes(t_list *list)
{
	t_list	*copied;
	t_node	*arg;
	t_node	*in;
	t_node	*out;

	arg = list->arg;
	in = list->infiles;
	out = list->outfiles;
	copied = list;
	while (copied)
	{
		remove_all_q(arg, in, out);
		copied = copied->next;
	}
	return (list);
}

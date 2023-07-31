/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:45:10 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/31 20:00:05 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_single(char read, int d, int s)
{
	if (read == '\"' && s == 0)
		d = !d;
	return (d);
}

int	check_double(char read, int d, int s)
{
	if (read == '\'' && d == 0)
		s = !s;
	return (s);
}

void	init_var(t_headvar *var)
{
	var->s = 0;
	var->d = 0;
	var->start = 0;
	var->cp = NULL;
	var->i = 0;
}

Node	*quotes_management(char *read, Node *head)
{
	t_headvar	var;

	init_var(&var);
	while (read[var.i])
	{
		var.s = check_single(read[var.i], var.d, var.s);
		var.d = check_double(read[var.i], var.d, var.s);
		if ((var.d == 0) && (var.s == 0))
		{
			if (ft_symbols(read[var.i]))
			{
				var.cp = ft_substr(read, var.start, var.i - var.start);
				if (var.cp != '\0' && ft_strlen(var.cp) != 0)
					add_elements(&head, var.cp);
				free(var.cp);
				var.i = string_list(read, var.i, &head);
				var.start += (var.i - var.start) + 1;
			}
		}
		var.i++;
	}
	var.cp = ft_substr(read, var.start, var.i - var.start);
	if (var.cp != '\0' && ft_strlen(var.cp) != 0)
		add_elements(&head, var.cp);
	free(var.cp);
	return (head);
}

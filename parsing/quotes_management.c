/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:45:10 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/04 18:03:03 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_var(t_headvar *var)
{
	var->s = 0;
	var->d = 0;
	var->start = 0;
	var->cp = NULL;
	var->i = 0;
}

void	double_single(t_headvar *var, char *read)
{
	if (read[var->i] == '\'' && var->d == 0)
		var->s = !var->s;
	if (read[var->i] == '\"' && var->s == 0)
		var->d = !var->d;
}

Node	*quotes_management(char *read, Node *head)
{
	t_headvar	var;

	init_var(&var);
	while (read[var.i++])
	{
	if (read[var.i] == '\'' && var.d == 0)
		var.s = !var.s;
	if (read[var.i] == '\"' && var.s == 0)
		var.d = !var.d;
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
	}
	var.cp = ft_substr(read, var.start, var.i - var.start);
	if (var.cp != '\0' && ft_strlen(var.cp) != 0)
		add_elements(&head, var.cp);
	return (free(var.cp), head);
}

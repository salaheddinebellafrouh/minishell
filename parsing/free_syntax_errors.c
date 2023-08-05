/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_syntax_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:37:18 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/05 21:16:05 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_t_nodes_prev(t_node *newt_node, t_node *temp)
{
	while (newt_node)
	{
		temp = newt_node->prev;
		free(newt_node->data);
		free(newt_node);
		newt_node = temp;
	}
}

void	free_t_nodes_next(t_node *newt_node, t_node *temp)
{
	while (newt_node)
	{
		temp = newt_node->next;
		free(newt_node->data);
		free(newt_node);
		newt_node = temp;
	}
}

void	free_newt_node(t_node *newt_node)
{
	free(newt_node->data);
	free(newt_node);
}

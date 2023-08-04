/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_syntax_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:37:18 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/02 19:31:34 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_nodes_prev(Node *newnode, Node *temp)
{
	while (newnode)
	{
		temp = newnode->prev;
		free(newnode->data);
		free(newnode);
		newnode = temp;
	}
}

void	free_nodes_next(Node *newnode, Node *temp)
{
	while (newnode)
	{
		temp = newnode->next;
		free(newnode->data);
		free(newnode);
		newnode = temp;
	}
}

void	free_newnode(Node *newnode)
{
	free(newnode->data);
	free(newnode);
}

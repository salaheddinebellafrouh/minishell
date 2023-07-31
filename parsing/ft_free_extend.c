/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_extend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:56:32 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/31 19:59:22 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node(Node *node)
{
	free(node->data);
	free(node);
}

void	free_t_list(t_list *list)
{
	free(list);
}

void	free_arg_nodes(t_list *list)
{
	Node	*arg;

	while (list->arg)
	{
		arg = list->arg->next;
		free_node(list->arg);
		list->arg = arg;
	}
}

void	free_redirect_nodes(t_list *list)
{
	Node	*redirect;

	while (list->redirect)
	{
		redirect = list->redirect->next;
		free_node(list->redirect);
		list->redirect = redirect;
	}
}

void	free_infiles_nodes(t_list *list)
{
	Node	*infiles;

	while (list->infiles)
	{
		infiles = list->infiles->next;
		free_node(list->infiles);
		list->infiles = infiles;
	}
}

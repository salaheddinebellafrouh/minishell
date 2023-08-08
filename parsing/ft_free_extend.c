/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_extend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:56:32 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/05 21:16:05 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_t_node(t_node *t_node)
{
	free(t_node->data);
	free(t_node);
}

void	free_t_list(t_list *list)
{
	free(list);
}

void	free_arg_t_nodes(t_list *list)
{
	t_node	*arg;

	while (list->arg)
	{
		arg = list->arg->next;
		free_t_node(list->arg);
		list->arg = arg;
	}
}

void	free_redirect_t_nodes(t_list *list)
{
	t_node	*redirect;

	while (list->redirect)
	{
		redirect = list->redirect->next;
		free_t_node(list->redirect);
		list->redirect = redirect;
	}
}

void	free_infiles_t_nodes(t_list *list)
{
	t_node	*infiles;

	while (list->infiles)
	{
		infiles = list->infiles->next;
		free_t_node(list->infiles);
		list->infiles = infiles;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:12:39 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/28 23:41:37 by sbellafr         ###   ########.fr       */
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

void	free_outfiles_nodes(t_list *list)
{
	Node	*outfiles;

	while (list->outfiles)
	{
		outfiles = list->outfiles->next;
		free_node(list->outfiles);
		list->outfiles = outfiles;
	}
}

void	free_hairdoc_nodes(t_list *list)
{
	Node	*hairdoc;

	while (list->hairdoc)
	{
		hairdoc = list->hairdoc->next;
		free_node(list->hairdoc);
		list->hairdoc = hairdoc;
	}
}

void	ft_free_list(t_list *list)
{
	t_list	*tmp_list;

	while (list)
	{
		free_arg_nodes(list);
		free_redirect_nodes(list);
		free_infiles_nodes(list);
		free_outfiles_nodes(list);
		free_hairdoc_nodes(list);
		tmp_list = list->next;
		free_t_list(list);
		list = tmp_list;
	}
}

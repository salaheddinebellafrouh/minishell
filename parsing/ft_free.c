/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:12:39 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/02 14:43:55 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

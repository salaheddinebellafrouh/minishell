/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:12:39 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/05 21:16:05 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_outfiles_t_nodes(t_list *list)
{
	t_node	*outfiles;

	while (list->outfiles)
	{
		outfiles = list->outfiles->next;
		free_t_node(list->outfiles);
		list->outfiles = outfiles;
	}
}

void	free_hairdoc_t_nodes(t_list *list)
{
	t_node	*hairdoc;

	while (list->hairdoc)
	{
		hairdoc = list->hairdoc->next;
		free_t_node(list->hairdoc);
		list->hairdoc = hairdoc;
	}
}

void	ft_free_list(t_list *list)
{
	t_list	*tmp_list;

	while (list)
	{
		free_arg_t_nodes(list);
		free_redirect_t_nodes(list);
		free_infiles_t_nodes(list);
		free_outfiles_t_nodes(list);
		free_hairdoc_t_nodes(list);
		tmp_list = list->next;
		free_t_list(list);
		list = tmp_list;
	}
}

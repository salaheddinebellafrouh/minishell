/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:32:09 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/07 15:05:31 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*init_list(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	list->arg = NULL;
	list->next = NULL;
	list->prev = NULL;
	list->redirect = NULL;
	list->infiles = NULL;
	list->outfiles = NULL;
	list->hairdoc = NULL;
	return (list);
}

t_node	*copy_list_red(t_list *currentlist, t_node *source)
{
	add_to_list(&(currentlist->redirect), source->data, 5);
	if (ft_strcmp(source->data, ">") == 0)
	{
		add_to_list(&(currentlist->outfiles), source->next->data, OUTFILE);
		source = source->next;
	}
	else if (ft_strcmp(source->data, ">>") == 0)
	{
		add_to_list(&(currentlist->outfiles), source->next->data, APPEND);
		source = source->next;
	}
	else if (ft_strcmp(source->data, "<") == 0)
	{
		add_to_list(&(currentlist->infiles), source->next->data, INFILE);
		currentlist->in_type = INFILE;
		source = source->next;
	}
	else if (ft_strcmp(source->data, "<<") == 0)
	{
		add_to_list(&(currentlist->hairdoc), source->next->data, HAIRDOC);
		currentlist->in_type = HAIRDOC;
		source = source->next;
	}
	return (source);
}

t_list	*copy_list(t_node *source)
{
	t_list	*returned;
	t_list	*currentlist;
	int		pipe;

	pipe = 0;
	returned = init_list();
	currentlist = returned;
	while (source != NULL)
	{
		if (ft_strcmp(source->data, "|") == 0)
		{
			currentlist->has_pipe = 1;
			currentlist->next = init_list();
			pipe++;
			currentlist = currentlist->next;
		}
		else if (!ft_strcmp(source->data, ">") || !ft_strcmp(source->data, ">>")
			|| !ft_strcmp(source->data, "<<") || !ft_strcmp(source->data, "<"))
			source = copy_list_red(currentlist, source);
		else
			add_elements(&(currentlist->arg), source->data);
		source = source->next;
	}
	returned->pipe = pipe;
	return (returned);
}

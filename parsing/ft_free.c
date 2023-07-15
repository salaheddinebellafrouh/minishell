/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:12:39 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/15 12:17:03 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list    *ft_free_list(t_list *list)
{
		t_list	*tmp_list;
		Node	*arg;
		Node	*redirect;
		Node	*infiles;
		Node	*outfiles;
		Node	*hairdoc; 
		
    	if (list)
		{
			while (list)
			{
				while (list->arg)
				{
					arg = list->arg->next;
					free(list->arg->data);
					free(list->arg);
					list->arg = arg;
				}
				while (list->redirect)
				{
					redirect = list->redirect->next;
					free(list->redirect->data);
					free(list->redirect);
					list->redirect = redirect;
				}
				while (list->infiles)
				{
					infiles = list->infiles->next;
					free(list->infiles->data);
					free(list->infiles);
					list->infiles = infiles;
				}
				while (list->outfiles)
				{
					outfiles = list->outfiles->next;
					free(list->outfiles->data);
					free(list->outfiles);
					list->outfiles = outfiles;
				}
				while (list->hairdoc)
				{
					hairdoc = list->hairdoc->next;
					free(list->hairdoc->data);
					free(list->hairdoc);
					list->hairdoc = hairdoc;
				}
				tmp_list = list->next;
				free(list);
				list=tmp_list;
				// list = list->next;
			}
		}
        return (list);
}

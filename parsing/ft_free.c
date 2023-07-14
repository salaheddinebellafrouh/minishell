/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:12:39 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/14 17:23:37 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list    *ft_free_list(t_list *list)
{
    	if (list)
		{
			while (list)
			{
				while (list->arg)
				{
					free(list->arg->data);
					free(list->arg);
					list->arg = list->arg->next;
				}
				while (list->redirect)
				{
					free(list->redirect->data);
					free(list->redirect);
					list->redirect = list->redirect->next;
				}
				while (list->infiles)
				{
					free(list->infiles->data);
					free(list->infiles);
					list->infiles = list->infiles->next;
				}
				while (list->outfiles)
				{
					free(list->outfiles->data);
					free(list->outfiles);
					list->outfiles = list->outfiles->next;
				}
				while (list->hairdoc)
				{
					free(list->hairdoc->data);
					free(list->hairdoc);
					list->hairdoc = list->hairdoc->next;
				}
				free(list);
				list = list->next;
			}
		}
        return (list);
}

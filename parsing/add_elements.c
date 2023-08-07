/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:52:33 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/07 15:01:35 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_list(t_node **head, char *data, int type)
{
	t_node	*newt_node;
	t_node	*current;

	newt_node = malloc(sizeof(t_node));
	newt_node->data = ft_strdup(data);
	newt_node->type = type;
	newt_node->next = NULL;
	newt_node->prev = NULL;
	if (*head == NULL)
	{
		*head = newt_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		newt_node->prev = current;
		current->next = newt_node;
	}
}

void	add_elements(t_node **head, char *data)
{
	t_node	*newt_node;
	t_node	*current;

	newt_node = malloc(sizeof(t_node));
	newt_node->data = ft_strdup(data);
	newt_node->next = NULL;
	newt_node->prev = NULL;
	if (*head == NULL)
	{
		*head = newt_node;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		newt_node->prev = current;
		current->next = newt_node;
	}
}

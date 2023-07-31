/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:52:33 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/31 19:54:27 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_list(Node **head, char *data, int type)
{
	Node	*newnode;
	Node	*current;

	newnode = (Node *)malloc(sizeof(Node));
	newnode->data = strdup(data);
	newnode->type = type;
	newnode->next = NULL;
	newnode->prev = NULL;
	if (*head == NULL)
	{
		*head = newnode;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		newnode->prev = current;
		current->next = newnode;
	}
}

void	add_elements(Node **head, char *data)
{
	Node	*newnode;
	Node	*current;

	newnode = (Node *)malloc(sizeof(Node));
	newnode->data = strdup(data);
	newnode->next = NULL;
	newnode->prev = NULL;
	if (*head == NULL)
	{
		*head = newnode;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		newnode->prev = current;
		current->next = newnode;
	}
}

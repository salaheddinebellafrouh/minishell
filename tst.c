/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:08:26 by sbellafr          #+#    #+#             */
/*   Updated: 2023/06/17 23:51:03 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct			Node
{
	char		*data;
	struct Node	*next;
};

void	addElement(struct Node **head, const char *data)
{
	struct Node	*newNode;
	struct Node	*current;

	newNode = (struct Node *)malloc(sizeof(struct Node));
	// Allocate memory for the string and copy the data
	newNode->data = (char *)malloc((strlen(data) + 1) * sizeof(char));
	strcpy(newNode->data, data);
	newNode->next = NULL;
	if (*head == NULL)
	{
		*head = newNode;
	}
	else
	{
		current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = newNode;
	}
}

void	printList(struct Node *head)
{
	struct Node	*current;

	current = head;
	while (current != NULL)
	{
		printf("[%s]", current->data);
		current = current->next;
	}
	printf("\n");
}

void	ft_start(char *read)
{
	struct Node	*head;
	char		*cp;
	int			i;
	int			j;

	head = NULL;
	j = 0;
	i = 0;
	while (read[i])
	{
		while ((read[i] == ' ' || read[i] == '\t') && read[i])
		{
			i++;
		}
		j = i;
		while ((read[i] != ' ' && read[i] != '\t') && read[i])
			i++;
		cp = malloc(i - j + 1);
		i = j;
		j = 0;
		if ((read[i] == '>' && read[i + 1] == '>'))
		{
			addElement(&head, ">>");
			i++;
			i++;
		}
		else if (read[i] == '>')
		{
			addElement(&head, ">");
			i++;
		}
		while ((read[i] != ' ' && read[i] != '\t' && read[i] != '>') && read[i])
		{
			cp[j] = read[i];
			j++;
			i++;
		}
		if (cp[0] != '\0')
			addElement(&head, cp);
		while ((read[i] == ' ' || read[i] == '\t') && read[i])
		{
			i++;
		}
	}
	printf("Linked List: ");
	printList(head);
}
int	main(void)
{
	char	*read;

	while (1)
	{
		read = readline("minishell> ");
		if (!read)
			exit(0);
		add_history(read);
		ft_start(read);
		free(read);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:08:26 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/08 16:15:30 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct			Node
{
	char		*data;
	struct Node	*next;
};

void	add_elements(struct Node **head, const char *data)
{
	struct Node	*newnode;
	struct Node	*current;

	newnode = (struct Node *)malloc(sizeof(struct Node));
	newnode->data = (char *)malloc((ft_strlen(data) + 1) * sizeof(char));
	strcpy(newnode->data, data);
	newnode->next = NULL;
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
		current->next = newnode;
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
int	ft_symbols(char c)
{
	if (c == ' ' || c == '>' || c == '<' || c == '|' || c == '>' || c == '\t')
		return (1);
	return (0);
}
void	check_syntax(char *read)
{
	int i;
	int count;

	count = 0;
	i = 0;

	while(read[i])
	{
		if(read[i] == '"')
		{
			count++;
			i++;
			while(read[i])
			{
				if(read[i] == '"')
				{
					count = 0;
					break;
				}
				i++;
			}
		}
		else if(read[i] == '\'')
		{
			count++;
			i++;
			while(read[i])
			{
				if(read[i] == '\'')
				{
					count = 0;
					break;
				}
				i++;
			}
		}
	
		i++;
	}
	if(count == 1)
		write(2, "Erreur\n", 7);
}
int	string_list(char *read, int i, struct Node **head)
{
	if (read[i] == '|')
		add_elements(&(*head), "|");
	if (read[i] == '<' && read[i + 1] == '<')
	{
		add_elements(&(*head), "<<");
		i++;
	}
	else if (read[i] == '<')
		add_elements(&(*head), "<");
	if (read[i] == '>' && read[i + 1] == '>')
	{
		add_elements(&(*head), ">>");
		i++;
	}
	else if (read[i] == '>')
		add_elements(&(*head), ">");
	return (i);
}
void	ft_start(char *read)
{
	struct Node	*head;
	char		*cp;
	int			i;
	int			start;
	int			s;
	int			d;

	s = 0;
	d = 0;
	head = NULL;
	start = 0;
	i = 0;
	
	check_syntax(read);
	i = 0;
	while (read[i])
	{
		if (read[i] == '\'' && d == 0)
			s = !s;
		if (read[i] == '\"' && s == 0)
			d = !d;
		if ((d == 0) && (s == 0))
		{
			if (ft_symbols(read[i]))
			{
				cp = ft_substr(read, start, i - start);
				if (cp != '\0' && ft_strlen(cp) != 0)
					add_elements(&head, cp);
				i = string_list(read, i, &head);
				start += (i - start) + 1;
			}
		}
		i++;
	}
	cp = ft_substr(read, start, i - start);
	if (cp != '\0' && ft_strlen(cp) != 0)
		add_elements(&head, cp);
	printf("Linked List: ");
	printList(head);
}
int	main(int ac, char **av, char **environ)
{
	char	*read;

	(void)ac;
	(void)av;
	
	while (1)
	{
		read = readline("minishell> ");
		if (!read)
			exit(0);
		add_history(read);
		// ft_start(read);
		
		execute_built_ins(read, environ);
			
		free(read);
	}
	return (0);
}

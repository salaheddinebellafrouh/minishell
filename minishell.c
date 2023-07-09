/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:08:26 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/09 16:12:14 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct Node
{
	char		*data;
	struct Node	*next;
}				Node;

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
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (read[i])
	{
		if (read[i] == '"')
		{
			count++;
			i++;
			while (read[i])
			{
				if (read[i] == '"')
				{
					count = 0;
					break ;
				}
				i++;
			}
		}
		else if (read[i] == '\'')
		{
			count++;
			i++;
			while (read[i])
			{
				if (read[i] == '\'')
				{
					count = 0;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	if (count == 1)
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
t_list	*copy_list(Node *source)
{
	t_list	*target;
	t_list	**targetPtr;
	t_list	*newNode;
	int		i;
	int		j;
	char	**newArg;
	char	**redirect;

	target = NULL;
	targetPtr = &target;
	newNode = NULL;
	i = 0;
	j = 0;
	newArg = NULL;
	redirect = NULL;
	while (source != NULL)
	{
		if (strcmp(source->data, "|") == 0)
		{
			printf("-------------------\n");
			if (newNode != NULL)
			{
				*targetPtr = newNode;
				targetPtr = &(newNode->next);
				newNode = NULL;
				i = 0;
			}
		}
		else
		{
			if (newNode == NULL)
			{
				if (strcmp(source->data, ">") == 0)
				{
					newNode = (t_list *)malloc(sizeof(t_list));
					newNode->redirect.redirect = (char **)malloc(2
							* sizeof(char *));
					newNode->redirect.redirect[0] = strdup(source->data);
					newNode->redirect.redirect[1] = NULL;
					newNode->data_size = 2;
					newNode->next = NULL;
					printf("Redirect: %s\n", newNode->redirect.redirect[0]);
				}
				else
				{
					newNode = (t_list *)malloc(sizeof(t_list));
					newNode->arg = (char **)malloc(2 * sizeof(char *));
					newNode->arg[0] = strdup(source->data);
					newNode->arg[1] = NULL;
					newNode->data_size = 2;
					newNode->next = NULL;
					printf("Arg: %s\n", newNode->arg[0]);
				}
			}
			else
			{
				if (strcmp(source->data, ">") == 0 || strcmp(source->data,
						"<") == 0 || strcmp(source->data, "<<") == 0
					|| strcmp(source->data, ">>") == 0)
				{
					redirect = (char **)malloc((i + 2) * sizeof(char *));
					j = 0;
					while (j < i)
					{
						redirect[j] = newNode->arg[j];
						j++;
					}
					redirect[i] = strdup(source->data);
					redirect[i + 1] = NULL;
					free(newNode->arg);
					newNode->arg = redirect;
					newNode->data_size = i + 2;
					printf("Redirect: %s\n", newNode->arg[i]);
				}
				else
				{
					newArg = (char **)malloc((i + 2) * sizeof(char *));
					j = 0;
					while (j < i)
					{
						newArg[j] = newNode->arg[j];
						j++;
					}
					newArg[i] = strdup(source->data);
					newArg[i + 1] = NULL;
					free(newNode->arg);
					newNode->arg = newArg;
					newNode->data_size = i + 2;
					printf("Arg: %s\n", newNode->arg[i]);
				}
			}
			i++;
		}
		source = source->next;
	}
	if (newNode != NULL)
	{
		*targetPtr = newNode;
	}
	return (target);
}

// void print_copy(t_list* list) {
//     while (list != NULL) {
//         printf("Redirect: ");
//         if (list->redirect.redirect != NULL) {
//             int i = 0;
//             while (list->redirect.redirect[i] != NULL) {
//                 printf("%s ", list->redirect.redirect[i]);
//                 i++;
//             }
//         }
//         printf("\n");

//         printf("Arg: ");
//         if (list->arg != NULL) {
//             int i = 0;
//             while (list->arg[i] != NULL) {
//                 printf("%s ", list->arg[i]);
//                 i++;
//             }
//         }
//         printf("\n");

//         list = list->next;
//     }
// }
void	print_copy(t_list *list)
{
	int	i;
	int	i;

	while (list != NULL)
	{
		if (list->redirect.redirect != NULL)
		{
			i = 0;
			while (list->redirect.redirect[i] != NULL)
			{
				printf("Redirect: %s\n", list->redirect.redirect[i]);
				i++;
			}
		}
		else if (list->arg != NULL)
		{
			i = 0;
			while (list->arg[i] != NULL)
			{
				printf("Arg: %s\n", list->arg[i]);
				i++;
			}
		}
		list = list->next;
	}
}

void	print_copy1(t_list *head)
{
	(void)head;
	// while (head != NULL)
	// {
	// for (int i = 0; i < head->data_size - 1; i++)
	// {
	// 	if (head->arg[i])
	// 		printf("*%s*\n", head->arg[i]);
	// else if (head->redirect.redirect[i])
	// printf("********\n");
	// if(head->arg[0])
	// 	printf("redirection : %s*\n", head->arg[0]);
	//  if(head->redirect.redirect[1])
	// 	printf("redirection : %s*\n", head->redirect.redirect[1]);
	// 	}
	// 	printf("---------------\n");
	// 	head = head->next;
	// }
	printf("\n");
}

void	ft_start(char *read)
{
	t_list		*copiedlist;
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
	copiedlist = copy_list(head);
	// print_copy(copiedlist);
	// printf("Linked List: ");
	// printList(head);
}
int	main(int ac, char **av, char **env)
{
	char	*read;

	(void)env;
	(void)ac;
	(void)av;
	while (1)
	{
		read = readline("minishell> ");
		if (!read)
			exit(0);
		add_history(read);
		ft_start(read);
		// execute_built_ins(read, environ);
		free(read);
	}
	return (0);
}

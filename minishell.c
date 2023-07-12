/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:08:26 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/12 16:43:36 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_elements(struct Node **head, char *data)
{
	struct Node	*newnode;
	struct Node	*current;

	newnode = (struct Node *)malloc(sizeof(struct Node));
	newnode->data = strdup(data);
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
		printf("Syntax Erreur\n");
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

t_list	*init_list()
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	list->arg = NULL;
	list->next = NULL;
	list->prev = NULL;	
	list->redirect = NULL;	
	list->red_file = NULL;
	return (list);
}

t_list *copy_list(Node *source)
{
    t_list *returned;
    t_list *currentList;

	returned = init_list();
	currentList = returned;
    while (source != NULL)
    {
        if (strcmp(source->data, "|") == 0)
        {
            currentList->next = init_list();
			currentList = currentList->next;
        }
        else if (strcmp(source->data, ">") == 0)
        {
			add_elements(&(currentList->redirect), source->data);
			add_elements(&(currentList->red_file), source->next->data);
			source = source->next;
        }
        else
        {
			add_elements(&(currentList->arg), source->data);
        }
        source = source->next;
    }
    return (returned);
}


void	print_copy(t_list *list)
{
	Node		*currentArg;
	Node	*file;
	Node	*red;

	currentArg = NULL;
	file = NULL;
	while (list != NULL)
	{
		currentArg = list->arg;
		while (currentArg != NULL)
		{
			printf("Arg: %s\n", currentArg->data);
			currentArg = currentArg->next;
		}
		file = list->red_file;
		if (file != NULL)
		{
			printf("Filename: %s\n", list->red_file->data);
		}
		red = list->redirect;
		if (file != NULL)
		{
			printf("red: %s\n", red->data);
		}
		list = list->next;
		printf("---------\n");
	}
}

t_list	*ft_start(char *read)
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
	// printf("%s\n", copiedlist->arg->arg);
	// copiedlist->arg = NULL;
	// copiedlist->redirect = NULL;
	// exit(0);
	print_copy(copiedlist);
	// exit(0);
	// printf("Linked List: ");
	// printList(head);
	return (copiedlist);
}
int	main(int ac, char **av, char **env)
{
	char		*read;
	t_builtins	*builts;
	t_list		*list;

	(void)ac;
	(void)av;
	builts = malloc(sizeof(t_builtins));
	fill_env(env, builts);
	while (1)
	{
		read = readline("minishell> ");
		if (!read)
			exit(0);
		add_history(read);
		list = ft_start(read);
		execute_built_ins(read, builts, list);
		free(read);
	}
	return (0);
}

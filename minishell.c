/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:08:26 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/09 16:14:48 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct			Node
{
	char		*data;
	struct Node	*next;
}Node;

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
t_list *copy_list(Node *source)
{
    t_list *target;
    t_list **targetPtr;
    t_list *newNode;
    int		i;
	int		j;
    target = NULL;
    targetPtr = &target;
    newNode = NULL;
    i = 0;
    
    while (source != NULL)
    {
        if (strcmp(source->data, "|") == 0)
        {
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
                newNode = (t_list *)malloc(sizeof(t_list));
                newNode->arg = (char **)malloc(2 * sizeof(char *));
                newNode->arg[0] = strdup(source->data);
                newNode->arg[1] = NULL;
                newNode->data_size = 2;
                newNode->next = NULL;
            }
            else
            {
                char **newArg = (char **)malloc((i + 2) * sizeof(char *));
                newNode->redirect.redirect = (char **)malloc((i + 2) * sizeof(char *));

				j = 0;
                while (j <= i) 
				{
                    newArg[j] = newNode->arg[j];
					j++;
                }
                newArg[i + 1] = NULL;

                free(newNode->arg);
                newNode->arg = newArg;
                newNode->data_size = i + 2;
                newNode->arg[i] = strdup(source->data);
            }
            
            i++;
        }
        
        source = source->next;
    }
    
    if (newNode != NULL)
    {
        *targetPtr = newNode;
    }
    
    return target;
}
void print_copy(t_list *list) {
    while (list != NULL) {
        
        printf("Arguments: ");
        for (int i = 0; list->arg[i] != NULL; i++) 
		{
			if(list->arg[i])
            printf("%s ", list->arg[i]);
        }
        printf("\n");
        
        // printf("Redirections: ");
        // for (int i = 0; i < list->redirect.redirect_size; i++) 
		// {
		// 	if(list->redirect.redirect[i])
        //     printf("%s ", list->redirect.redirect[i]);
        // }
        printf("-------PIPE-------\n");
      
        
        list = list->next;
    }
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
	print_copy(copiedlist);
	// printf("Linked List: ");
	// printList(head);
}
int	main(int ac, char **av, char **env)
{
	char		*read;
	t_builtins	*builts;

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
		// ft_start(read);

		execute_built_ins(read, builts);
			
		free(read);
	}
	return (0);
}

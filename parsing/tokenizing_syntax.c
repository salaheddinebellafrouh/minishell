/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:59:08 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/28 22:00:16 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_list(struct Node **head, char *data, int type)
{
	struct Node	*newnode;
	struct Node	*current;

	newnode = (struct Node *)malloc(sizeof(struct Node));
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

void	add_elements(struct Node **head, char *data)
{
	struct Node	*newnode;
	struct Node	*current;

	newnode = (struct Node *)malloc(sizeof(struct Node));
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

int	ft_symbols(char c)
{
	if (c == ' ' || c == '>' || c == '<' || c == '|' || c == '>' || c == '\t')
		return (1);
	return (0);
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

t_list	*copy_list(Node *source)
{
	t_list	*returned;
	t_list	*currentList;
	int		pipe;

	pipe = 0;
	returned = init_list();
	currentList = returned;
	while (source != NULL)
	{
		if (strcmp(source->data, "|") == 0)
		{
			currentList->has_pipe = 1;
			currentList->next = init_list();
			pipe++;
			currentList = currentList->next;
		}
		else if (strcmp(source->data, ">") == 0 || strcmp(source->data,
					">>") == 0 || strcmp(source->data, "<<") == 0
				|| strcmp(source->data, "<") == 0)
		{
			add_to_list(&(currentList->redirect), source->data, 5);
			if (strcmp(source->data, ">") == 0)
			{
				add_to_list(&(currentList->outfiles), source->next->data,
						OUTFILE);
				source = source->next;
			}
			else if (strcmp(source->data, ">>") == 0)
			{
				add_to_list(&(currentList->outfiles), source->next->data,
						APPEND);
				source = source->next;
			}
			else if (strcmp(source->data, "<") == 0)
			{
				add_to_list(&(currentList->infiles), source->next->data,
						INFILE);
				currentList->in_type = INFILE;
				source = source->next;
			}
			else if (strcmp(source->data, "<<") == 0)
			{
				add_to_list(&(currentList->hairdoc), source->next->data,
						HAIRDOC);
				currentList->in_type = HAIRDOC;
				source = source->next;
			}
		}
		else
		{
			add_elements(&(currentList->arg), source->data);
		}
		source = source->next;
	}
	returned->pipe = pipe;
	return (returned);
}

void	print_copy(t_list *list)
{
	Node	*currentArg;
	Node	*file;
	Node	*red;
	Node	*outfile;
	Node	*hairdoc;

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
		file = list->infiles;
		while (file != NULL)
		{
			printf("infiles: %s type : %d\n", file->data, file->type);
			file = file->next;
		}
		outfile = list->outfiles;
		while (outfile != NULL)
		{
			printf("outfiles: %s\n", outfile->data);
			outfile = outfile->next;
		}
		hairdoc = list->hairdoc;
		while (hairdoc != NULL)
		{
			printf("hairdoc: %s\n", hairdoc->data);
			hairdoc = hairdoc->next;
		}
		red = list->redirect;
		while (red != NULL)
		{
			printf("red: %s\n", red->data);
			red = red->next;
		}
		list = list->next;
		printf("---------\n");
	}
}
Node	*syntax_error(Node *head)
{
	Node	*newnode;

	newnode = NULL;
	newnode = head;
	while (newnode)
	{
		if (strcmp(newnode->data, ">") == 0 || strcmp(newnode->data, ">>") == 0
			|| strcmp(newnode->data, "<<") == 0 || strcmp(newnode->data,
				"<") == 0)
		{
			if (!newnode->next)
			{
				free(newnode->data);
				free(newnode);
				printf("minishell: syntax error near unexpected token `newline'\n");
				return (NULL);
			}
			if (strcmp(newnode->next->data, "|") == 0)
			{
				free(newnode->data);
				free(newnode);
				printf("minishell: syntax error near unexpected token `newline'\n");
				return (NULL);
			}
		}
		else if (strcmp(newnode->data, "|") == 0)
		{
			if (!newnode->next || !newnode->prev)
			{
				free(newnode->data);
				free(newnode);
				printf("minishell: syntax error near unexpected token `|'\n");
				return (NULL);
			}
			if (strcmp(newnode->next->data, "|") == 0)
			{
				free(newnode->data);
				free(newnode);
				printf("minishell: syntax error near unexpected token `|''\n");
				return (NULL);
			}
		}
		newnode = newnode->next;
	}
	return (head);
}
int	ft_syntax_quotes(Node *head)
{
	Node	*copy;
	int		i;
	int		valid;

	copy = head;
	valid = 1;
	i = 0;
	while (copy)
	{
		i = 0;
		while (copy->data[i])
		{
			if (copy->data[i] && copy->data[i] == '"')
			{
				valid = 0;
				i++;
				while (copy->data[i] && copy->data[i] != '"')
					i++;
				if (copy->data[i] && copy->data[i] == '"')
					valid = 1;
			}
			if (copy->data[i] && copy->data[i] == '\'')
			{
				valid = 0;
				i++;
				while (copy->data[i] && copy->data[i] != '\'')
					i++;
				if (copy->data[i] && copy->data[i] == '\'')
					valid = 1;
			}
			if (copy->data[i])
				i++;
		}
		if (valid == 0)
		{
			printf("Syntax Error\n");
			return (0);
		}
		copy = copy->next;
	}
	return (1);
}
t_list	*ft_start(char *read, char **env)
{
	t_list *copiedlist;
	struct Node *head;
	char *cp;
	int i;
	int start;
	int s;
	int d;
	Node *temp;

	(void)env;
	s = 0;
	d = 0;
	head = NULL;
	start = 0;
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
				free(cp);
				i = string_list(read, i, &head);
				start += (i - start) + 1;
			}
		}
		i++;
	}
	cp = ft_substr(read, start, i - start);
	if (cp != '\0' && ft_strlen(cp) != 0)
		add_elements(&head, cp);
	free(cp);
	if (!ft_syntax_quotes(head))
	{
		while (head)
		{
			temp = head->next;
			free(head->data);
			free(head);
			head = temp;
		}
		return (NULL);
	}
	head = syntax_error(head);
	if (!head)
		return (NULL);
	copiedlist = copy_list(head);
	while (head)
	{
		temp = head->next;
		free(head->data);
		free(head);
		head = temp;
	}
	copiedlist = ft_expand(copiedlist, env);
	copiedlist = ft_remove_quotes(copiedlist);
	print_copy(copiedlist);
	return (copiedlist);
}
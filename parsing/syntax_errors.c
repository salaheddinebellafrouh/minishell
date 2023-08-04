/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:50:49 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/02 18:32:43 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_redirections(Node *newnode)
{
	Node	*temp;

	temp = NULL;
	if (!newnode->next)
	{
		free_nodes_prev(newnode, temp);
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	else if (strcmp(newnode->next->data, "|") == 0)
	{
		free(newnode->next->data);
		free(newnode->next);
		free_nodes_prev(newnode, temp);
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

int	syntax_pipes(Node *newnode)
{
	Node	*temp;

	temp = NULL;
	if (!newnode->next || !newnode->prev)
	{
		if (!newnode->next && !newnode->prev)
			free_newnode(newnode);
		else if (!newnode->prev)
			free_nodes_next(newnode, temp);
		else if (!newnode->next)
			free_nodes_prev(newnode, temp);
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	else if (strcmp(newnode->next->data, "|") == 0)
	{
		free(newnode->next->data);
		free(newnode->next);
		free_nodes_prev(newnode, temp);
		printf("minishell: syntax error near unexpected token `|''\n");
		return (0);
	}
	return (1);
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
			if (!(syntax_redirections(newnode)))
				return (NULL);
		}
		else if (strcmp(newnode->data, "|") == 0)
		{
			if (!(syntax_pipes(newnode)))
				return (NULL);
		}
		newnode = newnode->next;
	}
	return (head);
}

int	check_syntax_q(int *valid, Node *copy, int i)
{
	if (copy->data[i] && copy->data[i] == '"')
	{
		*(valid) = 0;
		i++;
		while (copy->data[i] && copy->data[i] != '"')
			i++;
		if (copy->data[i] && copy->data[i] == '"')
			*(valid) = 1;
	}
	if (copy->data[i] && copy->data[i] == '\'')
	{
		*(valid) = 0;
		i++;
		while (copy->data[i] && copy->data[i] != '\'')
			i++;
		if (copy->data[i] && copy->data[i] == '\'')
			*(valid) = 1;
	}
	return (i);
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
			i = check_syntax_q(&valid, copy, i);
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

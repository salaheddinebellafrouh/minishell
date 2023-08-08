/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:50:49 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/07 15:47:46 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_redirections(t_node *newt_node)
{
	t_node	*temp;

	temp = NULL;
	if (!newt_node->next)
	{
		free_t_nodes_prev(newt_node, temp);
		g_global = 258;
		ft_putstr_fd("minishell: syntax error \n", 2);
		return (0);
	}
	else if (ft_strcmp(newt_node->next->data, "|") == 0)
	{
		free(newt_node->next->data);
		free(newt_node->next);
		free_t_nodes_prev(newt_node, temp);
		g_global = 258;
		ft_putstr_fd("minishell: syntax error \n", 2);
		return (0);
	}
	return (1);
}

int	syntax_pipes(t_node *newt_node)
{
	t_node	*temp;

	temp = NULL;
	if (!newt_node->next || !newt_node->prev)
	{
		if (!newt_node->next && !newt_node->prev)
			free_newt_node(newt_node);
		else if (!newt_node->prev)
			free_t_nodes_next(newt_node, temp);
		else if (!newt_node->next)
			free_t_nodes_prev(newt_node, temp);
		g_global = 258;
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	else if (ft_strcmp(newt_node->next->data, "|") == 0)
	{
		free(newt_node->next->data);
		free(newt_node->next);
		free_t_nodes_prev(newt_node, temp);
		g_global = 258;
		ft_putstr_fd("minishell: syntax error near unexpected token `|''\n", 2);
		return (0);
	}	
	return (1);
}

t_node	*syntax_error(t_node *head)
{
	t_node	*newt_node;

	newt_node = NULL;
	newt_node = head;
	while (newt_node)
	{
		if (ft_strcmp(newt_node->data, ">") == 0
			|| ft_strcmp(newt_node->data, ">>") == 0
			|| ft_strcmp(newt_node->data, "<<") == 0
			|| ft_strcmp(newt_node->data, "<") == 0)
		{
			if (!(syntax_redirections(newt_node)))
				return (NULL);
		}
		else if (ft_strcmp(newt_node->data, "|") == 0)
		{
			if (!(syntax_pipes(newt_node)))
				return (NULL);
		}
		newt_node = newt_node->next;
	}
	return (head);
}

int	check_syntax_q(int *valid, t_node *copy, int i)
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

int	ft_syntax_quotes(t_node *head)
{
	t_node	*copy;
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
			g_global = 258;
			ft_putstr_fd("minishell : Syntax Error\n", 2);
			return (0);
		}
		copy = copy->next;
	}
	return (1);
}

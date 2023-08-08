/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:45:10 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/05 21:16:05 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	double_single(t_headvar *var, char *read)
{
	if (read[var->i] == '\'' && var->d == 0)
		var->s = !var->s;
	if (read[var->i] == '\"' && var->s == 0)
		var->d = !var->d;
}

void	quotes_manage(t_headvar *var, char *read, t_node **head)
{
	int	d;
	int	s;

	d = 0;
	s = 0;
	while (read[++var->i])
	{
		if (read[var->i] == '\'' && d == 0)
			s = !s;
		if (read[var->i] == '\"' && s == 0)
			d = !d;
		if ((d == 0) && (s == 0) && ft_symbols(read[var->i]))
		{
			var->cp = ft_substr(read, var->start, var->i - var->start);
			if (var->cp != '\0' && ft_strlen(var->cp) != 0)
				add_elements(head, var->cp);
			free(var->cp);
			var->i = string_list(read, var->i, head);
			var->start += (var->i - var->start) + 1;
		}
	}
}

void	free_head(t_node *head, t_node *temp)
{
	while (head)
	{
		temp = head->next;
		free(head->data);
		free(head);
		head = temp;
	}
}

t_node	*space_quotes(t_node *head)
{
	while (head)
	{
		if (head->data[0] == '"')
		{
			if (head->data[1] == '"' && !head->data[2])
			{
				head->data[0] = ' ';
				head->data[1] = ' ';
			}
		}
		else if (head->data[0] == '\'')
		{
			if (head->data[1] == '\'' && !head->data[2])
			{
				head->data[0] = ' ';
				head->data[1] = ' ';
			}
		}
		head = head->next;
	}
	return (head);
}

t_list	*ft_start(char *read, char **env)
{
	t_list		*copiedlist;
	t_node		*head;
	t_node		*temp;
	t_headvar	var;

	temp = NULL;
	head = NULL;
	init_headvar(&var);
	quotes_manage(&var, read, &head);
	var.cp = ft_substr(read, var.start, var.i - var.start);
	if (var.cp != '\0' && ft_strlen(var.cp) != 0)
		add_elements(&head, var.cp);
	free(var.cp);
	space_quotes(head);
	if (!syntaxq_return(head, temp))
		return (NULL);
	head = syntax_error(head);
	if (!head)
		return (NULL);
	copiedlist = copy_list(head);
	free_head(head, temp);
	copiedlist = ft_expand(copiedlist, env);
	copiedlist = ft_remove_quotes(copiedlist);
	return (copiedlist);
}

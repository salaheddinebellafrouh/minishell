/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:59:08 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/04 18:22:56 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_symbols(char c)
{
	if (c == ' ' || c == '>' || c == '<' || c == '|' || c == '>' || c == '\t')
		return (1);
	return (0);
}

int	string_list(char *read, int i, Node **head)
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

void	print_copy(t_list *list)
{
	Node	*currentarg;
	Node	*file;
	Node	*red;
	Node	*outfile;
	Node	*hairdoc;

	currentarg = NULL;
	file = NULL;
	while (list != NULL)
	{
		currentarg = list->arg;
		while (currentarg != NULL)
		{
			printf("Arg: %s\n", currentarg->data);
			currentarg = currentarg->next;
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

int	syntaxq_return(Node *head, Node *temp)
{
	if (!ft_syntax_quotes(head))
	{
		while (head)
		{
			temp = head->next;
			free(head->data);
			free(head);
			head = temp;
		}
		return (0);
	}
	return (1);
}
Node	*fill_space(Node *head)
{
	Node	*copy;

	copy = head;
	while (copy)
	{
		if (copy->data[0] == '"' && !copy->data[3])
		{
			if (copy->data[1] == '"')
			{
				copy->data[1] = ' ';
				copy->data[0] = ' ';
			}
		}
		else if (copy->data[0] == '\'' && !copy->data[3])
		{
			if (copy->data[1] == '\'')
			{
				copy->data[1] = ' ';
				copy->data[0] = ' ';
			}
		}
		copy = copy->next;
	}
	return (head);
}
t_list	*ft_start(char *read, char **env)
{
	t_list	*copiedlist;
	Node	*head;
	Node	*temp;
	(void)env;
	temp = NULL;
	head = NULL;
	int 	i = 0;
		int			s;
	int			d;
	char *cp;
	s = 0;
	d = 0;
	int			start = 0;
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
	if (!syntaxq_return(head, temp))
		return (NULL);
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

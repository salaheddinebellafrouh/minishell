/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 21:59:08 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/05 16:21:30 by sbellafr         ###   ########.fr       */
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

// void	print_copy(t_list *list)
// {
// 	Node	*currentarg;
// 	Node	*file;
// 	Node	*red;
// 	Node	*outfile;
// 	Node	*hairdoc;

// 	currentarg = NULL;
// 	file = NULL;
// 	while (list != NULL)
// 	{
// 		currentarg = list->arg;
// 		while (currentarg != NULL)
// 		{
// 			printf("Arg: %s\n", currentarg->data);
// 			currentarg = currentarg->next;
// 		}
// 		file = list->infiles;
// 		while (file != NULL)
// 		{
// 			printf("infiles: %s type : %d\n", file->data, file->type);
// 			file = file->next;
// 		}
// 		outfile = list->outfiles;
// 		while (outfile != NULL)
// 		{
// 			printf("outfiles: %s\n", outfile->data);
// 			outfile = outfile->next;
// 		}
// 		hairdoc = list->hairdoc;
// 		while (hairdoc != NULL)
// 		{
// 			printf("hairdoc: %s\n", hairdoc->data);
// 			hairdoc = hairdoc->next;
// 		}
// 		red = list->redirect;
// 		while (red != NULL)
// 		{
// 			printf("red: %s\n", red->data);
// 			red = red->next;
// 		}
// 		list = list->next;
// 		printf("---------\n");
// 	}
// }

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

void	init_headvar(t_headvar *var)
{
	var->i = -1;
	var->start = 0;
}

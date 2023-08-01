/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:06:27 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/01 15:59:01 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_fill_arg_her(t_list *copy, char **before, char **after)
{
	Node	*arg_copy;
	Node	*heredoc;

	arg_copy = copy->arg;
	while (arg_copy)
	{
		arg_copy->data = expnd_data(arg_copy->data, before, after);
		arg_copy = arg_copy->next;
	}
	heredoc = copy->hairdoc;
	while (heredoc)
	{
		heredoc->data = expnd_data(heredoc->data, before, after);
		heredoc = heredoc->next;
	}
}

void	ft_fill_out_in(t_list *copy, char **before, char **after)
{
	Node	*infiles;
	Node	*outfiles;

	outfiles = copy->outfiles;
	while (outfiles)
	{
		outfiles->data = expnd_data(outfiles->data, before, after);
		outfiles = outfiles->next;
	}
	infiles = copy->infiles;
	while (infiles)
	{
		infiles->data = expnd_data(infiles->data, before, after);
		infiles = infiles->next;
	}
}

t_list	*ft_fill_expand(t_list *list, char **before, char **after)
{
	t_list	*copy;

	copy = list;
	while (copy)
	{
		ft_fill_arg_her(copy, before, after);
		ft_fill_out_in(copy, before, after);
		copy = copy->next;
	}
	return (list);
}

void	free_ba(char **after, char **before)
{
	int	i;

	i = 0;
	while (before[i])
	{
		free(before[i]);
		free(after[i]);
		i++;
	}
	free(before);
	free(after);
}

t_list	*ft_expand(t_list *list, char **env)
{
	int		i;
	char	**before;
	char	**after;

	i = 0;
	while (env[i])
		i++;
	before = calloc(sizeof(char *), (i + 1));
	after = calloc(sizeof(char *), (i + 1));
	i = 0;
	while (env[i])
	{
		before[i] = calloc(sizeof(char), calloc_before(env[i]) + 1);
		after[i] = calloc(sizeof(char), calloc_after(env[i]) + 1);
		before[i] = ft_strcpy_before(before[i], env[i]);
		after[i] = ft_strcpy_after(after[i], env[i]);
		i++;
	}
	list = ft_fill_expand(list, before, after);
	free_ba(after, before);
	return (list);
}

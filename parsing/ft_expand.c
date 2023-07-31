/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:15:54 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/30 00:53:46 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_dollar(char *data)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (data[i] && ((ft_isalnum(data[i])) || data[i] == '_'
			|| data[i] == '$'))
	{
		if (data[i] == '$')
		{
			k++;
		}
		else if (data[i] != '$')
		{
			break ;
		}
		i++;
	}
	return (k);
}
char	*get_id2(char *data)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (data[i] && ((ft_isalnum(data[i])) || data[i] == '_'))
		i++;
	return (ft_substr(data, 0, i));
}

void	ft_count_dollar(char *data, char **before, char **after, t_vars *d)
{
	d->kk = count_dollar(&(data[d->i]));
	if (d->kk % 2 == 0)
	{
		while (data[d->i] == '$')
			d->i++;
		d->id = get_id2(&(data[d->i]));
	}
	else
		d->id = ft_strdup("1");
	d->l = 0;
	while (before[d->l])
	{
		if (strcmp(before[d->l], d->id) == 0)
		{
			d->k = 0;
			while (after[d->l][d->k])
			{
				if (after[d->l][d->k] != '"' && (after[d->l][d->k]))
				{
					d->s++;
				}
				d->k++;
			}
			break ;
		}
		d->l++;
	}
	d->i += ft_strlen(d->id) - 1;
	if (d->id)
	{
		free(d->id);
		d->id = NULL;
	}
}
void	ft_count_dn(t_vars *d, char *data)
{
	d->i++;
	if (ft_isdigit(data[d->i]))
	{
		while (data[d->i + 1] && data[d->i] != '$')
		{
			if (data[d->i + 1] != '$')
				d->s++;
			d->i++;
		}
		d->s++;
	}
}
int	ft_count_string(char *data, char **before, char **after)
{
	t_vars	d;

	d.s = 0;
	d.i = 0;
	while (data[d.i])
	{
		if (data[d.i] == '\'')
		{
			while (data[d.i] != '\'')
			{
				d.s++;
				d.i++;
			}
		}
		if (data[d.i] == '$' && data[d.i] && ft_isdigit(data[d.i + 1]))
		{
			if (!data[d.i + 1])
				return (strlen(data));
			ft_count_dn(&d, data);
		}
		else if (data[d.i] != '$')
		{
			if (data[d.i] == '$')
				d.s++;
			d.s++;
		}
		if (data[d.i] == '$' && ++d.i && data[d.i] && !ft_isdigit(data[d.i
				+ 1]))
		{
			if (!data[d.i])
				return (0);
			ft_count_dollar(data, before, after, &d);
		}
		d.i++;
	}
	return (d.s);
}
char	*expnd_data(char *data, char **before, char **after)
{
	int		i;
	int		l;
	int		k;
	int		j;
	int		s;
	char	*string;
	char	*id;
	int		count;
	int		kk;
	int		d;

	d = 0;
	j = 0;
	k = 0;
	l = 0;
	i = 0;
	s = 0;
	count = ft_count_string(data, before, after) + 1;
	string = malloc(count);
	i = 0;
	while (data[i])
	{
		if (data[i] != '$' && data[i] != '\'')
			string[s++] = data[i];
		else if (data[i] == '\'')
		{
			string[s++] = data[i++];
			while (data[i] && data[i] != '\'')
				string[s++] = data[i++];
			string[s++] = data[i];
		}
		else if (data[i] == '$' && data[i] && ft_isdigit(data[i + 1]))
		{
			if (!data[i + 1])
				return (data);
			i++;
			if (ft_isdigit(data[i]))
			{
				while (data[i + 1] && data[i] != '$')
				{
					if (data[i + 1] != '$')
					{
						string[s] = data[i + 1];
						s++;
					}
					i++;
				}
			}
		}
		else if (data[i] == '$' && ++i && data[i] && !ft_isdigit(data[i + 1]))
		{
			d = 1;
			if (!data[i])
				return (NULL);
			kk = count_dollar(&(data[i]));
			if (kk % 2 == 0)
			{
				while (data[i] == '$')
					i++;
				id = get_id2(&(data[i]));
			}
			else
				id = ft_strdup("1");
			l = 0;
			while (before[l])
			{
				if (strcmp(before[l], id) == 0)
				{
					k = 0;
					while (after[l][k])
					{
						if (after[l][k] != '"' && (after[l][k]))
						{
							string[s] = after[l][k];
							s++;
						}
						k++;
					}
					break ;
				}
				l++;
			}
			i += ft_strlen(id) - 1;
			if (id)
			{
				free(id);
				id = NULL;
			}
		}
		i++;
	}
	string[s] = '\0';
	free(data);
	return (string);
}
int	calloc_before(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '=' && string[i])
		i++;
	return (i);
}
int	calloc_after(char *string)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (string[i] != '=' && string[i])
		i++;
	while (string[i])
	{
		j++;
		i++;
	}
	return (j);
}
t_list	*ft_expand(t_list *list, char **env)
{
	int		i;
	t_list	*copy;
	char	**before;
	char	**after;
	int		j;
	int		k;
	int		l;
	char	**cp;
	Node	*arg_copy;
	Node	*infiles;
	Node	*outfiles;
	Node	*heredoc;

	i = 0;
	while (env[i])
		i++;
	cp = calloc(i + 1, sizeof(char *));
	i = 0;
	while (env[i])
	{
		cp[i] = ft_strdup(env[i]);
		i++;
	}
	before = calloc(sizeof(char *), (i + 1));
	after = calloc(sizeof(char *), (i + 1));
	j = 0;
	k = 0;
	l = 0;
	i = 0;
	while (cp[i])
	{
		before[i] = calloc(sizeof(char), calloc_before(cp[i]) + 1);
		after[i] = calloc(sizeof(char), calloc_after(cp[i]) + 1);
		before[i] = ft_strcpy_before(before[i], cp[i]);
		after[i] = ft_strcpy_after(after[i], cp[i]);
		free(cp[i]);
		i++;
	}
	free(cp);
	i = 0;
	// i = 0;
	copy = list;
	while (copy)
	{
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
		copy = copy->next;
	}
	i = 0;
	while (before[i])
	{
		free(before[i]);
		free(after[i]);
		i++;
	}
	free(before);
	free(after);
	return (list);
}
int	count_quotes(char *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data[i])
	{
		if (data[i] == '"')
		{
			i++;
			while (data[i] != '"' && data[i])
			{
				i++;
			}
			count = count + 2;
		}
		else if (data[i] == '\'')
		{
			i++;
			while (data[i] != '\'' && data[i])
			{
				i++;
			}
			count = count + 2;
		}
		i++;
	}
	return (count);
}
char	*ft_rquotes(char *data)
{
	int		i;
	int		j;
	char	*returned;

	j = 0;
	i = 0;
	returned = malloc(ft_strlen(data) + 3000);
	while (data[i])
	{
		if (data[i] && data[i] == '"')
		{
			i++;
			while (data[i] && data[i] != '"')
			{
				returned[j] = data[i];
				i++;
				j++;
			}
			i++;
		}
		if (data[i] && data[i] == '\'')
		{
			i++;
			while (data[i] && data[i] != '\'')
			{
				returned[j] = data[i];
				i++;
				j++;
			}
			i++;
		}
		else
		{
			while (data[i])
			{
				if (data[i] != '"' && data[i] != '\'')
				{
					returned[j] = data[i];
					j++;
				}
				i++;
			}
		}
	}
	returned[j] = '\0';
	free(data);
	return (returned);
}
t_list	*ft_remove_quotes(t_list *list)
{
	t_list	*copied;
	Node	*arg;

	arg = list->arg;
	copied = list;
	while (copied)
	{
		while (arg)
		{
			arg->data = ft_rquotes(arg->data);
			arg = arg->next;
		}
		copied = copied->next;
	}
	return (list);
}

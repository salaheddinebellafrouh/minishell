/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 15:15:54 by sbellafr          #+#    #+#             */
/*   Updated: 2023/07/19 13:28:33 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_id(char *data)
{
	int	i;
	
	i = 0;
	while (data[i] && ((ft_isalnum(data[i])) || data[i] == '_'))
		i++;
	return (ft_substr(data, 0, i));
}
int		ft_count_string(char *data, char **before, char **after)
{
	int	i;
	int	j;
	int	k;
	int	s;
	int d = 0;
	int l;
	char *id;
	
	l = 0;
	s = 0;
	i = 0;
	j = 0;
	k = 0;
	while (data[i])
	{
		if(data[i] == '\'')
		{
			i++;
			while (data[i] && data[i] != '\'')
			{
				i++;
				s++;
			}
			s = s + 2;
		}
		else if (data[i] == '$' && ++i)
		{
			id = get_id(&(data[i]));
			l = 0;
			while (before[l])
			{
				// printf("%s\n", before[l]);
				if (strcmp(before[l], id) == 0)
				{
					// free(id);
					k = 0;
					while (after[l][k])
					{
						s++;
						k++;
					}
					break ;
				}
				l++;
			}
			i += ft_strlen(id) - 1;
		}
		else
		{
			s++;
		}
		d += s;
		i++;
	}
	// if(id)
	// 	free(id);
		
	// free(data);

	return (s);
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
	j = 0;
	k = 0;
	l = 0;
	i = 0;
	s = 0;

	int count = ft_count_string(data, before, after) + 1;
	string = malloc(count);
	i = 0;
	while (data[i])
	{

		if (data[i] == '\'')
		{
			i++;
			string[s] = '\'';
			s++;
			while (data[i] && data[i] != '\'')
				string[s++] = data[i++];
			string[s] = '\'';
			s++;
		}
		else if (data[i] == '$' && ++i)
		{
			id = get_id(&(data[i]));
			l = 0;
			while (before[l])
			{
				if (strcmp(before[l], id) == 0)
				{
					// free(id);
					k = 0;
					while (after[l][k])
					{
						string[s] = after[l][k];
						s++;
						k++;
					}
					break ;
				}
				l++;
			}
			i += ft_strlen(id) - 1;
		}
		else
		{
			string[s] = data[i];
			s++;
		}

		i++;
	}
	string[s] = '\0';
	// if(id)
	// 	free(id);
	free(data);
	return (string);
}
int calloc_before(char *string)
{
	int	i;
	
	i = 0;
	while(string[i] != '=' && string[i])
		i++;
	return (i);
}
int calloc_after(char *string)
{
	int	i;
	int	j;
	i = 0;
	j = 0;
	while(string[i] != '=' && string[i])
		i++;
	while(string[i])
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

	i = 0;
	while(env[i])
		i++;
	cp = calloc(i + 1 , sizeof(char *));
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
		before[i] = calloc(sizeof(char), 	calloc_before(cp[i]) + 1);
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
	Node *arg_copy ;
	Node *infiles ;
	Node *outfiles ;
	Node *heredoc ;

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
	while(before[i])
	{
		free(before[i]);
		free(after[i]);
		i++;
	}
	free(before);
	free(after);
	return (list);

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:25:08 by sbellafr          #+#    #+#             */
/*   Updated: 2023/08/04 16:15:31 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*var_dollar(t_vars *vars, char *data, char *string, char **after,
		char **before)
{
	vars->d = 1;
	vars->kk = count_dollar(&(data[vars->i]));
	if (vars->kk % 2 == 0)
	{
		while (data[vars->i] == '$')
			vars->i++;
		vars->id = get_id2(&(data[vars->i]));
	}
	else
		vars->id = ft_strdup("1");
	vars->l = 0;
	string = before_after(before, after, vars, string);
	vars->i += ft_strlen(vars->id) - 1;
	if (vars->id)
	{
		free(vars->id);
		vars->id = NULL;
	}
	return (string);
}

char	*ft_fill_single(t_vars *vars, char *data, char *string)
{
	string[vars->s++] = data[vars->i++];
	while (data[vars->i] && data[vars->i] != '\'')
		string[vars->s++] = data[vars->i++];
	string[vars->s++] = data[vars->i];
	return (string);
}

char	*expnd_data(char *data, char **before, char **after)
{
	char	*string;
	t_vars	vars;
	char	*g_str;
	int		s;

	init_vars(&vars);
	vars.count = ft_count_string(data, before, after) + 1;
	string = malloc(vars.count + 1);
	while (data[vars.i])
	{
		if (data[vars.i] == '$' && data[vars.i + 1] == '?')
		{
			vars.i++;
			g_str = ft_itoa(g_global);
			s = 0;
			while (g_str[s])
			{
				string[vars.s] = g_str[s];
				s++;
				vars.s++;
			}
			free(g_str);
		}
		else if (data[vars.i] != '$' && data[vars.i] != '\'')
			string[vars.s++] = data[vars.i];
		else if (data[vars.i] == '\'')
			string = ft_fill_single(&vars, data, string);
		else if (data[vars.i] == '$' && data[vars.i] && ft_isdigit(data[vars.i
					+ 1]))
			digit_dollar(&vars, data, string);
		else if (data[vars.i] == '$' && ++vars.i && data[vars.i]
				&& !ft_isdigit(data[vars.i + 1]))
			string = var_dollar(&vars, data, string, after, before);
		if (data[vars.i])
			vars.i++;
	}
	string[vars.s] = '\0';
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

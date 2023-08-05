/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 00:18:30 by nchaknan          #+#    #+#             */
/*   Updated: 2023/08/05 21:16:05 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_double_demen(char **split)
{
	int	j;

	j = -1;
	while (split[++j])
		free(split[j]);
	free(split);
}

int	check_arg(char *arg)
{
	int	i;

	i = -1;
	if (arg[0] == '_' || (arg[0] >= 65 && arg[0] <= 90) || (arg[0] >= 97
			&& arg[0] <= 122))
		i++;
	else
		return (0);
	while (arg[++i])
	{
		if (!ft_isalnum_v2(arg[i]))
			return (0);
	}
	return (1);
}

int	ft_lstsize(t_node *lst)
{
	int		count;
	t_node	*temp;

	count = 0;
	temp = (t_node *)lst;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

void	fill_args_arr(t_builtins *builts, t_list *list)
{
	t_node	*currentarg;
	int		i;

	currentarg = list->arg;
	i = 0;
	builts->args_arr = malloc((ft_lstsize(currentarg) + 1) * sizeof(char *));
	while (currentarg)
	{
		builts->args_arr[i] = strdup(currentarg->data);
		i++;
		currentarg = currentarg->next;
	}
	builts->args_arr[i] = NULL;
	builts->arg_len = i;
}

int	check_command(char *arg, char *str1)
{
	if (arg && !ft_strncmp(arg, str1, ft_strlen(str1))
		&& ft_strlen(arg) == ft_strlen(str1))
		return (1);
	return (0);
}

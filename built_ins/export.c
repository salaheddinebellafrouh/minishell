/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchaknan <nchaknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:59:04 by nchaknan          #+#    #+#             */
/*   Updated: 2023/08/05 18:13:18 by nchaknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_builtins *builts)
{
	char	**split;
	char	*variable;
	char	*value;
	int		j;

	j = -1;
	while (builts->env[++j])
	{
		split = ft_split(builts->env[j], '=');
		variable = split[0];
		value = ft_strchr(builts->env[j], '=');
		printf("declare -x %s", variable);
		if (if_equal_exist(builts->env[j]))
			printf("=");
		if (value)
			printf("\"%s\"", value);
		printf("\n");
		free_double_demen(split);
	}
}

void	export_exist(t_builtins *builts, char *arg, char *var, char *val)
{
	char	*new_vrbl;

	if (if_equal_exist(arg) && val)
	{
		var = ft_strjoin(var, "=");
		new_vrbl = var;
		var = ft_strjoin(new_vrbl, val);
		free(new_vrbl);
		free(builts->env[builts->exp_var_place]);
		builts->env[builts->exp_var_place] = var;
	}
	else if (if_equal_exist(arg))
	{
		var = ft_strjoin(var, "=");
		free(builts->env[builts->exp_var_place]);
		builts->env[builts->exp_var_place] = var;
	}
}

void	export_not_exist(t_builtins *builts, char *arg)
{
	char	**new_env;
	int		j;

	builts->env_len++;
	new_env = malloc(sizeof(char *) * (builts->env_len + 2));
	j = -1;
	while (builts->env[++j])
		new_env[j] = builts->env[j];
	new_env[j] = ft_strdup(arg);
	new_env[++j] = NULL;
	free(builts->env);
	builts->env = new_env;
}

int	srch_export_var_exist(t_builtins *builts, char *variable)
{
	int	len;
	int	exist;
	int	j;

	len = 0;
	while (variable[len])
		len++;
	exist = 0;
	j = -1;
	while (builts->env[++j])
	{
		if (!ft_strncmp(variable, builts->env[j], len))
		{
			exist = 1;
			builts->exp_var_place = j;
			break ;
		}
	}
	return (exist);
}

void	my_export(t_builtins *builts, char *arg)
{
	int		exist;
	char	**split;
	char	*variable;
	char	*value;

	split = ft_split(arg, '=');
	variable = split[0];
	value = split[1];
	if (arg && !check_arg(variable))
	{
		printf("export: `%s': not a valid identifier\n", arg);
		free_double_demen(split);
	}
	else
	{
		exist = srch_export_var_exist(builts, variable);
		if (exist)
			export_exist(builts, arg, variable, value);
		else if (!exist)
			export_not_exist(builts, arg);
		free_double_demen(split);
	}
}

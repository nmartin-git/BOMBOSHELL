/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:37:52 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/12 14:01:50 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

static void	handle_export_arg(t_env *env, char *arg)
{
	char	*equals;
	char	*key;
	char	*value;
	char	*expanded_key;

	equals = ft_strchr(arg, '=');
	expanded_key = NULL;
	if (!equals)
	{
		if (arg[0] == '"')
		{
			expanded_key = get_env_value(env, arg + 1);
			if (is_valid_identifier(arg) && expanded_key)
				set_env_value(env, arg, NULL);
			else
				printf("export: '%s': not a valid identifier\n", arg);
		}
		else if (is_valid_identifier(arg))
			set_env_value(env, arg, NULL);
		else
			printf("export: '%s': not a valid identifier\n", arg);
		return ;
	}
	*equals = '\0';
	key = arg;
	value = equals + 1;
	if (key[0] == '$')
	{
		expanded_key = get_env_value(env, key + 1);
		if (expanded_key && is_valid_identifier(expanded_key))
			set_env_value(env, expanded_key, value);
		else
			printf("export: '%s': not a valid identifier\n", arg);
	}
	else if (is_valid_identifier(key))
		set_env_value(env, key, value);
	else
		printf("export: '%s': not a valid identifier\n", arg);
}

static void	print_exports(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		printf("declare -x %s", current->key);
		if (current->value)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

int	ft_export(t_shell *cmd, char *command)
{
	int	i;
	i = 0;
	printf("|%s|", command);
	if (!cmd->command[1])
	{
		print_exports(cmd->env_vars);
		return (0);
	}
	i = 1;
	while (cmd->command[i])
	{
		handle_export_arg(cmd->env_vars, cmd->command[i]);
		i++;
	}
	return (0);
}

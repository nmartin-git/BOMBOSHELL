/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:37:52 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/18 19:36:35 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	handle_export_no_equals(t_env *env, char *cmd)
{
	if (!is_valid_identifier(cmd))
		return (print_invalid_id_error("export", cmd), 1);
	if (!get_env_value(env, cmd))
		set_env_value(env, cmd, NULL);
	return (0);
}

static int	handle_export_with_value(t_env *env, char *cmd, char *equals)
{
	char	*key;
	char	*value;
	char	*trimmed_value;

	*equals = '\0';
	key = cmd;
	value = equals + 1;
	if (!is_valid_identifier(key))
	{
		*equals = '=';
		return (print_invalid_id_error("export", key), 1);
	}
	trimmed_value = trim_quotes(value);
	if (!trimmed_value)
	{
		*equals = '=';
		return (print_invalid_id_error("export", value), 1);
	}
	set_env_value(env, key, trimmed_value);
	free(trimmed_value);
	*equals = '=';
	return (0);
}

static int	handle_export_arg(t_env *env, char *cmd)
{
	char	*equals;

	equals = ft_strchr(cmd, '=');
	if (!equals)
		return (handle_export_no_equals(env, cmd));
	if (equals == cmd)
		return (print_invalid_id_error("export", cmd), 1);
	return (handle_export_with_value(env, cmd, equals));
}

static int	handle_multiple_exports(t_env *env, char *command)
{
	char	**pairs;
	int		i;
	int		exit_code;

	pairs = split_sous_stero(&command);
	if (!pairs)
		return (1);
	i = 0;
	exit_code = 0;
	while (pairs[i])
	{
		if (handle_export_arg(env, pairs[i]))
			exit_code = 1;
		free(pairs[i]);
		i++;
	}
	free(pairs);
	return (exit_code);
}

static void	print_exports(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		printf("export %s", current->key);
		if (current->value)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

int	ft_export(t_shell *cmd, char *command)
{
	int	exit_code;

	if (!cmd->command[1])
	{
		print_exports(cmd->env_vars);
		return (0);
	}
	if (ft_strncmp(command, "export ", 7) == 0)
		command += 7;
	exit_code = handle_multiple_exports(cmd->env_vars, command);
	return (exit_code);
}

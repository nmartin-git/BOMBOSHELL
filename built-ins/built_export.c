/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:37:52 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/16 21:46:07 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	handle_export_arg(t_env *env, char *cmd)
{
	char	*equals;
	char	*key;
	char	*value;
	char	*trimmed_value;

	equals = ft_strchr(cmd, '=');
	if (!equals || equals == cmd || *(equals + 1) == '\0')
		return (print_invalid_id_error(cmd, NULL), 1);
	*equals = '\0';
	key = cmd;
	value = equals + 1;
	if (!is_valid_identifier(key))
	{
		*equals = '=';
		return (print_invalid_id_error(key, NULL), 1);
	}
	trimmed_value = trim_quotes(value);
	if (!trimmed_value)
	{
		*equals = '=';
		return (print_invalid_id_error(value, NULL), 1);
	}
	(set_env_value(env, key, trimmed_value), free(trimmed_value));
	*equals = '=';
	return (0);
}

static void	handle_multiple_exports(t_env *env, char *command)
{
	char	**pairs;
	int		i;

	pairs = split_sous_stero(&command);
	if (!pairs)
		return ;
	i = 0;
	while (pairs[i])
	{
		handle_export_arg(env, pairs[i]);
		free(pairs[i]);
		i++;
	}
	free(pairs);
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
	int	exit_status;

	exit_status = 0;
	if (!cmd->command[1])
	{
		print_exports(cmd->env_vars);
		return (0);
	}
	if (ft_strncmp(command, "export ", 7) == 0)
		command += 7;
	handle_multiple_exports(cmd->env_vars, command);
	return (exit_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:37:52 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/06 16:27:36 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

// static int	handle_equales(t_env *env, char *arg)
// {
// 	char	*expanded_key;

// 	expanded_key = get_env_value(env, arg + 1);
// 	printf("equals b4 if\n");
// 	if (arg[0] == '$')
// 	{
// 		if (is_valid_identifier(arg) && expanded_key)
// 			set_env_value(env, arg, expanded_key);
// 		else
// 			return (print_invalid_id_error(arg, NULL), 1);
// 	}
// 	else if (is_valid_identifier(arg))
// 		set_env_value(env, arg, expanded_key);
// 	else
// 		return (print_invalid_id_error(arg, NULL), 1);
// 	return (0);
// }

// static int	handle_expanded_key(t_env *env, char *key, char *value,
//		char *arg)
// {
// 	char	*expanded_key;

// 	expanded_key = get_env_value(env, key + 1);
// 	printf("exp key ft\n");
// 	if (!expanded_key)
// 	{
// 		ft_putstr_fd("export: '", 2);
// 		ft_putstr_fd(arg, 2);
// 		ft_putstr_fd("': not a valid identifier: variable not set\n", 2);
// 	}
// 	else if (is_valid_identifier(expanded_key))
// 		set_env_value(env, expanded_key, value);
// 	else
// 		return (print_invalid_id_error(arg, NULL), 1);
// 	return (0);
// }

// static char	*spliting_quotes(char *value)
// {
// 	char	quote;
// 	int		len;

// 	len = ft_strlen(value);
// 	if (len > 0 && (*value == '"' || *value == '\''))
// 	{
// 		quote = *value;
// 		if (len > 1 && value[len - 1] == quote)
// 		{
// 			value[len - 1] = '\0';
// 			value++;
// 		}
// 	}
// 	return (value);
// }

// char	*trim_last_quote(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '"')
// 		{
// 			s[i] = '\0';
// 			return (s);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

static int	handle_export_arg(t_env *env, char *arg, char *str)
{
	char	*equals;
	char	*key;
	char	*value;
	int		len;

	(void)str;
	printf("strb4:%s\n", str);
	equals = ft_strchr(str, '=');
	if (!equals)
		return (print_invalid_id_error(str, NULL), 1);
	*equals = '\0';
	key = str;
	value = equals + 1;
	len = ft_strlen(value);
	printf("(in handle exp arg) key:%s, value:%s\n", key, value);
	if (value[0] == '"')
	{
		printf("value b4 trim:%s\n", value);
		if (len > 1 && value[len - 1] == '"')
		{
			value[len - 1] = '\0';
			value++;
		}
		printf("value after trim:%s\n", value);
		set_env_value(env, key, value);
	}
	if (is_valid_identifier(key))
		set_env_value(env, key, value);
	else
		return (print_invalid_id_error(arg, NULL), printf("here %s\n", key), 1);
	return (0);
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

int	ft_export(t_shell *cmd, char *str)
{
	int	i;

	printf("IN FT%s\n", str);
	if (!cmd->command[1])
	{
		print_exports(cmd->env_vars);
		return (0);
	}
	i = 1;
	while (cmd->command[i])
	{
		if (!handle_export_arg(cmd->env_vars, cmd->command[i], str))
			return (1);
		i++;
	}
	return (0);
}

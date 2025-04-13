/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:36:54 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/06 18:16:34 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

static void	print_cd_error(char *s, char *dir)
{
	if (!dir)
		ft_printf_fd(2, "%s\n", s);
	else
	{
		ft_printf_fd(2, "%s\n", s);
		perror(dir);
	}
}

int	ft_cd(t_shell *cmd)
{
	char	*new_dir;
	char	*old_pwd;

	if (cmd->command[1] && cmd->command[2])
		return (print_cd_error("bomboshell: cd: too many arguments", NULL), 1);
	old_pwd = cmd->current_dir;
	if (!cmd->command[1])
		new_dir = get_env_value(cmd->env_vars, "HOME");
	else
		new_dir = cmd->command[1];
	if (!new_dir)
		return (print_cd_error("bomboshell: cd: HOME not set", NULL), 1);
	if (chdir(new_dir) == -1)
		return (print_cd_error("bomboshell: cd: HOME not set", new_dir), 1);
	set_env_value(cmd->env_vars, "OLDPWD", old_pwd);
	cmd->current_dir = getcwd(NULL, 0);
	if (!cmd->current_dir)
	{
		perror("getcwd");
		cmd->current_dir = ft_strdup(new_dir);
	}
	set_env_value(cmd->env_vars, "PWD", cmd->current_dir);
	return (0);
}

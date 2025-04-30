/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:36:54 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/30 20:25:34 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	cd_too_many_args(t_shell *cmd)
{
	if (cmd->command[1] && cmd->command[2])
	{
		ft_printf_fd(2, "bomboshell: cd: too many arguments\n");
		return (1);
	}
	return (0);
}

static int	cd_change_dir(t_shell *cmd, char *new_dir, char *old_pwd)
{
	if (chdir(new_dir) == -1)
	{
		ft_putstr_fd("bomboshell: cd:", 2);
		perror(new_dir);
		g_exit_status = 1;
		return (1);
	}
	set_env_value(cmd->env_vars, "OLDPWD", old_pwd);
	if (cmd->current_dir)
		free(cmd->current_dir);
	cmd->current_dir = getcwd(NULL, 0);
	if (!cmd->current_dir)
	{
		perror("getcwd");
		cmd->current_dir = ft_strdup(new_dir);
	}
	set_env_value(cmd->env_vars, "PWD", cmd->current_dir);
	g_exit_status = 0;
	return (0);
}

int	ft_cd(t_shell *cmd)
{
	char	*new_dir;
	char	*old_pwd;

	if (cd_too_many_args(cmd))
		return (1);
	old_pwd = cmd->current_dir;
	if (!cmd->command[1])
		new_dir = get_env_value(cmd->env_vars, "HOME");
	else
		new_dir = cmd->command[1];
	if (!new_dir)
	{
		ft_printf_fd(2, "bomboshell: cd: HOME not set\n");
		return (1);
	}
	return (cd_change_dir(cmd, new_dir, old_pwd));
}

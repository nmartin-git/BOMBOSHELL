/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:36:54 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/14 19:01:36 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(t_shell *cmd)
{
	char	*new_dir;
	char	*old_pwd;
	
	if (cmd->command[1] && cmd->command[2])
	{
		ft_printf_fd(2, "bomboshell: cd: too many arguments");
		return (1);
	}
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
	if (chdir(new_dir) == -1)
	{
		ft_putstr_fd("bomboshell: cd:", 2);
		perror(new_dir);
		cmd->last_exit_status = 1;
		return (0);
	}
	set_env_value(cmd->env_vars, "OLDPWD", old_pwd);
	cmd->current_dir = getcwd(NULL, 0);
	if (!cmd->current_dir)
	{
		perror("getcwd");
		cmd->current_dir = ft_strdup(new_dir);
	}
	set_env_value(cmd->env_vars, "PWD", cmd->current_dir);
	cmd->last_exit_status = 0;
	return (1);
}

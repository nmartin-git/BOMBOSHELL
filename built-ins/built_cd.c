/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:36:54 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/04 22:42:16 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built-ins.h"

int	ft_cd(t_command *cmd, t_shell *shell)
{
	char	*new_dir;
	char	*old_pwd;

	old_pwd = shell->current_dir;
	if (cmd->argc == 1)
		new_dir = get_env_value(shell->env_vars, "HOME");
	else
		new_dir = cmd->argv[1];
	if (!new_dir)
	{
		printf("cd: HOME not set\n");
		return (1);
	}
	if (chdir(new_dir) == -1)
	{
		ft_putstr_fd("bomboshell:cd:", 2);
		perror(new_dir);
		shell->last_exit_status = 1;
		return (0);
	}
	set_env_value(shell->env_vars, "OLDPWD", old_pwd);
	shell->current_dir = getcwd(NULL, 0);
	if (!shell->current_dir)
	{
		perror("getcwd");
		shell->current_dir = ft_strdup(new_dir);
	}
	set_env_value(shell->env_vars, "PWD", shell->current_dir);
	shell->last_exit_status = 0;
	return (1);
}

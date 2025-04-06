/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:07:27 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/06 18:21:35 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdio.h>//TODO supp

void print_tokens(t_input *arg_lst) //TODO supp
{
	t_input *tmp;

	tmp = arg_lst;
	while (tmp)
	{
		if (tmp->token == HERE_DOC)
			printf("HERE_DOC -> ");
		else if (tmp->token == INFILE)
			printf("INFILE -> ");
		else if (tmp->token == OUTFILE)
			printf("OUTFILE -> ");
		else if (tmp->token == APPEND)
			printf("APPEND -> ");
		else if (tmp->token == CMD)
			printf("CMD -> ");
		else if (tmp->token == REDIR)
			printf("REDIR -> ");
		else if (tmp->token == PIPE)
			printf("PIPE -> ");
		else if (tmp->token == WORD)
			printf("WORD -> ");
		else if (tmp->token == WORD_D_QUOTE)
			printf("WORD_D_QUOTE -> ");
		else if (tmp->token == WORD_S_QUOTE)
			printf("WORD_S_QUOTE -> ");
		else if (tmp->token == SPACES)
			printf("SPACES -> ");
		else if (tmp->token == BOOL)
			printf("BOOL -> ");
		else if (tmp->token == PARANTHESIS)
			printf("PARANTHESIS -> ");
		else if (tmp->token == QUOTE)
			printf("QUOTE -> ");
		tmp = tmp->next;
	}
	printf("null\n");
}//TODO supp ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void	handle_exec(t_input *cmd, t_input *files, t_exec *exec_lst)
{
	// if (is_built - ins)
	// 	// exec_built-ins(tmp, files, input, output)
	// else
	// 	// exec_cmd(tmp, files, input, output)
	cmd = files;
	exec_lst = NULL;
}

int exec(t_input **arg_lst, t_env **env)
{
	t_input *tmp;
	t_input *files;
	t_exec	*exec_lst;
	t_exec	*exec_tmp;

	//print_tokens(*arg_lst);//TODO supp
	files_tokenisation(arg_lst, NULL);
	// expend_env_var
	cmd_tokenisation(*arg_lst);
	tmp = *arg_lst;
	files = *arg_lst;
	exec_lst = exec_init(*arg_lst, NULL);
	exec_tmp = exec_lst;
	while (tmp)
	{
		if (tmp->token == CMD)
		{
			if (is_built_in(tmp->arg, 0))
				execute_builtin(env, tmp->arg);
			else
				handle_exec(tmp, files, exec_tmp);
			while (files && files->token != PIPE && files->token != BOOL)
				files = files->next;
			exec_tmp = exec_tmp->next;
		}
		tmp = tmp->next;
	}
	//print_tokens(*arg_lst);//TODO supp
	return (0);
}

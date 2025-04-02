/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmartin <nmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:52:33 by nmartin           #+#    #+#             */
/*   Updated: 2025/04/02 14:18:36 by nmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#include <stdio.h>
#include "exec.h"

void	print_tokens(t_input *arg_lst)
{
    t_input	*tmp;

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
}

void    exec_cmd(t_input *arg_lst)
{
    
}

int	exec(t_input **arg_lst)
{
	print_tokens(*arg_lst);
	files_tokenisation(arg_lst, NULL);
    //expend_env_var
    cmd_tokenisation(*arg_lst);
    //exec
	print_tokens(*arg_lst);
	return (0);
}

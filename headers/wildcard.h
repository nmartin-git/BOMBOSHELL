/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atazzit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+ +#+#+#+#+#+   */
/*   Created: 2025/04/11 16:32:19 by atazzit           #+#    #+#             */
/*   Updated: 2025/04/11 17:34:49 by atazzit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "bomboshell.h"
# include "libft.h"
# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>

typedef struct s_wildcard
{
	char				*content;
	struct s_wildcard	*next;
	// int					count;
}						t_wildcard_list;

t_wildcard_list			*expand_wildcards(char *pattern);
int						match_pattern(const char *pattern, const char *str);
void					list_add_back_wildcard(t_wildcard_list **head,
							char *content);
void					list_free_wildcard(t_wildcard_list *head);
char					**list_to_array(t_wildcard_list *head);
char					**expand_args_wildcards(char **args);
int						has_wildcards(const char *str);
void					find_matches(char **args, t_wildcard_list **expanded,
							int i);
void					expand_wildcards_in_tokens(t_input *arg_lst);
char					**list_to_array(t_wildcard_list *head);
int						list_size(t_wildcard_list *head);
t_wildcard_list			*add_match(t_wildcard_list *matches, char *pattern,
							int i);

#endif

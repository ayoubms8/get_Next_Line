/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:16:04 by alemsafi          #+#    #+#             */
/*   Updated: 2022/11/03 12:38:05 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_nl(t_list *stash)
{
	t_list	*last;
	int		i;

	if (!stash)
		return (0);
	last = ft_lstlast(stash);
	i = 0;
	while (last->content[i])
	{
		if (last->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (tmp == NULL)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_buf_to_stash(t_list **stash, char *buff, int ch7al_read)
{
	t_list	*new_node;
	t_list	*last;
	int		i;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->content = malloc(sizeof(char) * (ch7al_read + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buff[i] && i < ch7al_read)
	{
		new_node->content[i] = buff[i];
		i++;
	}
	new_node->content[i] = '\0';
	new_node->next = NULL;
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lstlast(*stash);
	last->next = new_node;
}

void	free_stash(t_list *stash)
{
	t_list	*tmp;

	if (!stash)
		return ;
	while (stash)
	{
		tmp = (stash)->next;
		free((stash)->content);
		free(stash);
		stash = tmp;
	}
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

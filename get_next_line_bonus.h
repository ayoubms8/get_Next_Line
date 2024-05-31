/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:48:22 by alemsafi          #+#    #+#             */
/*   Updated: 2022/11/09 10:48:24 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
int		found_nl(t_list *stash);
t_list	*ft_lstlast(t_list *lst);
void	read_add_tostash(int fd, t_list **stash);
void	add_buf_to_stash(t_list **stash, char *buff, int ch7al_read);
void	allocate_line(t_list *stash, char **line);
void	extract_line(t_list *stash, char **line);
void	clean_stash(t_list **stash);
void	free_stash(t_list *stash);
size_t	ft_strlen(const char *str);

#endif

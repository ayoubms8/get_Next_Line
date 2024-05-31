/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemsafi <alemsafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:14:30 by alemsafi          #+#    #+#             */
/*   Updated: 2023/06/12 16:52:10 by alemsafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	read_add_tostash(fd, &stash);
	if (stash == NULL)
		return (NULL);
	extract_line(stash, &line);
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_add_tostash(int fd, t_list **stash)
{
	char	*buf;
	int		ch7al_read;

	ch7al_read = 1;
	while (!found_nl(*stash) && ch7al_read != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return ;
		ch7al_read = (int)read(fd, buf, BUFFER_SIZE);
		if ((*stash == NULL && ch7al_read == 0) || ch7al_read == -1)
		{
			free(buf);
			return ;
		}
		buf[ch7al_read] = '\0';
		add_buf_to_stash(stash, buf, ch7al_read);
		free(buf);
	}
}

void	allocate_line(t_list *stash, char **line)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	allocate_line(stash, line);
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*node;
	int		i;
	int		j;

	node = malloc(sizeof(t_list));
	if (stash == NULL || node == NULL)
		return ;
	node->next = NULL;
	last = ft_lstlast(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] && last->content[i] == '\n')
		i++;
	node->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i) + 1));
	if (node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		node->content[j++] = last->content[i++];
	node->content[j] = '\0';
	free_stash(*stash);
	*stash = node;
}

#include <stdio.h>
#include <fcntl.h>

#include "stdlib.h"
#include "unistd.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	while (src[i] != '\0')
		i++;
	dest = malloc(i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != 0)
		++i;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dest)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		dest[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		dest[i + j] = s2[j];
	dest[i + j] = '\0';
	free(s1);
	return (dest);
}

char	*get_line_cleanstr(char **str)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
	{
		line[i] = (*str)[i];
		i++;
	}
	line[i] = '\0';
	if ((*str)[i] == '\n')
		i++;
	temp = ft_strdup(*str + i);
	free(*str);
	*str = temp;
	return (line);
}

int	ft_strchr(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		++i;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buff;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	if (!str)
		str = ft_strdup("");
	while (!ft_strchr(str, '\n'))
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i <= 0)
			break ;
		buff[i] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	if (i < 0)
		return (NULL);
	return (get_line_cleanstr(&str));
}

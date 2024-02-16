/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskhairi <mskhairi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:14:58 by mskhairi          #+#    #+#             */
/*   Updated: 2024/02/16 22:19:03 by mskhairi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **s1)
{
	free(*s1);
	*s1 = NULL;
}

char	*ft_next(char *str)
{
	char	*next;
	int		index;
	int		i;

	i = 0;
	index = 0;
	index = ft_strchr(str, '\n');
	if (index == -1)
		return (NULL);
	if (str[index + 1] == 0)
	{
		ft_free(&str);
		return (NULL);
	}
	index++;
	next = ft_calloc(ft_strlen(str + index) + 1, 1);
	if (!next)
	{
		ft_free(&str);
		return (strdup("fail allocation"));
	}
	while (str[index])
		next[i++] = str[index++];
	ft_free(&str);
	return (next);
}

char	*ft_new_line(char *str)
{
	char	*new_line;
	int		index;

	if (!str || !*str)
		return (NULL);
	index = ft_strchr(str, '\n');
	if (index == -1)
		return (str);
	else
	{
		index++;
		new_line = ft_calloc(index + 1, 1);
	}
	if (!new_line)
		return (NULL);
	while (index--)
		new_line[index] = str[index];
	return (new_line);
}

void	ft_readalloc(int fd, char **next)
{
	char	*buff;
	int		r;

	r = 1;
	buff = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buff)
	{
		ft_free(next);
		return ;
	}
	while (ft_strchr(buff, '\n') == -1 && r != 0)
	{
		r = read(fd, buff, BUFFER_SIZE);
		if (r == -1)
		{
			ft_free(next);
			break ;
		}
		buff[r] = '\0';
		*next = ft_strjoin(*next, buff);
		if (!*next)
			break ;
	}
	ft_free(&buff);
}

char	*get_next_line(int fd)
{
	char		*new_line;
	static char	*next;

	new_line = 0;
	if (BUFFER_SIZE > INT_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	ft_readalloc(fd, &next);
	if (!next)
		return (NULL);
	new_line = ft_new_line(next);
	next = ft_next(next);
	if (!new_line)
	{
		ft_free(&next);
		return (NULL);
	}
	return (new_line);
}

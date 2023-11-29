/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antramir <antramir@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:14:36 by antramir          #+#    #+#             */
/*   Updated: 2022/09/02 23:17:52 by antramir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read_text(int fd, char *stack)
{
	char	*buffer;
	int		bytes;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (bytes != 0 && ft_strchr(stack, '\n') == NULL)
	{
		bytes = read (fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		stack = ft_strjoin(stack, buffer);
	}
	free(buffer);
	return (stack);
}

static char	*ft_get_line(char *stack)
{
	char	*line;
	int		num_char;
	int		i;

	num_char = 0;
	if (stack[num_char] == '\0')
		return (NULL);
	while (stack[num_char] != '\n' && stack[num_char] != '\0')
		num_char++;
	line = (char *)malloc(sizeof(char) * num_char + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (i <= num_char)
	{
		line[i] = stack[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_remove_characters(char *stack)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (stack[i] != '\n' && stack[i] != '\0')
		i++;
	if (stack[i] == '\0')
	{
		free(stack);
		return (NULL);
	}
	str = (char *)malloc((ft_strlen(stack) - i) + 1);
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (stack[i] != '\0')
		str[j++] = stack[i++];
	str[j] = '\0';
	free(stack);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stack;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!stack)
	{
		stack = (char *)malloc(sizeof(char *));
		stack[0] = '\0';
	}
	stack = ft_read_text(fd, stack);
	if (!stack)
		return (NULL);
	line = ft_get_line(stack);
	stack = ft_remove_characters(stack);
	if (!line || ft_strlen(line) == 0)
		return (NULL);
	return (line);
}

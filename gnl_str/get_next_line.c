/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:43:07 by gkamanur          #+#    #+#             */
/*   Updated: 2024/12/12 16:48:56 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *rem_str)
{
	int		i;
	char	*str;

	i = 0;
	if (!rem_str || !rem_str[i])
		return (NULL);
	while (rem_str[i] && rem_str[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (rem_str[i] && rem_str[i] != '\n')
	{
		str[i] = rem_str[i];
		i++;
	}
	if (rem_str[i] == '\n')
	{
		str[i] = rem_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_left_str(char *rem_str)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (rem_str[i] && rem_str[i] != '\n')
		i++;
	if (!rem_str[i])
	{
		free(rem_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(rem_str) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (rem_str[i])
		str[j++] = rem_str[i++];
	str[j] = '\0';
	free(rem_str);
	return (str);
}

char	*ft_read_to_left_str(int fd, char *rem_str)
{
	char	*buff;
	int		read_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (free_rem(rem_str));
	read_bytes = 1;
	while (!ft_strchr(rem_str, '\n') && (read_bytes > 0))
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (free_rem(rem_str));
		}
		buff[read_bytes] = '\0';
		rem_str = ft_strjoin(rem_str, buff, -1, 0);
		if (!rem_str)
		{
			free(buff);
			return (NULL);
		}
	}
	free(buff);
	return (rem_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rem_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rem_str = ft_read_to_left_str(fd, rem_str);
	if (!rem_str)
		return (NULL);
	if (rem_str[0] == '\0')
	{
		free(rem_str);
		rem_str = NULL;
		return (NULL);
	}
	line = ft_get_line(rem_str);
	rem_str = ft_new_left_str(rem_str);
	if (!line && rem_str)
	{
		free(rem_str);
		rem_str = NULL;
	}
	return (line);
}

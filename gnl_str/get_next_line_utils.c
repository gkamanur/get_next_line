/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:43:38 by gkamanur          #+#    #+#             */
/*   Updated: 2024/12/12 16:27:14 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_rem(char *rem_str)
{
	free(rem_str);
	return (NULL);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *rem_str, char *buff, size_t i, size_t j)
{
	char	*str;

	if (!rem_str)
	{
		rem_str = (char *)malloc(1 * sizeof(char));
		rem_str[0] = '\0';
	}
	if (!rem_str || !buff)
		return (free_rem(rem_str));
	str = malloc(sizeof(char) * ((ft_strlen(rem_str) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (free_rem(rem_str));
	if (rem_str)
		while (rem_str[++i] != '\0')
			str[i] = rem_str[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(rem_str) + ft_strlen(buff)] = '\0';
	free(rem_str);
	return (str);
}

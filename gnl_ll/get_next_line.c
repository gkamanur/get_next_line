/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:27:25 by gkamanur          #+#    #+#             */
/*   Updated: 2024/12/05 17:13:32 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	prep_list(t_list **head, int i, int j)
{
	t_list	*end_node;
	t_list	*clean_list;
	char	*buf;

	end_node = last_node(*head);
	if (!end_node || !end_node->content)
		return ;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	clean_list = malloc(sizeof(t_list));
	if (!buf || !clean_list)
	{
		free(buf);
		free(clean_list);
		return ;
	}
	while (end_node->content[i] && end_node->content[i] != '\n')
		++i;
	if (end_node->content[i] == '\n')
		++i;
	while (end_node->content[i])
		buf[j++] = end_node->content[i++];
	buf[j] = '\0';
	clean_list->content = buf;
	clean_list->next = NULL;
	dealloc(head, clean_list, buf);
}

static void	make_list(t_list **head, int fd)
{
	char	*buf;
	int		char_read;

	while (!new_line(*head))
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read <= 0)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append_list(head, buf);
	}
}

static char	*make_str(t_list *head, int i, int j, int len)
{
	char	*str;

	if (!head)
		return (NULL);
	len = len_newline(head);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (head)
	{
		i = 0;
		while (head->content[i])
		{
			if (head->content[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return (str);
			}
			str[j++] = head->content[i++];
		}
		head = head->next;
	}
	str[j] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	static t_list	*head = NULL;
	char			*newstr;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		if (head)
			dealloc(&head, NULL, NULL);
		return (NULL);
	}
	make_list(&head, fd);
	if (!head)
		return (NULL);
	newstr = make_str(head, 0, 0, 0);
	prep_list(&head, 0, 0);
	return (newstr);
}

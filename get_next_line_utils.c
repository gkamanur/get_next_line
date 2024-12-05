/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:27:36 by gkamanur          #+#    #+#             */
/*   Updated: 2024/12/05 17:12:07 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	append_list(t_list **head, char *str)
{
	t_list	*new_list;
	t_list	*curr;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (!new_list)
	{
		free(str);
		return ;
	}
	new_list->next = NULL;
	new_list->content = str;
	if (*head == NULL)
	{
		*head = new_list;
		return ;
	}
	curr = *head;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_list;
}

t_list	*last_node(t_list *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

int	new_line(t_list *head)
{
	int	i;

	while (head)
	{
		i = 0;
		while (head->content[i] && (i < BUFFER_SIZE))
		{
			if (head->content[i] == '\n')
				return (1);
			++i;
		}
		head = head->next;
	}
	return (0);
}

void	dealloc(t_list **head, t_list *clean_node, char *buf)
{
	t_list	*temp;
	t_list	*next;

	if (!head || !*head)
		return ;
	temp = *head;
	while (temp)
	{
		next = temp->next;
		free(temp->content);
		free(temp);
		temp = next;
	}
	*head = NULL;
	if (clean_node && clean_node->content && clean_node->content[0])
		*head = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}

int	len_newline(t_list *head)
{
	int	len;
	int	i;

	len = 0;
	if (!head)
		return (0);
	while (head)
	{
		i = 0;
		while (head->content[i])
		{
			if (head->content[i] == '\n')
				return (len + 1);
			++len;
			++i;
		}
		head = head->next;
	}
	return (len);
}

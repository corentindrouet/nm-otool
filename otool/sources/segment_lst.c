/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 11:07:21 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/20 14:15:07 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

t_segment_list	*create_segment(void *seg)
{
	t_segment_list	*elem;

	elem = (t_segment_list*)malloc(sizeof(t_segment_list));
	elem->index = 1;
	elem->segment.seg = seg;
	elem->first_section = NULL;
	elem->next = NULL;
	return (elem);
}

void			add_segment(t_segment_list **lst, t_segment_list *elem)
{
	t_segment_list	*tmp;

	tmp = *lst;
	if (!(*lst))
	{
		*lst = elem;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	elem->index = tmp->index + 1;
	tmp->next = elem;
}

t_segment_list	*search_segment_by_index(t_segment_list *lst, int index)
{
	if (!lst)
		return (NULL);
	while (lst)
		if (lst->index == index)
			break ;
		else
			lst = lst->next;
	return (lst);
}

void			delete_segment_lst(t_segment_list *lst)
{
	if (!lst)
		return ;
	if (lst->next)
		delete_segment_lst(lst->next);
	free(lst);
}

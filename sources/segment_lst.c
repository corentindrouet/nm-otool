/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 11:07:21 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/06 14:08:13 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <stdio.h>

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

void			print_segments(t_segment_list *lst)
{
	uint32_t	i;
	t_section_list	*tmp;

	while (lst)
	{
		printf("cmd %d index %d\n", lst->segment.seg_64->cmd, lst->index);
		printf("segname %s\n", lst->segment.seg_64->segname);
		i = 0;
		tmp = lst->first_section;
		while (i < lst->segment.seg_64->nsects)
		{
			printf("  %d sectname %s\n", tmp->index, tmp->section.sect_64->sectname);
			printf("  type %x\n", (tmp->section.sect_64->flags & SECTION_TYPE));
			tmp = tmp->next;
			i++;
		}
		printf("\n");
		lst = lst->next;
	}
}

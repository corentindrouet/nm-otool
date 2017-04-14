/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectment_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 11:18:12 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/06 14:50:54 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_section_list	*create_section(void *sect)
{
	t_section_list	*elem;

	elem = (t_section_list*)malloc(sizeof(t_section_list));
	elem->index = 1;
	elem->section.sect = sect;
	elem->next = NULL;
	return (elem);
}

void			add_section(t_section_list **lst, t_section_list *elem)
{
	t_section_list	*tmp;

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

t_section_list	*search_section_by_index(t_section_list *lst, int index)
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

void			delete_section_lst(t_section_list *lst)
{
	if (!lst)
		return ;
	if (lst->next)
		delete_section_lst(lst->next);
	free(lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtable_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 14:48:44 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/21 09:38:08 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_symtable		*create_symtable(void *sym, char *name)
{
	t_symtable	*elem;

	elem = (t_symtable*)malloc(sizeof(t_symtable));
	elem->symtable.symtable_64 = sym;
	elem->name = name;
	elem->next = NULL;
	return (elem);
}

void			add_symtable(t_symtable **lst, t_symtable *elem)
{
	t_symtable	*tmp;

	if (!(*lst))
	{
		*lst = elem;
		return ;
	}
	if (ft_strcmp(elem->name, (*lst)->name) < 0)
	{
		elem->next = (*lst);
		*lst = elem;
		return ;
	}
	tmp = *lst;
	while (tmp->next && ft_strcmp(tmp->next->name, elem->name) < 0)
		tmp = tmp->next;
	if (tmp->next)
		elem->next = tmp->next;
	tmp->next = elem;
}

int				is_sorted(t_symtable *lst)
{
	if (!lst)
		return (1);
	while (lst->next)
	{
		if (ft_strcmp(lst->name, lst->next->name) > 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}

void			delete_symtable(t_symtable *lst)
{
	if (!lst)
		return ;
	if (lst->next)
		delete_symtable(lst->next);
	free(lst);
}

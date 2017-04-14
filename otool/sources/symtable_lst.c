/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtable_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 14:48:44 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/14 14:09:15 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

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
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = elem;
}

int				is_sorted(t_symtable *lst)
{
	if (!lst)
		return (1);
	while (lst->next)
	{
		if (strcmp(lst->name, lst->next->name) > 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}

void			sort_symtable(t_symtable *lst)
{
	char		*tmp_name;
	void		*tmp_sym;
	t_symtable	*tmp;

	if (!lst)
		return ;
	while (!is_sorted(lst))
	{
		tmp = lst;
		while (tmp->next)
		{
			if (strcmp(tmp->name, tmp->next->name) > 0)
			{
				tmp_name = tmp->next->name;
				tmp->next->name = tmp->name;
				tmp->name = tmp_name;
				tmp_sym = tmp->next->symtable.symtable_64;
				tmp->next->symtable.symtable_64 = tmp->symtable.symtable_64;
				tmp->symtable.symtable_64 = tmp_sym;
			}
			tmp = tmp->next;
		}
	}
}

void			delete_symtable(t_symtable *lst)
{
	if (!lst)
		return ;
	if (lst->next)
		delete_symtable(lst->next);
	free(lst);
}

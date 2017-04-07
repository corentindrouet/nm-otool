/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 08:52:25 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/07 13:01:22 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H
# include "libft.h"
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>

union			u_section
{
	struct section		*sect;
	struct section_64	*sect_64;
};

union			u_segment
{
	struct segment_command		*seg;
	struct segment_command_64	*seg_64;
};

union			u_header
{
	struct mach_header		*header;
	struct mach_header_64	*header_64;
};

union			u_symtable
{
	struct nlist	*symtable;
	struct nlist_64	*symtable_64;
};

typedef struct	s_segment_list
{
	int						index;
	union u_segment			segment;
	void					*first_section;
	struct s_segment_list	*next;
}				t_segment_list;

typedef struct	s_section_list
{
	int						index;
	union u_section			section;
	struct s_section_list	*next;
}				t_section_list;

typedef struct	s_symtable
{
	union u_symtable	symtable;
	char				*name;
	struct s_symtable	*next;
}				t_symtable;

typedef struct	s_file_structs
{
	union u_header			headers;
	struct s_segment_list	*segments;
	struct s_section_list	*sections;
	struct symtab_command	*sym;
	char					*file;
	int						swap;
}				t_file_structs;

int				error_exit(char *msg, char *name, int exit_type);
void			nm_file(t_file_structs *file);
void			handle_64_bits_files(t_file_structs *file);
void			handle_32_bits_files(t_file_structs *file);
t_segment_list	*create_segment(void *seg);
void			add_segment(t_segment_list **lst, t_segment_list *elem);
t_segment_list	*search_segment_by_index(t_segment_list *lst, int index);
void			delete_segment_lst(t_segment_list *lst);
t_section_list	*create_section(void *sect);
void			add_section(t_section_list **lst, t_section_list *elem);
t_section_list	*search_section_by_index(t_section_list *lst, int index);
void			delete_section_lst(t_section_list *lst);
void			print_segments(t_segment_list *lst);
void			sort_symtable(t_symtable *lst);
t_symtable		*create_symtable(void *sym, char *name);
void			add_symtable(t_symtable **lst, t_symtable *elem);
void			sort_symtable(t_symtable *lst);
void			delete_symtable(t_symtable *lst);
uint64_t		swap_byte(uint64_t a, int size, int need_swap);

#endif

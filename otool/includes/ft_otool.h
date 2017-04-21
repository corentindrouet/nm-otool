/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 08:52:25 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/21 09:41:00 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H
# include "libft.h"
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include <mach-o/ranlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# define SWAP(x, y) swap_byte(x, sizeof(x), y)

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
};;

typedef struct	s_arch_header
{
	char		name[16];
	char		last_modification[12];
	char		user_id[6];
	char		group_id[6];
	char		mode[8];
	char		size[10];
	uint16_t	ending;
}				t_arch_header;

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

typedef struct	s_file_structs
{
	union u_header			headers;
	struct s_segment_list	*segments;
	struct s_section_list	*sections;
	char					*file;
	struct stat				*file_info;
	int						swap;
	char					*file_name;
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
uint64_t		swap_byte(uint64_t a, int size, int need_swap);
void			handle_archives(t_file_structs *file);
void			init_file_struct(t_file_structs *file, char *filename);
void			handle_fat_file(t_file_structs *file);
int				host_arch(void);

#endif

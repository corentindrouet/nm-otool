/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 08:52:06 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/20 14:26:41 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			host_arch(void)
{
	return ((sizeof(void*) == 8) ? 64 : 32);
}

int			error_exit(char *msg, char *name, int exit_type)
{
	ft_putstr_fd(msg, 2);
	if (name)
		ft_putendl_fd(name, 2);
	else
		ft_putendl_fd("", 2);
	return (exit_type);
}

void		init_file_struct(t_file_structs *file, char *filename)
{
	file->headers.header = NULL;
	file->headers.header_64 = NULL;
	file->segments = NULL;
	file->sections = NULL;
	file->sym = NULL;
	file->file = NULL;
	file->file_info = malloc(sizeof(struct stat));
	file->swap = 0;
	file->file_name = filename;
}

int			exec_for_file(char *name, t_file_structs *file)
{
	int	fd;

	init_file_struct(file, name);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (error_exit("Permission denied. ", name, EXIT_FAILURE));
	else if (fd == -1)
		return (EXIT_FAILURE);
	if (fstat(fd, file->file_info) < 0)
		return (EXIT_FAILURE);
	if ((file->file = mmap(0, file->file_info->st_size,
					PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (EXIT_FAILURE);
	nm_file(file);
	free(file->file_info);
	if (munmap(file->file, file->file_info->st_size) == -1)
		return (EXIT_FAILURE);
	close(fd);
	return (EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
	int				i;
	t_file_structs	file;

	if (ac <= 1)
		return (exec_for_file("./a.out", &file));
	i = 1;
	while (i < ac)
	{
		if (ac > 2)
			ft_printf("\n%s:\n", av[i]);
		if (exec_for_file(av[i], &file) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

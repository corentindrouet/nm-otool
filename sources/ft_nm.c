/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 08:52:06 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/13 14:32:21 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			host_arch(void)
{
	return ((sizeof(void*) == 8) ? 64 : 32);
}

int			error_exit(char *msg, char *name, int exit_type)
{
	ft_putstr(msg);
	if (name)
		ft_putendl(name);
	else
		ft_putendl("");
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

int			main(int ac, char **av)
{
	int				i;
	int				fd;
	t_file_structs	file;

	if (ac <= 1)
		return (error_exit("Need one or more aguments", NULL, EXIT_FAILURE));
	i = 1;
	while (i < ac)
	{
		init_file_struct(&file, av[i]);
		fd = open(av[i], O_RDONLY);
		if (fd == -1)
			return (error_exit("Can't open file ", av[i], EXIT_FAILURE));
		if (fstat(fd, file.file_info) < 0)
			return (error_exit("fstat error", NULL, EXIT_FAILURE));
		if ((file.file = mmap(0, file.file_info->st_size,
						PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return (error_exit("mmap error", NULL, EXIT_FAILURE));
		if (ac > 2)
			ft_printf("\n%s:\n", av[i]);
		nm_file(&file);
		free(file.file_info);
		if (munmap(file.file, file.file_info->st_size) == -1)
			return (error_exit("munmap error", NULL, EXIT_FAILURE));
		close(fd);
		i++;
	}
	return (EXIT_SUCCESS);
}

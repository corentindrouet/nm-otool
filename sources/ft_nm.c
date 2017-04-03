/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 08:52:06 by cdrouet           #+#    #+#             */
/*   Updated: 2017/03/31 09:26:18 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int		error_exit(char *msg, char *name, int exit_type)
{
	ft_putstr(msg);
	if (name)
		ft_putendl(name);
	else
		ft_putendl("");
	return (exit_type);
}

int		main(int ac, char **av)
{
	int			i;
	int			fd;
	struct stat	buf;
	char		*ptr;

	if (ac <= 1)
		return (error_exit("Need one or more aguments", NULL, EXIT_FAILURE));
	i = 1;
	while (i < ac)
	{
		fd = open(av[i], O_RDONLY);
		if (fd == -1)
			return (error_exit("Can't open file ", av[i], EXIT_FAILURE));
		if (fstat(fd, &buf) < 0)
			return (error_exit("fstat error", NULL, EXIT_FAILURE));
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return (error_exit("mmap error", NULL, EXIT_FAILURE));
		nm_file(ptr);
		if (munmap(ptr, buf.st_size) == -1)
			return (error_exit("munmap error", NULL, EXIT_FAILURE));
		close(fd);
		i++;
	}
	return (EXIT_SUCCESS);
}

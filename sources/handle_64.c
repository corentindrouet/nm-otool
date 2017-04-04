/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 09:41:37 by cdrouet           #+#    #+#             */
/*   Updated: 2017/04/04 14:10:23 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <stdio.h>

void	print_output(char *ptr, struct symtab_command *sym)
{
	uint32_t		i;
	char 			*str_table;
	struct nlist_64	*sym_table;

	i = 0;
	str_table = (void*)ptr + sym->stroff;
	sym_table = (void*)ptr + sym->symoff;
	while (i < sym->nsyms)
	{
		printf("%s %d\n", str_table + sym_table[i].n_un.n_strx,
				(uint8_t)(str_table + sym_table[i].n_sect));
		i++;
	}
}

void	print_seg_name(void *segment, char *ptr)
{
	struct segment_command_64	*seg;
	(void)ptr;
	struct section_64			*sec;
	uint32_t					i;

	seg = segment;
	printf("  cmd %d\n", seg->cmd);
	printf("  cmdsize %d\n", seg->cmdsize);
	printf("  segname %s\n", seg->segname);
	printf("  nsects %d\n", seg->nsects);
	i = 0;
	sec = (void*)seg + sizeof(struct segment_command_64);
	while (i < seg->nsects)
	{
		printf("    addr %llx\n", sec->addr);
		printf("    offset %d\n", sec->offset);
		printf("    size %llu\n", sec->size);
		i++;
		sec = (void*)sec + sizeof(struct section_64);
	}
	printf("  flags %d\n", seg->flags);
	printf("\n");
}

void	print_main(void *cmd, char *ptr)
{
	struct entry_point_command	*main_cmd;

	(void)ptr;
	main_cmd = cmd;
	printf("    cmd %d\n", main_cmd->cmd);
	printf("    cmdsize %d\n", main_cmd->cmd);
	printf("    entryoff %llu\n", main_cmd->entryoff);
	printf("    stacksize %llu\n", main_cmd->stacksize);
}

void	print_data(void *cmd, char *ptr)
{
	struct data_in_code_entry	*data;

	(void)ptr;
	data = cmd;
	printf("    offset %d\n", data->offset);
	printf("    length %d\n", data->length);
	printf("    kind %d\n", data->kind);
	write(1, ptr + data->offset, data->length);
}

void	handle_64_bits_files(char *ptr)
{
	struct mach_header_64		*header;
	struct load_command			*cmd;
	struct symtab_command		*sym;
	union lc_str				*essai;
	uint32_t					i;

	header = (struct mach_header_64*)ptr;
	cmd = (void*)ptr + sizeof(*header);
	i = 0;
	printf("%d\n", header->ncmds);
	while (i < header->ncmds)
	{
		essai = (void*)cmd;
		if (cmd->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command*)cmd;
			print_output(ptr, sym);
		}
		else if (cmd->cmd == LC_SEGMENT_64)
			print_seg_name(cmd, ptr);
		else if (cmd->cmd == LC_MAIN)
			print_main(cmd, ptr);
		else if (cmd->cmd == LC_DATA_IN_CODE)
			print_data(cmd, ptr);
		else
			printf("%d\n", cmd->cmd);
		cmd = (void*) cmd + cmd->cmdsize;
		i++;
	}
}

/*
** EPITECH PROJECT, 2020
** nm
** File description:
** nm_32.c
*/

#include "nm_32.h"

#include <stdio.h>

#include "../common/def.h"
#include "elf_32.h"
#include "symbol_table_32.h"

int nm_32(const char *path, Elf32_Ehdr *elf_header)
{
    if (elf_32_get_section_header_by_name(elf_header, ".symtab") == NULL) {
        fprintf(stderr, "nm: %s: no symbols\n", path);

        return (FAILURE);
    }

    int *indexes = NULL;
    unsigned long size;

    symbol_table_32_get_indexes(elf_header, &indexes, &size);
    symbol_table_32_sort_indexes_alphabetically(elf_header, indexes, size);
    symbol_table_32_print(elf_header, indexes, size);

    return (SUCCESS);
}
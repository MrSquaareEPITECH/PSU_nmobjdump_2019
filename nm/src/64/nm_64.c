/*
** EPITECH PROJECT, 2020
** nm
** File description:
** nm_64.c
*/

#include "nm_64.h"

#include <stdio.h>

#include "../common/def.h"
#include "elf_64.h"
#include "symbol_table_64.h"

int nm_64(const char *path, Elf64_Ehdr *elf_header)
{
    if (elf_64_get_section_header_by_name(elf_header, ".symtab") == NULL) {
        fprintf(stderr, "nm: %s: no symbols\n", path);

        return (FAILURE);
    }

    int *indexes = NULL;
    unsigned long size;

    symbol_table_64_get_indexes(elf_header, &indexes, &size);
    symbol_table_64_sort_indexes_alphabetically(elf_header, indexes, size);
    symbol_table_64_print(elf_header, indexes, size);

    return (SUCCESS);
}
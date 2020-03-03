/*
** EPITECH PROJECT, 2020
** nm
** File description:
** nm_64.c
*/

#include "nm_64.h"

#include <stddef.h>

#include "symbol_table_64.h"

int nm_64(Elf64_Ehdr *elf_header)
{
    int *indexes = NULL;
    unsigned long size;

    symbol_table_64_get_indexes(elf_header, &indexes, &size);
    symbol_table_64_sort_indexes_alphabetically(elf_header, indexes, size);
    symbol_table_64_print(elf_header, indexes, size);

    return (0);
}
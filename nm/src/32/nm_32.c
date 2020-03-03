/*
** EPITECH PROJECT, 2020
** nm
** File description:
** nm_32.c
*/

#include "nm_32.h"

#include <stddef.h>

#include "symbol_table_32.h"

int nm_32(Elf32_Ehdr *elf_header)
{
    int *indexes = NULL;
    unsigned long size;

    symbol_table_32_get_indexes(elf_header, &indexes, &size);
    symbol_table_32_sort_indexes_alphabetically(elf_header, indexes, size);
    symbol_table_32_print(elf_header, indexes, size);

    return (0);
}
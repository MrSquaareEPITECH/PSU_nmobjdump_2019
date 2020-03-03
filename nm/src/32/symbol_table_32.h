/*
** EPITECH PROJECT, 2020
** nm
** File description:
** symbol_table_32.h
*/

#ifndef NM_SYMBOL_TABLE_32_H
#define NM_SYMBOL_TABLE_32_H

#include <elf.h>

void symbol_table_32_get_indexes(
    const Elf32_Ehdr *elf_hdr, int **indexes, unsigned long *size);
void symbol_table_32_sort_indexes_alphabetically(
    const Elf32_Ehdr *elf_hdr, int *indexes, unsigned long size);
void symbol_table_32_print(
    const Elf32_Ehdr *elf_hdr, const int *indexes, unsigned long size);

#endif  // NM_SYMBOL_TABLE_32_H

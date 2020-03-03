/*
** EPITECH PROJECT, 2020
** nm
** File description:
** symbol_table_64.h
*/

#ifndef NM_SYMBOL_TABLE_64_H
#define NM_SYMBOL_TABLE_64_H

#include <elf.h>

void symbol_table_64_get_indexes(
    const Elf64_Ehdr *elf_hdr, int **indexes, unsigned long *size);
void symbol_table_64_sort_indexes_alphabetically(
    const Elf64_Ehdr *elf_hdr, int *indexes, unsigned long size);
void symbol_table_64_print(
    const Elf64_Ehdr *elf_hdr, const int *indexes, unsigned long size);

#endif  // NM_SYMBOL_TABLE_64_H

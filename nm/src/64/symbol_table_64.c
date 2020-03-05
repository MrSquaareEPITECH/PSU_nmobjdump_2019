/*
** EPITECH PROJECT, 2020
** nm
** File description:
** symbol_table_64.c
*/

#include "symbol_table_64.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/def.h"
#include "elf_64.h"
#include "symbol_64.h"

static int strcasecmp_alpha(const char *s1, const char *s2)
{
    unsigned long len1 = strlen(s1), len2 = strlen(s2);
    unsigned long i = 0, j = 0;

    for (; (i < len1) && (j < len2); ++i, ++j) {
        while (!isalnum(s1[i]) && (i < len1))
            i++;
        while (!isalnum(s2[j]) && (j < len2))
            j++;

        int c1 = tolower(s1[i]);
        int c2 = tolower(s2[j]);

        if (c1 != c2)
            return (c1 - c2);
    }

    return (s1[i] - s2[j]);
}

static void swap_indexes(int *indexes, unsigned long i, unsigned long j)
{
    int indexes_i = indexes[i];

    indexes[i] = indexes[j];
    indexes[j] = indexes_i;
}

void symbol_table_64_get_indexes(
    const Elf64_Ehdr *elf_hdr, int **indexes, unsigned long *size)
{
    Elf64_Shdr *sym_hdr = elf_64_get_section_header_by_name(elf_hdr, ".symtab");

    *size = sym_hdr->sh_size / sym_hdr->sh_entsize;
    *indexes = malloc(sizeof(int) * (*size));

    for (unsigned long i = 0; i < *size; ++i)
        (*indexes)[i] = (int)(i);
}

void symbol_table_64_sort_indexes_alphabetically(
    const Elf64_Ehdr *elf_hdr, int *indexes, unsigned long size)
{
    Elf64_Shdr *sym_hdr = elf_64_get_section_header_by_name(elf_hdr, ".symtab");
    Elf64_Shdr *str_hdr = elf_64_get_section_header_by_name(elf_hdr, ".strtab");
    Elf64_Sym *sym_table = PTR_CREMENT(elf_hdr, sym_hdr->sh_offset);
    char *str_table = PTR_CREMENT(elf_hdr, str_hdr->sh_offset);

    for (unsigned long i = 1; i < size; ++i) {
        for (unsigned long j = 1; j < size; ++j) {
            const Elf64_Sym *sym1 = &sym_table[indexes[j - 1]];
            const Elf64_Sym *sym2 = &sym_table[indexes[j]];
            const char *str1 = &str_table[sym1->st_name];
            const char *str2 = &str_table[sym2->st_name];
            int compare = strcasecmp_alpha(str1, str2);

            if (compare == 0)
                compare = strcasecmp(str1, str2);

            if (compare > 0)
                swap_indexes(indexes, j - 1, j);
        }
    }
}

void symbol_table_64_print(
    const Elf64_Ehdr *elf_hdr, const int *indexes, unsigned long size)
{
    Elf64_Shdr *sym_hdr = elf_64_get_section_header_by_name(elf_hdr, ".symtab");
    Elf64_Shdr *str_hdr = elf_64_get_section_header_by_name(elf_hdr, ".strtab");
    Elf64_Sym *sym_table = PTR_CREMENT(elf_hdr, sym_hdr->sh_offset);
    char *str_table = PTR_CREMENT(elf_hdr, str_hdr->sh_offset);

    for (unsigned long i = 0; i < size; ++i) {
        const Elf64_Sym *sym = &sym_table[indexes[i]];

        if ((sym->st_name == 0) || (sym->st_info == STT_FILE))
            continue;

        char type = symbol_64_get_type(sym, elf_hdr);
        const char *str = &str_table[sym->st_name];

        if (sym->st_value)
            printf("%.16lx %c %s\n", sym->st_value, type, str);
        else
            printf("%16c %c %s\n", ' ', type, str);
    }
}
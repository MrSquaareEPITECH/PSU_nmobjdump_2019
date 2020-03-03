/*
** EPITECH PROJECT, 2020
** nm
** File description:
** elf_32.c
*/

#include "elf_32.h"

#include <string.h>

#include "../common/def.h"
#include "section_32.h"

Elf32_Shdr *elf_32_get_section_header_by_name(
    const Elf32_Ehdr *elf_hdr, const char *name)
{
    Elf32_Shdr *sec_hdr_table = PTR_CREMENT(elf_hdr, elf_hdr->e_shoff);
    Elf32_Shdr *sec_hdr = NULL;
    char *sec_str = NULL;

    for (int i = 0; i < elf_hdr->e_shnum; ++i) {
        sec_hdr = &sec_hdr_table[i];
        sec_str = section_32_get_name(sec_hdr, elf_hdr);

        if (strcmp(sec_str, name) == 0) return (sec_hdr);
    }

    return (NULL);
}

Elf32_Shdr *elf_32_get_section_header_by_type(
    const Elf32_Ehdr *elf_hdr, Elf32_Word type)
{
    Elf32_Shdr *sec_hdr_table = PTR_CREMENT(elf_hdr, elf_hdr->e_shoff);
    Elf32_Shdr *sec_hdr = NULL;

    for (int i = 0; i < elf_hdr->e_shnum; ++i) {
        sec_hdr = &sec_hdr_table[i];

        if (sec_hdr->sh_type == type) return (sec_hdr);
    }

    return (NULL);
}

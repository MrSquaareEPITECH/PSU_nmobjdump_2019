/*
** EPITECH PROJECT, 2020
** nm
** File description:
** elf_64.c
*/

#include "elf_64.h"

#include <string.h>

#include "../common/def.h"
#include "section_64.h"

Elf64_Shdr *elf_64_get_section_header_by_name(
    const Elf64_Ehdr *elf_hdr, const char *name)
{
    Elf64_Shdr *sec_hdr_table = PTR_CREMENT(elf_hdr, elf_hdr->e_shoff);
    Elf64_Shdr *sec_hdr = NULL;
    char *sec_str = NULL;

    for (int i = 0; i < elf_hdr->e_shnum; ++i) {
        sec_hdr = &sec_hdr_table[i];
        sec_str = section_64_get_name(sec_hdr, elf_hdr);

        if (strcmp(sec_str, name) == 0) return (sec_hdr);
    }

    return (NULL);
}

Elf64_Shdr *elf_64_get_section_header_by_type(
    const Elf64_Ehdr *elf_hdr, Elf64_Word type)
{
    Elf64_Shdr *sec_hdr_table = PTR_CREMENT(elf_hdr, elf_hdr->e_shoff);
    Elf64_Shdr *sec_hdr = NULL;

    for (int i = 0; i < elf_hdr->e_shnum; ++i) {
        sec_hdr = &sec_hdr_table[i];

        if (sec_hdr->sh_type == type) return (sec_hdr);
    }

    return (NULL);
}

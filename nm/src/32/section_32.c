/*
** EPITECH PROJECT, 2020
** nm
** File description:
** section_32.c
*/

#include "section_32.h"

#include "../common/def.h"

char *section_32_get_name(const Elf32_Shdr *sec_hdr, const Elf32_Ehdr *elf_hdr)
{
    Elf32_Shdr *sec_hdr_table = PTR_CREMENT(elf_hdr, elf_hdr->e_shoff);
    Elf32_Shdr *shstr_hdr = &sec_hdr_table[elf_hdr->e_shstrndx];
    char *shstr_table = PTR_CREMENT(elf_hdr, shstr_hdr->sh_offset);
    char *name = &shstr_table[sec_hdr->sh_name];

    return (name);
}

/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** objdump_32.c
*/

#include "objdump_32.h"

#include <string.h>

#include "../common/def.h"
#include "elf_32.h"
#include "section_32.h"

int objdump_32(const char *path, const Elf32_Ehdr *elf_hdr)
{
    Elf32_Shdr *sec_hdr_table = PTR_CREMENT(elf_hdr, elf_hdr->e_shoff);

    elf_32_print(elf_hdr, path);

    for (int i = 0; i < elf_hdr->e_shnum; ++i) {
        Elf32_Shdr *sec_hdr = &sec_hdr_table[i];

        if (sec_hdr->sh_name == 0) continue;

        char *sec_str = section_32_get_name(sec_hdr, elf_hdr);

        if (strcmp(sec_str, ".bss") == 0) continue;
        if (strcmp(sec_str, ".shstrtab") == 0) continue;
        if (strcmp(sec_str, ".strtab") == 0) continue;
        if (strcmp(sec_str, ".symtab") == 0) continue;

        section_32_print(sec_hdr, elf_hdr);
    }

    return (SUCCESS);
}
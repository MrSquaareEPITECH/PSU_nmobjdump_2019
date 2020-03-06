/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** objdump_32.c
*/

#include "objdump_32.h"

#include <string.h>

#include "../common/def.h"
#include "../common/struct.h"
#include "elf_32.h"
#include "section_32.h"

static void objdump_32_section_print(
    const Elf32_Ehdr *elf_hdr, const Elf32_Shdr *sec_hdr)
{
    if (sec_hdr->sh_name == 0)
        return;

    char *sec_str = section_32_get_name(sec_hdr, elf_hdr);

    for (int j = 0; ELF_SEC_NAME_SKIP[j]; ++j)
        if (strcmp(sec_str, ELF_SEC_NAME_SKIP[j]) == 0)
            return;

    section_32_print(sec_hdr, elf_hdr);
}

int objdump_32(const char *path, const Elf32_Ehdr *elf_hdr)
{
    Elf32_Shdr *sec_hdr_table = PTR_CREMENT(elf_hdr, elf_hdr->e_shoff);

    elf_32_print(elf_hdr, path);

    for (int i = 0; i < elf_hdr->e_shnum; ++i) {
        Elf32_Shdr *sec_hdr = &sec_hdr_table[i];

        objdump_32_section_print(elf_hdr, sec_hdr);
    }

    return (SUCCESS);
}
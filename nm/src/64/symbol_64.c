/*
** EPITECH PROJECT, 2020
** nm
** File description:
** symbol_64.c
*/

#include "symbol_64.h"

#include <ctype.h>
#include <string.h>

#include "../common/def.h"
#include "../common/struct.h"
#include "section_64.h"

static char symbol_64_get_weak(const Elf64_Sym *sym)
{
    int st_bind = ELF64_ST_BIND(sym->st_info);
    int st_type = ELF64_ST_TYPE(sym->st_info);

    if (st_bind == STB_WEAK) {
        char letter = SYM_TYPE_WEAK;

        if (st_type == STT_OBJECT)
            letter = SYM_TYPE_WEAK_OBJECT;

        if (sym->st_value == 0)
            letter = tolower(letter);

        return (letter);
    }

    return (SYM_TYPE_UNKNOWN);
}

static char symbol_64_get_shndx(const Elf64_Sym *sym)
{
    for (int i = 0; SYM_SHNDX_TYPES[i].type; ++i)
        if (sym->st_shndx == SYM_SHNDX_TYPES[i].shndx)
            return (SYM_SHNDX_TYPES[i].type);

    return (SYM_TYPE_UNKNOWN);
}

static char symbol_64_get_sec_name(
    const Elf64_Sym *sym, const Elf64_Ehdr *elf_header)
{
    Elf64_Shdr *sec_hdr_table = PTR_CREMENT(elf_header, elf_header->e_shoff);
    Elf64_Shdr *sec_hdr = &sec_hdr_table[sym->st_shndx];

    if (sec_hdr->sh_name == 0)
        return (SYM_TYPE_UNKNOWN);

    char *sec_str = section_64_get_name(sec_hdr, elf_header);

    for (int i = 0; SYM_SEC_NAME_TYPES[i].type; ++i)
        if (strcmp(sec_str, SYM_SEC_NAME_TYPES[i].name) == 0)
            return (SYM_SEC_NAME_TYPES[i].type);

    return (SYM_TYPE_UNKNOWN);
}

static char symbol_64_get_sec_flags(
    const Elf64_Sym *sym, const Elf64_Ehdr *elf_header)
{
    Elf64_Shdr *sec_hdr_table = PTR_CREMENT(elf_header, elf_header->e_shoff);
    Elf64_Shdr *sec_hdr = &sec_hdr_table[sym->st_shndx];

    for (int i = 0; SYM_SEC_FLAGS_TYPES[i].type; ++i)
        if (sec_hdr->sh_flags & SYM_SEC_FLAGS_TYPES[i].flags)
            return (SYM_SEC_FLAGS_TYPES[i].type);

    return (SYM_TYPE_UNKNOWN);
}

char symbol_64_get_type(const Elf64_Sym *sym, const Elf64_Ehdr *elf_header)
{
    char type = symbol_64_get_weak(sym);

    if (type == SYM_TYPE_UNKNOWN)
        type = symbol_64_get_shndx(sym);

    if (type == SYM_TYPE_UNKNOWN)
        type = symbol_64_get_sec_name(sym, elf_header);

    if (type == SYM_TYPE_UNKNOWN)
        type = symbol_64_get_sec_flags(sym, elf_header);

    if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL)
        type = tolower(type);

    return (type);
}
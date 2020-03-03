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
#include "section_64.h"

static char symbol_64_get_letter(
    const Elf64_Sym *sym, const Elf64_Ehdr *elf_header)
{
    int st_bind = ELF64_ST_BIND(sym->st_info);
    int st_type = ELF64_ST_TYPE(sym->st_info);

    if (st_bind == STB_WEAK) {
        if (st_type == STT_OBJECT) return ((sym->st_value) ? 'V' : 'v');
        return ((sym->st_value) ? 'W' : 'w');
    }

    Elf64_Shdr *sec_hdr_table = PTR_CREMENT(elf_header, elf_header->e_shoff);
    Elf64_Shdr *sec_hdr = &sec_hdr_table[sym->st_shndx];
    char *sec_str = section_64_get_name(sec_hdr, elf_header);

    if (strcmp(sec_str, ".bss") == 0) return ('B');
    if (strcmp(sec_str, ".data") == 0) return ('D');
    if (strcmp(sec_str, ".data1") == 0) return ('D');
    if (strcmp(sec_str, ".debug") == 0) return ('N');
    if (strcmp(sec_str, ".rodata") == 0) return ('R');
    if (strcmp(sec_str, ".rodata1") == 0) return ('R');
    if (strcmp(sec_str, ".text") == 0) return ('T');

    if (sec_hdr->sh_flags == SHF_ALLOC + SHF_WRITE) return ('D');
    if (sec_hdr->sh_flags == SHF_ALLOC) return ('R');
    if (sec_hdr->sh_flags == SHF_ALLOC + SHF_EXECINSTR) return ('T');

    if (sym->st_shndx == SHN_ABS) return ('A');
    if (sym->st_shndx == SHN_COMMON) return ('C');
    if (sym->st_shndx == SHN_UNDEF) return ('U');

    return ('?');
}

char symbol_64_get_type(const Elf64_Sym *sym, const Elf64_Ehdr *elf_header)
{
    char letter = symbol_64_get_letter(sym, elf_header);

    if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL) letter = tolower(letter);
    return (letter);
}
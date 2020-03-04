/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** elf_64.c
*/

#include "elf_64.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/def.h"
#include "../common/struct.h"
#include "section_64.h"

static void elf_64_architecture(const Elf64_Ehdr *elf_hdr, char **architecture)
{
    for (int i = 0; ELF_MACHINE_ARCH[i].str; ++i) {
        if (ELF_MACHINE_ARCH[i].e_machine == elf_hdr->e_machine) {
            *architecture = ELF_MACHINE_ARCH[i].str;
            return;
        }
    }
}

static void elf_64_flags_value(const Elf64_Ehdr *elf_hdr, unsigned long *value)
{
    if (elf_hdr->e_type == ET_REL) *value += HAS_RELOC;
    if (elf_hdr->e_type == ET_EXEC) *value += EXEC_P;
    if (elf_hdr->e_type == ET_DYN) *value += DYNAMIC;

    Elf64_Shdr *sec_hdr_table = PTR_CREMENT(elf_hdr, elf_hdr->e_shoff);

    for (unsigned int i = 0; i < elf_hdr->e_shnum; ++i) {
        Elf64_Shdr *sec_hdr = &sec_hdr_table[i];

        if (sec_hdr->sh_type == SHT_DYNAMIC && !(*value & D_PAGED))
            *value += D_PAGED;
        if (sec_hdr->sh_type == SHT_DYNSYM && !(*value & HAS_SYMS))
            *value += HAS_SYMS;
        if (sec_hdr->sh_type == SHT_SYMTAB && !(*value & HAS_SYMS))
            *value += HAS_SYMS;

        if (sec_hdr->sh_name == 0) continue;

        char *sec_str = section_64_get_name(sec_hdr, elf_hdr);

        if (strcmp(sec_str, ".debug") == 0) *value += HAS_DEBUG;
    }
}

static void elf_64_flags(
    const Elf64_Ehdr *elf_hdr, char ***flags, unsigned long *value)
{
    elf_64_flags_value(elf_hdr, value);

    unsigned long size = 0;

    for (int i = 0; ELF_BFD_FLAGS[i].str; ++i)
        if (*value & ELF_BFD_FLAGS[i].flag) size++;

    *flags = malloc(sizeof(char *) * (size + 1));

    for (int i = 0, j = 0; ELF_BFD_FLAGS[i].str; ++i) {
        if (*value & ELF_BFD_FLAGS[i].flag) {
            (*flags)[j] = ELF_BFD_FLAGS[i].str;
            j++;
        }
    }
}

void elf_64_print(const Elf64_Ehdr *elf_hdr, const char *path)
{
    char *architecture = NULL;
    char **flags = NULL;
    unsigned long value = 0;

    elf_64_architecture(elf_hdr, &architecture);
    elf_64_flags(elf_hdr, &flags, &value);

    printf("\n%s:     file format elf64-x86-64\n", path);
    printf("architecture: %s, flags 0x%.8lx:\n", architecture, value);

    for (int i = 0; flags && (flags[i]); ++i) {
        if (i) printf(", ");

        printf("%s", flags[i]);
    }

    if (flags == NULL) printf("NO_FLAGS");

    printf("\nstart address 0x%.16lx\n\n", elf_hdr->e_entry);

    free(flags);
}

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
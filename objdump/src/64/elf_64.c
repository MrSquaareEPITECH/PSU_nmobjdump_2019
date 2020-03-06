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

static void elf_64_flags_value_sec(
    const Elf64_Ehdr *elf_hdr, unsigned long *value, const Elf64_Shdr *sec_hdr)
{
    for (int j = 0; ELF_SEC_TYPE_FLAGS[j].flag; ++j)
        if ((sec_hdr->sh_type == ELF_SEC_TYPE_FLAGS[j].sh_type) &&
            !(*value & ELF_SEC_TYPE_FLAGS[j].flag))
            *value += ELF_SEC_TYPE_FLAGS[j].flag;

    if (sec_hdr->sh_name == 0)
        return;

    char *sec_str = section_64_get_name(sec_hdr, elf_hdr);

    for (int j = 0; ELF_SEC_NAME_FLAGS[j].flag; ++j)
        if (strcmp(sec_str, ELF_SEC_NAME_FLAGS[j].name) == 0)
            *value += ELF_SEC_NAME_FLAGS[j].flag;
}

static void elf_64_flags_value(const Elf64_Ehdr *elf_hdr, unsigned long *value)
{
    for (int i = 0; ELF_TYPE_FLAGS[i].flag; ++i)
        if (elf_hdr->e_type == ELF_TYPE_FLAGS[i].e_type)
            *value += ELF_TYPE_FLAGS[i].flag;

    Elf64_Shdr *sec_hdr_table = PTR_CREMENT(elf_hdr, elf_hdr->e_shoff);

    for (unsigned int i = 0; i < elf_hdr->e_shnum; ++i) {
        Elf64_Shdr *sec_hdr = &sec_hdr_table[i];

        elf_64_flags_value_sec(elf_hdr, value, sec_hdr);
    }
}

static void elf_64_flags(
    const Elf64_Ehdr *elf_hdr, char ***flags, unsigned long *value)
{
    elf_64_flags_value(elf_hdr, value);

    unsigned long size = 0;

    for (int i = 0; ELF_BFD_FLAGS[i].str; ++i)
        if (*value & ELF_BFD_FLAGS[i].flag)
            size++;

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

    for (int i = 0; flags && (flags[i]); ++i)
        printf("%.*s%s", ((i) ? 2 : 0), ", ", flags[i]);

    if (flags == NULL)
        printf("NO_FLAGS");

    printf("\nstart address 0x%.16lx\n\n", elf_hdr->e_entry);

    free(flags);
}
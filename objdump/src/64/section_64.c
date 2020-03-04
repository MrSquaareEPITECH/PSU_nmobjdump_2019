/*
** EPITECH PROJECT, 2020
** objdump
** File description:
** section_64.c
*/

#include "section_64.h"

#include <ctype.h>
#include <stdio.h>

#include "../common/def.h"

static void section_64_print_addr(const Elf64_Shdr *sec_hdr, unsigned long i)
{
    unsigned long max_addr = sec_hdr->sh_addr + sec_hdr->sh_size;
    int zeros = 0;

    for (; max_addr; ++zeros, max_addr /= 0xf)
        ;

    if (zeros < 4) zeros = 4;

    printf(" %.*lx", zeros, sec_hdr->sh_addr + i);
}

static void section_64_print_hexa(
    const Elf64_Shdr *sec_hdr, const Elf64_Ehdr *elf_hdr, unsigned long i)
{
    char *content = PTR_CREMENT(elf_hdr, sec_hdr->sh_offset);

    for (int j = 0; (j < 16); ++j) {
        if ((j % 4) == 0) printf(" ");

        if ((i + j) < sec_hdr->sh_size) {
            if (content[i + j] > 0)
                printf("%.2x", content[i + j]);
            else if (content[i + j] < 0)
                printf("%.2x", 256 + content[i + j]);
            else
                printf("00");
        } else {
            printf("  ");
        }
    }
}

static void section_64_print_char(
    const Elf64_Shdr *sec_hdr, const Elf64_Ehdr *elf_hdr, unsigned long i)
{
    char *content = PTR_CREMENT(elf_hdr, sec_hdr->sh_offset);

    for (int j = 0; (j < 16); ++j) {
        if ((i + j) < sec_hdr->sh_size) {
            if (isprint(content[i + j]))
                printf("%c", content[i + j]);
            else
                printf(".");
        } else {
            printf(" ");
        }
    }
}

void section_64_print(const Elf64_Shdr *sec_hdr, const Elf64_Ehdr *elf_hdr)
{
    char *sec_str = section_64_get_name(sec_hdr, elf_hdr);

    printf("Contents of section %s:", sec_str);

    for (unsigned long i = 0; i < sec_hdr->sh_size; i += 16) {
        printf("\n");

        section_64_print_addr(sec_hdr, i);

        section_64_print_hexa(sec_hdr, elf_hdr, i);

        printf("  ");

        section_64_print_char(sec_hdr, elf_hdr, i);
    }

    printf("\n");
}

char *section_64_get_name(const Elf64_Shdr *sec_hdr, const Elf64_Ehdr *elf_hdr)
{
    Elf64_Shdr *sec_hdr_table = PTR_CREMENT(elf_hdr, elf_hdr->e_shoff);
    Elf64_Shdr *shstr_hdr = &sec_hdr_table[elf_hdr->e_shstrndx];
    char *shstr_table = PTR_CREMENT(elf_hdr, shstr_hdr->sh_offset);
    char *name = &shstr_table[sec_hdr->sh_name];

    return (name);
}
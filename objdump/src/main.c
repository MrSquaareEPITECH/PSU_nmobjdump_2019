/*
** EPITECH PROJECT, 2020
** nm
** File description:
** main.c
*/

#include <bfd.h>
#include <ctype.h>
#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include "def.h"
#include "struct.h"

int elf32(Elf32_Ehdr *ehdr)
{
    (void)ehdr;

    return 0;
}

char *elf_machine_isa(Elf64_Half e_machine)
{
    for (int i = 0; ELF_MACHINE_ISA[i].str != NULL; ++i)
        if (ELF_MACHINE_ISA[i].e_machine == e_machine)
            return ELF_MACHINE_ISA[i].str;
    return (ELF_MACHINE_ISA->str);
}

unsigned long elf_flags(
    Elf64_Ehdr *elfHdr, Elf64_Shdr *secHdrTable, char *shstrtab)
{
    unsigned long flags = 0;

    if (elfHdr->e_type == ET_REL) flags += HAS_RELOC;
    if (elfHdr->e_type == ET_EXEC) flags += EXEC_P;
    if (elfHdr->e_type == ET_DYN) flags += DYNAMIC;

    for (unsigned int i = 0; i < elfHdr->e_shnum; ++i) {
        Elf64_Shdr *secHdr = &secHdrTable[i];

        if (secHdr->sh_name == 0) continue;

        char *str = &shstrtab[secHdr->sh_name];

        if (strcmp(str, ".debug") == 0) flags += HAS_DEBUG;
        if (strcmp(str, ".symtab") == 0) flags += HAS_SYMS;
    }

    if (elfHdr->e_phoff) flags += D_PAGED;

    return flags;
}

void section_print(Elf64_Shdr *secHdr, Elf64_Ehdr *elfHdr, char *shstrtab)
{
    printf("Contents of section %s:", &shstrtab[secHdr->sh_name]);

    char *content = PTR_CREMENT(elfHdr, secHdr->sh_offset);
    unsigned int i = 0;

    for (; i < secHdr->sh_size; i += 16) {
        if ((i % 16) == 0) {
            printf("\n");

            printf(" %.4lx", secHdr->sh_addr + i);
        }

        for (int j = 0; (j < 16); ++j) {
            if ((j % 4) == 0) printf(" ");

            if ((i + j) < secHdr->sh_size) {
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

        printf("  ");

        for (int j = 0; (j < 16); ++j) {
            if ((i + j) < secHdr->sh_size) {
                if (isprint(content[i + j]))
                    printf("%c", content[i + j]);
                else
                    printf(".");
            } else {
                printf(" ");
            }
        }
    }

    printf("\n");
}

int elf64(char *path, Elf64_Ehdr *elfHdr)
{
    Elf64_Shdr *secHdrTable = PTR_CREMENT(elfHdr, elfHdr->e_shoff);
    Elf64_Shdr *shstrHdr = &secHdrTable[elfHdr->e_shstrndx];
    char *shstrtab = PTR_CREMENT(elfHdr, shstrHdr->sh_offset);

    printf("shstrtab:\n");

    for (unsigned int i = 0; i < elfHdr->e_shnum; ++i) {
        Elf64_Shdr *secHdr = &secHdrTable[i];

        if (secHdr->sh_name) printf("%s\n", &shstrtab[secHdr->sh_name]);
    }

    printf("\n");

    printf("objdump-like:\n");

    unsigned long flags = elf_flags(elfHdr, secHdrTable, shstrtab);

    printf("%s:     file format elf64-x86-64\n", path);
    printf("architecture: %s, flags 0x%.8lx:\n",
        elf_machine_isa(elfHdr->e_machine), flags);

    char print = 0;

    for (int i = 0; BFD_FLAGS[i].str; ++i) {
        if (flags & BFD_FLAGS[i].flag) {
            if (print) printf(", ");
            printf("%s", BFD_FLAGS[i].str);
            print = 1;
        }
    }

    printf("\n");
    printf("start address 0x%.16lx\n", elfHdr->e_entry);
    printf("\n");

    for (unsigned int i = 0; i < elfHdr->e_shnum; ++i) {
        Elf64_Shdr *secHdr = &secHdrTable[i];

        if (secHdr->sh_name == 0) continue;

        char *secStr = &shstrtab[secHdr->sh_name];

        if (strcmp(secStr, ".bss") == 0) continue;
        if (strcmp(secStr, ".shstrtab") == 0) continue;
        if (strcmp(secStr, ".strtab") == 0) continue;
        if (strcmp(secStr, ".symtab") == 0) continue;

        section_print(secHdr, elfHdr, shstrtab);
    }

    printf("\n");

    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "Invalid number of arguments.");

        return 84;
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        fprintf(stderr, "Failed while opening file.");

        return 84;
    }

    struct stat stat;

    fstat(fd, &stat);

    char *buffer = mmap(NULL, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    byte *arch = PTR_CREMENT(buffer, 4);

    if (*arch == 1)
        elf32((Elf32_Ehdr *)(buffer));
    else if (*arch == 2)
        elf64(argv[1], (Elf64_Ehdr *)(buffer));

    munmap(buffer, stat.st_size);
    close(fd);
}

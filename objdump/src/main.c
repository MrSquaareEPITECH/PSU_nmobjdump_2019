/*
** EPITECH PROJECT, 2020
** nm
** File description:
** main.c
*/

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

void section_print(Elf64_Shdr *secHdr, Elf64_Ehdr *elfHdr, char *shstrtab)
{
    printf("Contents of section %s:", &shstrtab[secHdr->sh_name]);

    char *content = PTR_CREMENT(elfHdr, secHdr->sh_offset);
    unsigned int i = 0;

    for (; i < secHdr->sh_size; ++i) {
        if ((i % 16) == 0) {
            printf("\n");

            printf(" %.4lx ", secHdr->sh_offset + i);
        }

        if (isprint(content[i]))
            printf("%c", content[i]);
        else
            printf(".");
    }

    printf("\n");
}

int elf64(Elf64_Ehdr *elfHdr)
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
        elf64((Elf64_Ehdr *)(buffer));

    munmap(buffer, stat.st_size);
    close(fd);
}

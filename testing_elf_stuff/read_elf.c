#include <stdio.h>
#include <errno.h>
#include <elf.h>

int main(void) {
    Elf64_Ehdr elf_header;

    FILE* file = fopen("hello", "rb");
    if (file == NULL) {
        printf("fopen failed with errno: %d", errno);
    }

    fread(&elf_header, sizeof(elf_header), 1, file);

    Elf64_Phdr program_header;
    fseek(file, elf_header.e_phoff, SEEK_SET);
    fread(&program_header, sizeof(program_header), 1, file);

    Elf64_Shdr section_headers[elf_header.e_shentsize] ;
    fseek(file, elf_header.e_shoff, SEEK_SET);
    fread(&section_headers, sizeof(section_headers), 1, file);

    // FIXME this is wrong, nice
    // FIXME likely fread done stupidly wrong
    for (int i=0; i<elf_header.e_shentsize; i++) {
        printf("%lu", section_headers[i].sh_flags);
    }
}
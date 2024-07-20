#include <stdio.h>
#include <errno.h>
#include <elf.h>

char* get_n_string(char* start, int n) {
    int c = 0;
    while (c < n) {
        if (*start++ == 0) c++;
    }
    return start;
}

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

    Elf64_Shdr section_headers[elf_header.e_shnum] ;
    fseek(file, elf_header.e_shoff, SEEK_SET);
    fread(&section_headers, sizeof(section_headers), 1, file);

    Elf64_Shdr shstrtab_header = section_headers[elf_header.e_shstrndx];
    char shstrtab_content[shstrtab_header.sh_size];
    fseek(file, shstrtab_header.sh_offset, SEEK_SET);
    fread(&shstrtab_content, sizeof(char), shstrtab_header.sh_size, file);

    for (int i=0; i<elf_header.e_shnum; i++) {
        Elf64_Shdr section_header = section_headers[i];

        printf("SECTION: %s\n", &shstrtab_content[section_header.sh_name]);
        printf("\ttype: %u\n", section_header.sh_type);
        printf("\tflags: %lu\n", section_header.sh_flags);
        printf("\taddr: %lu\n", section_header.sh_addr);
        printf("\toffset: %lu\n", section_header.sh_offset);
        printf("\tsize: %lu\n", section_header.sh_size);
        printf("\tlink: %u\n", section_header.sh_link);
        printf("\tinfo: %u\n", section_header.sh_info);
        printf("\taddralign: %lu\n", section_header.sh_addralign);
        printf("\tentsize: %lu\n\n", section_header.sh_entsize);
    }
}
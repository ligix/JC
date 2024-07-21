#include <stdio.h>
#include <errno.h>
#include <elf.h>
#include <stdbool.h>

char* get_n_string(char* start, int n) {
    int c = 0;
    while (c < n) {
        if (*start++ == 0) c++;
    }
    return start;
}

int main(void) {
    Elf64_Ehdr elf_header;

    FILE* file = fopen("python3.12", "rb");
    if (file == NULL) {
        printf("fopen failed with errno: %d", errno);
        return 1;
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


    // I can see three main ways move the relocation metadata (needed because I need to make it bigger):
    // 1) "Deleting" the previous section without any fixup
    // 2) "Deleting" the previous section and fixing all references across sections
    // 3) Leaving the unreferenced section where it was
    //
    // 1- May break programs when the relocation metadata is between sections which have references between them (think
    //    .text and .bss with address relative to RIP)
    // 2- Requires way too much work, I'd need to parse and fix instructions and even that is not guaranteed to work (packers
    //    which unpack only code which then references the same .bss as the packer)
    // 3- Makes the binary way bigger because not only are we adding a LOT of relocation metadata to achieve the desired
    //    computation but we are also duplicating the old one
    //
    // I'm lazy so 3 it is
    //
    // 4) Create a new relocation section, duh

    for (int i=0; i<elf_header.e_shnum; i++) {
        Elf64_Shdr section_header = section_headers[i];

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

    Elf64_Shdr relocation_header;
    bool found_relocation_header = false;
    for (int i=0; i<elf_header.e_shnum; i++) {
        relocation_header = section_headers[i];
        if (relocation_header.sh_type == SHT_RELA){
            found_relocation_header = true;
            break;
        }
    }
    if (!found_relocation_header) {
        printf("Binary does not seem to have a SHT_RELA section");
        return 1;
    }

}
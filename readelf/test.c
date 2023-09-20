#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <elf_file>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    int fd = open(file_path, O_RDONLY);

    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    Elf64_Ehdr elf_header;

    if (read(fd, &elf_header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr)) {
        perror("Failed to read ELF header");
        close(fd);
        return 1;
    }

    // プログラムヘッダ情報の表示
    printf("Program Headers:\n");
    Elf64_Phdr program_header;
    for (int i = 0; i < elf_header.e_phnum; i++) {
        lseek(fd, elf_header.e_phoff + i * sizeof(Elf64_Phdr), SEEK_SET);
        read(fd, &program_header, sizeof(Elf64_Phdr));
        printf("  Type: 0x%lx, Offset: 0x%lx, Vaddr: 0x%lx\n",
               (unsigned long)program_header.p_type, (unsigned long)program_header.p_offset, (unsigned long)program_header.p_vaddr);
        // 他のプログラムヘッダ情報を表示することもできます
    }

    // セクションヘッダ情報の表示
    printf("Section Headers:\n");
    Elf64_Shdr section_header;
    for (int i = 0; i < elf_header.e_shnum; i++) {
        lseek(fd, elf_header.e_shoff + i * sizeof(Elf64_Shdr), SEEK_SET);
        read(fd, &section_header, sizeof(Elf64_Shdr));
        printf("  Name Index: %d, Type: 0x%lx, Addr: 0x%lx\n",
               section_header.sh_name, (unsigned long)section_header.sh_type, (unsigned long)section_header.sh_addr);
        // 他のセクションヘッダ情報を表示することもできます
    }

    close(fd);
    return 0;
}


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

    // ELFヘッダ情報の表示
    printf("ELF Header:\n");
    printf("  Magic: ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", elf_header.e_ident[i]);
    }
    printf("\n");
    printf("  Class: \n");
    printf("  Data: \n");
    printf("  OS/ABI: \n");
    printf("  Type: %d \n", elf_header.e_version);
    printf("  ABI Version:�\n");
    printf("  Type: %d \n", elf_header.e_type);
    close(fd);
    return 0;
}


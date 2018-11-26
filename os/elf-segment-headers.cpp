#include <iostream>
#include <fstream>

#define ELF_NIDENT 16
#define PT_LOAD		1

/**
 To complie

 g++ -std=c++11 elf.cpp -o elf

 ./elf testfile
  ep = 4562864 (4562864 => 459FB0 in hex so similar to readelf)

 readelf -h testfile
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x459fb0
  Start of program headers:          64 (bytes into file)
  Start of section headers:          624 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         10
  Size of section headers:           64 (bytes)
  Number of section headers:         37
  Section header string table index:
 */

struct elf_hdr {
    std::uint8_t e_ident[ELF_NIDENT];
    std::uint16_t e_type;
    std::uint16_t e_machine;
    std::uint32_t e_version;
    std::uint64_t e_entry;
    std::uint64_t e_phoff;
    std::uint64_t e_shoff;
    std::uint32_t e_flags;
    std::uint16_t e_ehsize;
    std::uint16_t e_phentsize;
    std::uint16_t e_phnum;
    std::uint16_t e_shentsize;
    std::uint16_t e_shnum;
    std::uint16_t e_shstrndx;
} __attribute__((packed));

struct elf_phdr {
    std::uint32_t p_type;
    std::uint32_t p_flags;
    std::uint64_t p_offset;
    std::uint64_t p_vaddr;
    std::uint64_t p_paddr;
    std::uint64_t p_filesz;
    std::uint64_t p_memsz;
    std::uint64_t p_align;
} __attribute__((packed));

// return required number of bytes that
// need to be loaded in memory
std::size_t space(const char *name)
{
    std::ifstream ifs{name, std::ios::binary};
    struct elf_hdr hdr;

    if (!ifs.read((char *)(&hdr), sizeof(struct elf_hdr))) {
        return 0;
    }

    struct elf_phdr phdr;
    std::size_t size = 0;

    for (std::size_t i = 0; i < hdr.e_phnum; i++) {
        ifs.read((char *)(&phdr), sizeof(struct elf_phdr));

        std::cout << phdr.p_type << "=" << phdr.p_memsz << std::endl;

        if (phdr.p_type == PT_LOAD) {
            size += phdr.p_memsz;
        }
    }

    return size;
}

std::uintptr_t entry_point(const char *name)
{
    std::ifstream ifs{name, std::ios::binary};
    struct elf_hdr hdr;

    if (!ifs.read((char *)(&hdr), sizeof(struct elf_hdr))) {
        return 0;
    }

    return hdr.e_entry;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Specify ELF filename" << std::endl;
        return 1;
    }

    std::cout << "space = " << space(argv[1]) << std::endl;

    return 0;
}
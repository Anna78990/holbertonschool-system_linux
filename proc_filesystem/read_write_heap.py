#!/usr/bin/python3

from sys import argv
import os


def replace_in_heap(pid, search_string, replace_string):
    """ replace string in heap """
    try:
        # Read the process's memory maps to find heap addresses
        maps_file = f"/proc/{pid}/maps"
        with open(maps_file, 'r') as f:
            for line in f:
                if "[heap]" in line:
                    addr_range = line.split()[0]
                    addr_start, addr_end = \
                        map(lambda x: int(x, 16), addr_range.split("-"))
                    break

        # Read the process's memory from the heap
        mem_file = f"/proc/{pid}/mem"
        with open(mem_file, 'rb+') as f:
            f.seek(addr_start)
            heap_data = f.read(addr_end - addr_start)
            offset = heap_data.find(search_string.encode())
            # Seek back to the start of the heap and write the modified data
            f.seek(addr_start + offset)
            written = f.write(replace_string.encode() + b'\x00')
        print("[*] {:d} bytes written!".format(written))

    except Exception as e:
        print("[ERROR] String '{:s}' not found in heap.".format(search_string))
        exit(1)


if __name__ == "__main__":
    if len(argv) != 4:
        print("Usage: read_write_heap.py pid search_string replace_string")
        sys.exit(1)

    pid = argv[1]
    search_string = argv[2]
    replace_string = argv[3]

    if not pid.isdigit():
        print("Error: PID must be a number.")
        exit(1)

    replace_in_heap(int(pid), search_string, replace_string)

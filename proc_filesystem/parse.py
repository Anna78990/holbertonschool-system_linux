#!/usr/bin/env python3

with open('/proc/self/maps', 'r') as maps_file:
    for line in maps_file:
        print(line.strip())


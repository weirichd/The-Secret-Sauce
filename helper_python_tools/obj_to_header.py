"""
A little script which will convert wavefront obj files into
c header files.
"""

import sys
from random import random

file = sys.argv[1]
output_name = sys.argv[2]

header_name = output_name.upper() + '_H'

positions = []
indices = []

with open(file, 'r') as f:
    line = f.readline()

    while line:
        parts = line.split()

        if len(parts) > 0:

            if parts[0] == 'v':
                positions.append(parts[1] + ', ' + parts[2] + ', ' + parts[3] + ', ')

            if parts[0] == 'f':
                a = int(parts[1]) - 1
                b = int(parts[2]) - 1
                c = int(parts[3]) - 1
                indices.append('{}, {}, {},'.format(a, b, c))

        line = f.readline()


print('#ifndef', header_name)
print('#define', header_name)

# Print out positions
print()
print('float ' + output_name + '_positions[] = {')
for position in positions:
    print('    ' + position)
print('};')

# Print out colors
print()
print('float ' + output_name + '_colors[] = {')
for position in positions:
    print('    {}, {}, {},'.format(random(), random(), random()))
print('};')

# Print out indices
print()
print('int ' + output_name + '_indices[] = {')
for index in indices:
    print('    ' + index)
print('};')

print()
print('int n_' + output_name + '_indices = sizeof(' + output_name + '_indices) / sizeof(int);')
print()
print('int n_' + output_name + '_vertices = sizeof(' + output_name + '_positions) / (sizeof(float) * 3);')
print()
print('#endif')

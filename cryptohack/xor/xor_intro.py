#!/usr/bin/python3

from pwn import *

text = "label"
print(xor(text, 13))
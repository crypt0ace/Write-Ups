#!/usr/bin/env python3

import pwn
with open('cipher.txt') as handle:
	cipher = handle.read()
	for i in range(255):
		print (pwn.xor(cipher, i))

#!/usr/bin/env python

buf = ""
buf += "A"*500

with open("buffer.txt", "w") as f:
	f.write(buf)

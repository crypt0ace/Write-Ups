cipher = bytes.fromhex("73626960647f6b206821204f21254f7d694f7624662065622127234f726927756d")

flag = ""

for byte in range(256):
	res = [chr(n^byte) for n in cipher]
	flag = "".join(res)
	if flag.startswith("crypto"):
		print(flag)
		print(byte)
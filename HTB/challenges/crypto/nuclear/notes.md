```
Nuclear - HackTheBox Crypto Challenge
```

#Findings + Completion
>we are given a '.pcap' file to examine
>can see a hint of 'XOR'
>we find three ciphertexs
	encrypted info of buyer:
		6b65813f4fe991efe2042f79988a3b2f2559d358e55f2fa373e53b1965b5bb2b175cf039
	ciphertext encrypted w a key:
		fd034c32294bfa6ab44a28892e75c4f24d8e71b41cfb9a81a634b90e6238443a813a3d34
	again encrypting w key:
		de328f76159108f7653a5883decb8dec06b0fd9bc8d0dd7dade1f04836b8a07da20bfe70
>using CyberChef
>add the last key 'de328...' as the input
>use recipie;
	HEX:XOR:XOR
>add the other two keys into XOR
>flag.txt
	HTB{s3cr3t_sh4r1ng_w1th_x0r_15_l4m3}
from pwn import *

cipher = bytes.fromhex("0e0b213f26041e480b26217f27342e175d0e070a3c5b103e2526217f27342e175d0e077e263451150104")

# flag format = "crypto{"
# message ^ secret_key = crypto{?????????
# secret_key = message ^ crypto{?????????

res = xor(cipher[:7], "crypto{")

partial_key = "myXORkey"
complete_key = (partial_key * (len(cipher)//len(partial_key)+1))[:len(cipher)]

flag = xor(cipher, complete_key)

print(flag)
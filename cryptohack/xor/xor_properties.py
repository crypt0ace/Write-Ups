#!/usr/bin/python3

from pwn import *

# ---------challenge-----------
# KEY1 = a6c8b6733c9b22de7bc0253266a3867df55acde8635e19c73313
# KEY2 ^ KEY1 = 37dcb292030faa90d07eec17e3b1c6d8daf94c35d4c9191a5e1e
# KEY2 ^ KEY3 = c1545756687e7573db23aa1c3452a098b71a7fbf0fddddde5fc1
# FLAG ^ KEY1 ^ KEY3 ^ KEY2 = 04ee9855208a2cd59091d04767ae47963170d1660df7f56f5faf

# KEY2 = KEY1 ^ (KEY1 ^ KEY2)
# KEY3 = KEY2 ^ (KEY2 ^ KEY3)
# KEY{1,2,3} = KEY3 ^ (KEY1 ^ KEY2)
# FLAG = {FLAG ^ KEY1 ^ KEY3 ^ KEY2} ^ KEY{1,2,3}
# ------------------------------

key1 = bytes.fromhex("a6c8b6733c9b22de7bc0253266a3867df55acde8635e19c73313")
key1_2 = "37dcb292030faa90d07eec17e3b1c6d8daf94c35d4c9191a5e1e"
key2_3 = "c1545756687e7573db23aa1c3452a098b71a7fbf0fddddde5fc1"
flag_123 = "04ee9855208a2cd59091d04767ae47963170d1660df7f56f5faf"

key2 = xor(key1, bytes.fromhex(key1_2))
key3 = xor(key2, bytes.fromhex(key2_3))
key1_2_3 = xor(key3, bytes.fromhex(key1_2))

flag = xor(key1_2_3, bytes.fromhex(flag_123))

print(flag).decode()
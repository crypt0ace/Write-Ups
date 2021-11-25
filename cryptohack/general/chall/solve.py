#!/usr/bin/python3

#!/usr/bin/env python3
from pwn import *
import json
import base64
import binascii
import codecs
import sys

def decode(t, data):
    if t == 'base64':
        return base64.b64decode(data).decode('utf-8')
    elif t == 'hex':
        return binascii.unhexlify(data).decode('utf-8')
    elif t == 'bigint':
        return binascii.unhexlify(data.replace('0x', '')).decode('utf-8')
    elif t == 'rot13':
        return codecs.encode(data, 'rot_13')
    elif t == 'utf-8':
        s = ""
        for c in data:
            s += chr(c)
        return s


r = remote('socket.cryptohack.org', 13377, level = 'debug')

def json_recv():
    line = r.recvline()
    return json.loads(line.decode())

def json_send(hsh):
    request = json.dumps(hsh).encode()
    r.sendline(request)

while True:

    received = json_recv()

    if "flag" in received:
        print("FLAG: %s" % received["flag"])
        sys.exit(0)

    to_send = {
        "decoded": decode(received["type"], received["encoded"])
    }
    json_send(to_send)

# import telnetlib
# import base64
# import Crypto.Util.number
# import codecs
# import random
# import json

# HOST = "socket.cryptohack.org"
# PORT = 13377

# tn = telnetlib.Telnet(HOST, PORT)

# def readline():
#     return tn.read_until(b"\n")

# def json_recv():
#     line = readline()
#     return json.loads(line.decode())

# def json_send(hsh):
#     request = json.dumps(hsh).encode()
#     tn.write(request)

# def decoder(kind,text):
#     if kind == 'hex':
#         return bytes.fromhex(text).decode('utf-8')
    
#     elif kind == 'utf-8':
#         answer = ""
#         for n in text:
#             answer += chr(n)
#         return answer
    
#     elif kind == 'rot13':
#         return codecs.decode(text, "rot13")
    
#     elif kind == 'base64':
#         return base64.b64decode(text).decode()

#     elif kind ==  'bigint':
#         return Crypto.Util.number.long_to_bytes(int(text, 16)).decode()

# for i in range(1,101):
#     received = json_recv()    
#     print(f"Question {i}")
#     print(f"Received type: {received['type']}")
#     print(f"Received encoded value: {received['encoded']}")
#     to_send = {"decoded": decoder(received["type"],received["encoded"])}    
#     print(f"Answer: {to_send} \n")
#     json_send(to_send)

# json_recv()
# json_recv()
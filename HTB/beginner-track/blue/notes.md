```
Blue - 10.10.10.40
```

#Port Open - 135,139,445

#Findings + Exploitation
>port 445 was open so i used nmap script to check if vulnerable to eternal blue
	sudo nmap -A --script /usr/share/nmap/scripts/smb-vuln-ms17-010.nse 10.10.10.40 -p 445 -Pn
>it was vulnerable
>used metsploit to exploit it
>user.txt
	4c546aea7dbee75cbd71de245c8deea9
>in the meterpreter used the command to get root
	getsystem
>got ROOT!!!
	ff548eb71e920ff6c08843ce9df4e717
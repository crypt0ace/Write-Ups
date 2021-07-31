```
Netmon - 10.10.10.152
```

#Ports Open - 21,80,135,139,445

#Detail of Ports:
>21		ftp
>80		http
>135	msrpc
>139	netbios
>445	microsoft-ds

#Findings + Exploitation
>found 'C:\' running of ftp
>found user in the \Public Foler
	dd58ce67b49e15105e88096c8d9255a5
>found the config file for PRTG at 'C:\programdata\Paessler'
>found the old pass in 'PRTG Configuration.old.bak'
	prtgadmin:PrTg@dmin2019
>got in
>found the scanners page
>added a exe scanner
>with powershell and added a parameter with ";" and then space and then the reverse shell of powwershell
>started a istener
>got a shell back
>root.txt
	3018977fb944bf1878f75b879fba67cc
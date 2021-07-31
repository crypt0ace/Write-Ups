```
Devel - 10.10.10.5
```

#Ports Open - 21,80

#Detail of Ports
>21		ftp
>80		http

#Findings + Exploitation
>found IIS 7 running on port 80
>found it can host aspx files
>ftp was the web's root folder
>uploaded the cmd.aspx on ftp
>accessed it on port 80
>used it to get a shell using msfvenom and certutil
>used metasploits local-exploit-suggestor to get priv esc ideas
>one of them worked and got ROOT!!!
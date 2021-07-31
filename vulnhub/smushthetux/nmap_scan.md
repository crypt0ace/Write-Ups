# Nmap 7.91 scan initiated Fri Feb 19 02:46:33 2021 as: nmap -sV -A -p- -oN nmap_scan.md 192.168.43.234
Nmap scan report for tux (192.168.43.234)
Host is up (0.0010s latency).
Not shown: 65532 closed ports
PORT      STATE SERVICE VERSION
22/tcp    open  ssh     OpenSSH 6.7p1 Debian 5+deb8u1 (protocol 2.0)
| ssh-hostkey: 
|   1024 14:a6:c1:38:01:ac:66:8f:59:95:3b:6d:27:76:e1:41 (DSA)
|   2048 ae:c5:f4:67:7c:77:18:17:2e:3d:51:c1:2a:8a:76:df (RSA)
|   256 5e:08:31:f6:dc:d3:90:4a:36:a7:33:44:95:5e:87:3a (ECDSA)
|_  256 20:8e:d2:99:81:aa:39:01:f3:78:87:8e:75:07:eb:e4 (ED25519)
111/tcp   open  rpcbind 2-4 (RPC #100000)
| rpcinfo: 
|   program version    port/proto  service
|   100000  2,3,4        111/tcp   rpcbind
|   100000  2,3,4        111/udp   rpcbind
|   100000  3,4          111/tcp6  rpcbind
|   100000  3,4          111/udp6  rpcbind
|   100024  1          37844/tcp   status
|   100024  1          41851/udp6  status
|   100024  1          59980/udp   status
|_  100024  1          59983/tcp6  status
37844/tcp open  status  1 (RPC #100024)
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
# Nmap done at Fri Feb 19 02:46:58 2021 -- 1 IP address (1 host up) scanned in 25.21 seconds

Starting Nmap 7.91 ( https://nmap.org ) at 2021-04-02 11:55 EDT
Nmap scan report for dc-5.home (192.168.10.9)
Host is up (0.00055s latency).

PORT      STATE SERVICE VERSION
80/tcp    open  http    nginx 1.6.2
|_http-server-header: nginx/1.6.2
|_http-title: Welcome
111/tcp   open  rpcbind 2-4 (RPC #100000)
| rpcinfo: 
|   program version    port/proto  service
|   100000  2,3,4        111/tcp   rpcbind
|   100000  2,3,4        111/udp   rpcbind
|   100000  3,4          111/tcp6  rpcbind
|   100000  3,4          111/udp6  rpcbind
|   100024  1          43364/tcp   status
|   100024  1          47600/udp   status
|   100024  1          51383/tcp6  status
|_  100024  1          58293/udp6  status
43364/tcp open  status  1 (RPC #100024)

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 12.83 seconds
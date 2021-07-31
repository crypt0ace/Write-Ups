```
MarketDump - Forensics
```

#Notes
>opened pcap in wireshark
>went all the way down and saw a GET request made to customers.sql
>followed the TCPStream and found some AmericanExpress logs
>found a base 58 encoded string in the middle
>decoded and got flag
	HTB{DonTRuNAsRoOt!MESsEdUpMarket}
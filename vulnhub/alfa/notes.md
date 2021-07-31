
#Found this on robots.txt

/home
/admin
/login
/images
/cgi-bin
/intranet
/wp-admin
/wp-login


++++++++++[>+>+++>+++++++>++++++++++<<<<-]>>+++++++++++++++++.>>---.+++++++++++.------.-----.<<--.>>++++++++++++++++++.++.-----..-.+++.++.



the brainfuck code gave another directory to work with. /alfa-support
in there found that thomas pass is pet name with 3 digits. pet is milo. made a script for 3 digits generation.

bruteforce ssh using the pass made from script

found pass milo666


got user flag:
user_flag==>> M4Mh5FX8EGGGSV6CseRuyyskG
got root flag:
root_flag==>> QFqy4EUHwtu9rrrVe2T27we5W



#root how?

well, we had a remote secret file. used it to crack pass.
first started ssh tunnel through local hsot on our machine

an unusual port on 5901 was running. its vnc.

so first sent the file to our server. 
On attacker machine:
[scp -P{port of ssh on victim} {name of ssh}@{ip address of victim}:/{path of the file to send} {path to send it to}]

use this command to start ssh tunneling:
[ssh -L {port to tunnel (in our case port of vnc a.k.a. 5901)}:localhost:{port to tunnel (in our case port of vnc a.k.a. 5901)} {name of victim machine}@{ip of victim machine} -p {port of ssh}]

the vnc port should be open for localhost now. check using:
nmap -p{port of vnc} localhost

then start the vnc viewer:
vncviewer -passwd {the file} localhost{the port to tunnel to}

now youre root!
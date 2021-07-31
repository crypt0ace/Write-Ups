#found "dale" on robots.txt. possible username.

#Dirsearch of scripts folder found a "script.txt" file:
	#!/bin/bash
	read -p "Enter Username: " REDACTED
	read -sp "Enter Username Password: " REDACTED
	echo
	ftp_server="localhost"
	ftp_username="$Username"
	ftp_password="$Password"
	mkdir /home/username/linux/source_folder
	source_folder="/home/username/source_folder/"
	cp -avr config* $source_folder
	dest_folder="/home/username/linux/dest_folder/"
	ftp -in $ftp_server <<END_SCRIPT
	quote USER $ftp_username
	quote PASS $decrypt
	cd $source_folder
	!cd $dest_folder
	mget -R *
	quit

	# Updated version of the script
	# Note to self had to change the extension of the old "script" in this folder, as it has creds in

#searched for old scripts found nothing.

#found a subdomain:
	dev.team.thm

#added to /etc/hosts file

#had a link vuln to LFI

#used it to find a ssh key of dale in /etc/ssh/sshd_config

#cut the "#" in front of all lines using:
	cat id_rsa | sed 's/^.//'

#ssh into dale

#found dale can run admin_checks using gyles

# 
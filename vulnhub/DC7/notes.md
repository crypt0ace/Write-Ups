#found 40 disallowed entries in robots.txt

#enumeration found that a username DC7USER is in the copyright section

#Twitter shows a profile with that username with a github link

#github link gives a staffdb database

#contains a config file with user/pass:
	dc7user:MdR3xOgB7#dW

#ssh success

#enumeration found a backups.sh script running but being owned by www-data as group

#in the script "drush" is being used

#used this command to change pass for admin in drupal:
	drush user-password admin --pasword=crypt0ace

#changed pass

#logged in admin

#had to download the php module

#changed the 404 page to php reverse shell

#got a shell back

#added one liner reverse shell to backups.sh

#waited for some time because it was on cron job so it would automatically start it

#got root!

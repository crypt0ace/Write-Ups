
  _|. _ _  _  _  _ _|_    v0.4.1
 (_||| _) (/_(_|| (_| )

Extensions: php, aspx, jsp, html, js | HTTP method: GET | Threads: 30 | Wordlist size: 10848

Error Log: /home/crypt0ace/Desktop/dirsearch/logs/errors-21-03-29_12-20-21.log

Target: http://192.168.10.13/

Output File: /home/crypt0ace/Desktop/dirsearch/reports/192.168.10.13/_21-03-29_12-20-23.txt

[12:20:23] Starting: 
[12:20:25] 403 -  299B  - /.ht_wsr.txt                                                                                                  
[12:20:25] 403 -  304B  - /.htaccess.sample
[12:20:26] 403 -  302B  - /.htaccess.bak1
[12:20:26] 403 -  302B  - /.htaccess_orig
[12:20:26] 403 -  302B  - /.htaccess.save
[12:20:26] 403 -  303B  - /.htaccess_extra
[12:20:26] 403 -  302B  - /.htaccess.orig
[12:20:26] 403 -  292B  - /.htm
[12:20:26] 403 -  300B  - /.htaccess_sc
[12:20:26] 403 -  300B  - /.htaccessOLD
[12:20:26] 403 -  300B  - /.htaccessBAK
[12:20:26] 403 -  301B  - /.htaccessOLD2
[12:20:26] 403 -  298B  - /.htpasswds    
[12:20:26] 403 -  302B  - /.htpasswd_test              
[12:20:26] 403 -  299B  - /.httr-oauth            
[12:20:26] 403 -  293B  - /.html                   
[12:20:27] 403 -  292B  - /.php                                       
[12:20:27] 403 -  293B  - /.php3            
[12:20:49] 200 -   52KB - /index.php                                                                              
[12:20:50] 200 -   19KB - /license.txt                                                                  
[12:20:56] 200 -    7KB - /readme.html                                                         
[12:20:57] 403 -  301B  - /server-status                                                                
[12:20:57] 403 -  302B  - /server-status/  
[12:21:02] 301 -  317B  - /wp-admin  ->  http://192.168.10.13/wp-admin/                                           
[12:21:02] 200 -    0B  - /wp-content/          
[12:21:02] 301 -  319B  - /wp-content  ->  http://192.168.10.13/wp-content/
[12:21:02] 200 -   69B  - /wp-content/plugins/akismet/akismet.php                      
[12:21:03] 500 -    0B  - /wp-content/plugins/hello.php
[12:21:03] 500 -    0B  - /wp-includes/rss-functions.php                                        
[12:21:03] 301 -  320B  - /wp-includes  ->  http://192.168.10.13/wp-includes/
[12:21:03] 200 -   40KB - /wp-includes/                      
[12:21:04] 200 -    0B  - /wp-config.php                       
[12:21:04] 200 -    0B  - /wp-cron.php
[12:21:04] 302 -    0B  - /wp-signup.php  ->  http://dc-2/wp-login.php?action=register
[12:21:04] 200 -    2KB - /wp-login.php
[12:21:05] 200 -    1B  - /wp-admin/admin-ajax.php
[12:21:05] 302 -    0B  - /wp-admin/  ->  http://dc-2/wp-login.php?redirect_to=http%3A%2F%2F192.168.10.13%2Fwp-admin%2F&reauth=1
[12:21:05] 200 -    1KB - /wp-admin/install.php
[12:21:05] 500 -    4KB - /wp-admin/setup-config.php
[12:21:05] 405 -   42B  - /xmlrpc.php

Task Completed             




-----------------
DIRB v2.22    
By The Dark Raver
-----------------

START_TIME: Mon Mar 29 12:23:17 2021
URL_BASE: http://192.168.10.13/
WORDLIST_FILES: /usr/share/dirb/wordlists/common.txt

-----------------

GENERATED WORDS: 4612                                                                      

---- Scanning URL: http://192.168.10.13/ ----
+ http://192.168.10.13/index.php (CODE:200|SIZE:53562)                                                                                                               
+ http://192.168.10.13/server-status (CODE:403|SIZE:301)                                                                                                             
==> DIRECTORY: http://192.168.10.13/wp-admin/                                                                                                                        
==> DIRECTORY: http://192.168.10.13/wp-content/                                                                                                                      
==> DIRECTORY: http://192.168.10.13/wp-includes/                                                                                                                     
+ http://192.168.10.13/xmlrpc.php (CODE:405|SIZE:42)                                                                                                                 
                                                                                                                                                                     
---- Entering directory: http://192.168.10.13/wp-admin/ ----
+ http://192.168.10.13/wp-admin/admin.php (CODE:302|SIZE:0)                                                                                                          
==> DIRECTORY: http://192.168.10.13/wp-admin/css/                                                                                                                    
==> DIRECTORY: http://192.168.10.13/wp-admin/images/                                                                                                                 
==> DIRECTORY: http://192.168.10.13/wp-admin/includes/                                                                                                               
+ http://192.168.10.13/wp-admin/index.php (CODE:302|SIZE:0)                                                                                                          
==> DIRECTORY: http://192.168.10.13/wp-admin/js/                                                                                                                     
==> DIRECTORY: http://192.168.10.13/wp-admin/maint/                                                                                                                  
==> DIRECTORY: http://192.168.10.13/wp-admin/network/                                                                                                                
==> DIRECTORY: http://192.168.10.13/wp-admin/user/                                                                                                                   
                                                                                                                                                                     
---- Entering directory: http://192.168.10.13/wp-content/ ----
+ http://192.168.10.13/wp-content/index.php (CODE:200|SIZE:0)                                                                                                        
==> DIRECTORY: http://192.168.10.13/wp-content/languages/                                                                                                            
==> DIRECTORY: http://192.168.10.13/wp-content/plugins/                                                                                                              
==> DIRECTORY: http://192.168.10.13/wp-content/themes/                                                                                                               
                                                                                                                                                                     
---- Entering directory: http://192.168.10.13/wp-includes/ ----
(!) WARNING: Directory IS LISTABLE. No need to scan it.                        
    (Use mode '-w' if you want to scan it anyway)
                                                                                                                                                                     
---- Entering directory: http://192.168.10.13/wp-admin/css/ ----
(!) WARNING: Directory IS LISTABLE. No need to scan it.                        
    (Use mode '-w' if you want to scan it anyway)
                                                                                                                                                                     
---- Entering directory: http://192.168.10.13/wp-admin/images/ ----
(!) WARNING: Directory IS LISTABLE. No need to scan it.                        
    (Use mode '-w' if you want to scan it anyway)
                                                                                                                                                                     
---- Entering directory: http://192.168.10.13/wp-admin/includes/ ----
(!) WARNING: Directory IS LISTABLE. No need to scan it.                        
    (Use mode '-w' if you want to scan it anyway)
                                                                                                                                                                     
---- Entering directory: http://192.168.10.13/wp-admin/js/ ----
(!) WARNING: Directory IS LISTABLE. No need to scan it.                        
    (Use mode '-w' if you want to scan it anyway)
                                                                                                                                                                     
---- Entering directory: http://192.168.10.13/wp-admin/maint/ ----
(!) WARNING: Directory IS LISTABLE. No need to scan it.                        
    (Use mode '-w' if you want to scan it anyway)
                                                                                                                                                                     
---- Entering directory: http://192.168.10.13/wp-admin/network/ ----
+ http://192.168.10.13/wp-admin/network/admin.php (CODE:302|SIZE:0)                                                                                                  
+ http://192.168.10.13/wp-admin/network/index.php (CODE:302|SIZE:0)                                                                                                  
                                                                                                                                                                     
---- Entering directory: http://192.168.10.13/wp-admin/user/ ----
+ http://192.168.10.13/wp-admin/user/admin.php (CODE:302|SIZE:0)                                                                                                     
+ http://192.168.10.13/wp-admin/user/index.php (CODE:302|SIZE:0)                                                                                                     
                                                                                                                                                                     
---- Entering directory: http://192.168.10.13/wp-content/languages/ ----
(!) WARNING: Directory IS LISTABLE. No need to scan it.                        
    (Use mode '-w' if you want to scan it anyway)
                                                                                                                                                                     
---- Entering directory: http://192.168.10.13/wp-content/plugins/ ----
+ http://192.168.10.13/wp-content/plugins/index.php (CODE:200|SIZE:0)                                                                                                
                                                                                                                                                                     
---- Entering directory: http://192.168.10.13/wp-content/themes/ ----
+ http://192.168.10.13/wp-content/themes/index.php (CODE:200|SIZE:0)                                                                                                 
                                                                                                                                                                     
-----------------
END_TIME: Mon Mar 29 12:23:48 2021
DOWNLOADED: 32284 - FOUND: 12
                                        
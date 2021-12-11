<?php
	$IP = $_SERVER['REMOTE_ADDR'];
	$allowed_server = fopen("../.htpasswd/myip", "r") or die ("Failed to load.");
	$allowed = fread($allowed_server, filesize("../.htpasswd/myip"));

	if (strpos($allowed, $IP) !== false) {
		echo "Welcome Ian!<br>";
	
		foreach (file("../.htpasswd/log.txt") as $name) {
   			 echo('<tr><td align="center">'.$name.'</td></tr>');
		}

	} else {
		$warning = sprintf("You aren't supposed to be here %s!", $IP);
		echo $warning;
	}

	fclose($allowed_server);
?>

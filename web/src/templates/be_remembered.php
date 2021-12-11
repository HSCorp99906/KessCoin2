<?php
	$IP = $_SERVER['REMOTE_ADDR'];
	$log = fopen("../.htpasswd/log.txt", "a") or die("Unable to load, try refreshing.");
	fwrite($log, "$IP\n");
	fclose($log);

	echo "You shall be remembered! Just wait!";
?>

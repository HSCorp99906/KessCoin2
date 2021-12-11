<?php
	include("restricted_page__join.html");

	$message = sprintf("Sorry, %s. The form is broken.", $_GET["name"]);
	echo $message;
?>

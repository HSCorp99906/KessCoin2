<?php
	$webhook = "https://discord.com/api/webhooks/919115606316421201/6jhel636nIGEvYzWLMLE4U_x2_II5tcC1M5_wMq9E14xnRJ7SUmhtq8zuSFBAjwdG9iE";

	$headers = [ 'Content-Type: application/json; charset=utf-8' ];
	$timestamp = date("c", strtotime("now"));
	define("CLIENT", $_SERVER["REMOTE_ADDR"]);

	$webhook_data = [
			"username" => "___MINE_DATA___",
			"content" = sprintf("%s submitted a mine request. Checking blocks..\nRequest made at: $timestamp", CLIENT);
		];

	$ch = curl_init();
	curl_setopt($ch, CURLOPT_URL, $webhook);
	curl_setopt($ch, CURLOPT_POST, true);
	curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
	curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($webhook_data));
	$response = curl_exec($ch);
	echo $response;

	echo "Welcome to the mining station!<br>";
	echo "Checking if there are blocks to mine..<br>";

	$checkfile = "";
?>

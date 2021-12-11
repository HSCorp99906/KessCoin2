<?php
	echo "Welcome to the mining station..<br>";
	echo "Mining...";

	$url = "https://discord.com/api/webhooks/919115606316421201/6jhel636nIGEvYzWLMLE4U_x2_II5tcC1M5_wMq9E14xnRJ7SUmhtq8zuSFBAjwdG9iE";
	$headers = [ 'Content-Type: application/json; charset=utf-8' ];
	$POST = ["username" => "___MINED_DATA___", "content" => "BLOCK_READY_TO_BE_MINED"];

	$ch = curl_init();
	curl_setopt($ch, CURLOPT_URL, $url);
	curl_setopt($ch, CURLOPT_POST, true);
	curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
	curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
	curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($POST));
	$response   = curl_exec($ch);

?>

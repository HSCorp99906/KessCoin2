<html>
	<head>
		<title>Wallet</title>
		<meta name="description" content="KessCoin Wallet">
	

		<style>
			#pk {
				filter: blur(4px);
				cursor: pointer;
				transition: 1.5s
			}

			#pk:hover {
				filter: blur(0px);
			}

			#transactions {
				border: 5px solid black;				
			}
		</style>

        <script>
            // Frees resources if user closes
            window.onbeforeunload = () => {
                const xhr = new XMLHttpRequest();
                xhr.open("GET", "/freetransaction.php");
                xhr.send(null);
		       document.cookie = 'tcansend=; Max-Age=0; path=/; domain=' + location.host;
            }

	       let confirmtransaction = () => {
		       if (!(window.confirm("Are you sure you want to make a transaction?"))) {
			       document.cookie = "confirm=false";
		       } else {
			       document.cookie = "confirm=true";
		       }
	       }
        </script>

	</head>

	<body>
		<?php
			session_start();
			$correct_token = $_SESSION["privkey"] == "5KbDjRoof8PX84KebRZd3oehNnAHgU5WkW9NM5rEy3k1yXNXz9m";

			if (!(isset($_SESSION["username"]) || !(correct_token))) {
				header("Location: /401.html");
			}

			$pubkey = $_SESSION["pubkey"];

		?>


		<h1>Wallet</h1>

		<div class="wallet-info">
			<p>Private Key</p>
			<input id="pk" value=<?php echo $_SESSION['privkey'] ?> readonly>
			<h4>Your public key is: <?php echo $_SESSION['pubkey']?></h4>
			<h4>Your balance is: <?php echo file_get_contents("../secrets/$pubkey/balance.bal", true);?></h4>
		</div>
		<br><br><br>

		<h1>Send Transaction</h1>
		<form method="post">
            <label for="to-address">To Address</label>
            <input type="text" name="ta"><br>
            <label for="from-address">From Address</label>
            <input type="text" value="<?php echo $_SESSION['pubkey'];?>" name="fa" readonly><br>
            <label for="amount">Amount</label>
            <input type="text" name="amt"><br>
            <button type="submit" id="submit" style="border-radius: 500px" onclick="confirmtransaction()">Submit</button>
        </form>

		<?php
			while (file_exists("newtransaction")) {
				sleep(5);
			}
		?>

        <?php
            $lenta = strlen($_POST["ta"]);
            $lenfa = strlen($_SESSION["pubkey"]);
			$amt = $_POST["amt"];
            $error = false;
			$to_addr = $_POST["ta"];
			$from_addr = $_POST["fa"];

			$okay = $from_addr == $_SESSION["pubkey"];
        ?>

<?php if ($lenta != 34 && $lenta > 0 || $lenfa != 34 && $lenta > 0 || !(file_exists("../secrets/$to_addr")) && strlen($to_addr) > 0 || !($okay) && $from_addr > 0 || $to_addr > 0 && $to_addr == $from_addr) {
            $error = true;
            ?>
            <h1 style="background-color: rgb(255, 0, 0)">INVALID TO-ADDR/FROM-ADDR/AMOUNT</h1>
        <?php
			} elseif (!($error) && $lenta == 34 && $_COOKIE['confirm'] == "true" && !(isset($_COOKIE['visited']))) {
				srand(date());
                $transaction = fopen("newtransaction", "a");
                $tinfo = $_POST['ta'];
                $tinfo .= PHP_EOL;
                $tinfo .= $_SESSION["pubkey"];
                $tinfo .= PHP_EOL;
				$tinfo .= $_POST['amt'];
				$tinfo .= PHP_EOL;
				$tinfo .= rand() + rand();

				$fa = $_POST['fa'];

                fwrite($transaction, $tinfo, strlen($tinfo));
                fclose($transaction);
                sleep(20);
                unlink("newtransaction");
				$cur_id = rand();
				$rn2 = rename("../secrets/newtransaction", "../secrets/transaction-$cur_id-$fa");

				if (rn1 == false || rn2 == false) {
					echo "<br>ERROR</br>";
				}

                echo "Your transaction has finished processing, you may exit this page.<br>";
				echo "<strong>Please do not reload or your transaction might be repeated.</strong>";
            } elseif ($_COOKIE['confirm'] == "false") {
				setcookie("confirm", "true", time() - 3600);
				header("Location: https://kesscoin.com/");
			}

			$addr = $_SESSION["pubkey"];

			$files = glob("../secrets/*$addr");
			$transactionData = array();
			foreach($files as $file) {
				$handle = fopen($file, "r");
				$content = null;

				print_r($file);

				while (!(feof($handle))) {
					$content = fgets($handle);
					array_push($transactionData, $content);
				}

				fclose($handle);
			}
	?>

		<br><br>

		<h1>Pending Transactions</h1>
		<div id="transactions">

			<?php
				$thingidx = 0;  // 1: TO_ADDRESS, 2: FROM_ADDRESS, 3: AMOUNT
			?>
		
			<h1><?php foreach($transactionData as $t) { if ($thingidx == 1) { echo "TO_ADDRESS: $t<br>"; } else if ($thingidx == 2) { echo "FROM ADDRESS: $t<br>"; } else if ($thingidx == 3) { echo "AMOUNT: $t KC<br>";} else if ($thingidx == 4) { echo "ID: $t<br>"; } $thingidx++;continue; }?></h1>
		</div>	

		<br><br><a href="/logout.php">Logout</a>

	</body>
</html>

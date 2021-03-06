<html>
    <head>
        <title>Transaction Center</title> 
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

		<?php
		    if (isset($_COOKIE['visited'])) {   // Prevents re-visiting after awhile.
			header("Location: /");
		    }
		?>

    </head>

    <body>

        <h1>Once form is complete, wait up to a minute for transaction to process.<br>Please Do not close tab.</h1>

        <form method="post">
            <label for="to-address">To Address</label>
            <input type="text" name="ta"><br>
            <label for="from-address">From Address</label>
            <input type="text" name="fa"><br>
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
            $lenfa = strlen($_POST["fa"]);
            $error = false;
        ?>

        <?php if ($lenta != 64 and $lenta > 0 or lenfa != 64 and lenfa > 0) {
            $error = true;
            ?>
            <h1 style="background-color: rgb(255, 0, 0)">INVALID TO/FROM ADDRESS.</h1>
        <?php
            } elseif (!($error) && $lenfa == 64 && $lenta == 64 && $_COOKIE['confirm'] == "true" && !(isset($_COOKIE['visited']))) {
                $transaction = fopen("newtransaction", "a");
                $tinfo = $_POST['ta'];
                $tinfo .= PHP_EOL;
                $tinfo .= $_POST['fa'];
                $tinfo .= PHP_EOL;
                $tinfo .= $_POST['amt'];

				$fa = $_POST['fa'];

                fwrite($transaction, $tinfo, strlen($tinfo));
                fclose($transaction);
                sleep(20);
                unlink("newtransaction");
				$cur_id = rand();
				$rn1 = rename("../secrets/sha1.sign", "../secrets/sha1-$cur_id-$fa.sign");
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
        ?>

    </body>
</html>

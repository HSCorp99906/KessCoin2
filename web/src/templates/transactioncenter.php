<html>
    <head>
        <title>Transaction Center</title>

        <script>
            // Frees resources if user closes
            window.onbeforeunload = () => {
                const xhr = new XMLHttpRequest();
                xhr.open("GET", "/freetransaction.php");
                xhr.send(null);
            }
        </script>

    </head>

    <body>

        <h1>Once form is complete, wait up to a minute for transaction to process.<br>Please Do not close tab.</h1>

        <form>
            <label for="to-address">To Address</label>
            <input type="text" name="ta"><br>
            <label for="from-address">From Address</label>
            <input type="text" name="fa"><br>
            <label for="amount">Amount</label>
            <input type="text" name="amt"><br>
            <button type="submit" style="border-radius: 500px">Submit</button>
        </form>

        <?php
            $lenta = strlen($_GET["ta"]);
            $lenfa = strlen($_GET["fa"]);
            $error = false;
        ?>

        <?php if ($lenta != 64 and $lenta > 0 or lenfa != 64 and lenfa > 0) {
            $error = true;
            ?>
            <h1 style="background-color: rgb(255, 0, 0)">INVALID TO/FROM ADDRESS.</h1>
        <?php
            } elseif (!($error) && $lenfa == 64 && $lenta == 64) {
                $transaction = fopen("newtransaction", "a");
                $tinfo = $_GET['ta'];
                $tinfo .= PHP_EOL;
                $tinfo .= $_GET['fa'];
                $tinfo .= PHP_EOL;
                $tinfo .= $_GET['amt'];
                fwrite($transaction, $tinfo, strlen($tinfo));
                fclose($transaction);
                sleep(11);
                unlink("newtransaction");
                echo "Your transaction is complete! You may now exit off of this page.";
            }
        ?>

    </body>
</html>

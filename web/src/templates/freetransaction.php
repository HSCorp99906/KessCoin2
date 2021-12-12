<?php
    if (file_exists("newtransaction")) {
        unlink("newtransaction");
    }

    header("Location: https://kesscoin.com/");
?>

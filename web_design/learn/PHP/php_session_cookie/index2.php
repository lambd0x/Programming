<?php
session_start();
// Check if session exists
if(isset($_SESSION['nome'])) {
	echo $_SESSION['nome'];
}

// Delete a session variable
unset($_SESSION['nome']);

// Destroy every session variable if more there is.
session_destroy();
?>

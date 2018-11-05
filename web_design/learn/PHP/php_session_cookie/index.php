<?php
//Sessions
session_start();
$_SESSION['nome'] = 'Nick';

//Cookie: A / é para que o cookie seja acessível de qualquer página, não apenas aqui.
setcookie('name','value','time()+(60*60*24)', '/');

echo $_COOKIE['name'];
?>



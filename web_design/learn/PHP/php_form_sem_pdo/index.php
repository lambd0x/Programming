<!DOCTYPE html>
<html>
<title>Formulario</title>
<header>
</header>


<body>
<?php
if(isset($_POST['acao'])){
	$nome = $_POST['nome'];
	$email = $_POST['email'];
	echo "<hr>$nome<br>$email<hr>";
}
?>
	<form method="post">
	<input type="text" name="nome" />
	<input type="text" name="email" />
	<input type="submit" name="acao" value="Enviar"/>
	</form>
	</body>

	</html>

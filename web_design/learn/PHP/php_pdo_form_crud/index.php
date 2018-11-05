<?php
date_default_timezone_set("America/Sao_Paulo");
$pdo = new PDO('mysql:host=localhost;dbname=modulo_8','root','');

if(isset($_POST['acao_inserir'])) {
	$nome = $_POST['nome'];
	$sobrenome = $_POST['sobrenome'];
	$momento_registro = date('Y-m-d H:i:s');
	$sql = $pdo->prepare("insert into `teste` values (null,?,?,?);");
	#Inserção de modo seguro / previne SQL injection
	if($sql->execute(array($nome,$sobrenome,$momento_registro))) {
		echo "Cliente inserido com sucesso";
	}
}

if(isset($_POST['acao_atualizar'])) {
	$nome_pesquisa = $_POST['nome_atualizar'];
	$nome_novo = $_POST['nome_novo'];
	$sql = $pdo->prepare("select * from `teste` where nome=?");
	if($sql->execute([$nome_pesquisa])) {
		// Acesso ao conteúdo via info[0];
		$info = $sql->fetch();
		$sql_update = $pdo->prepare("update `teste` SET nome=? where id=?;");
		if($sql_update->execute(array($nome_novo, $info[0]))) {
			echo "Tabela atualizada com $nome_novo";
		}
	}
}

if(isset($_POST['acao_remover'])) {
	$nome_remover = $_POST['nome_remover'];
	$sql = $pdo->prepare("delete from `teste` where nome=?;");
	if($sql->execute([$nome_remover])) {
		echo "$nome_remover foi removido";
	}
}
?>
<!DOCTYPE html>
<html>
	<title>Teste com cad em base MySQL</title>

	<header>
	</header>

	<body>
		<form method="post">
		<input type="text" name="nome" required />
		<input type="text" name="sobrenome" required />
		<input type="submit" name="acao_inserir" value="Inserir registro" />
	</form>
	<hr>
	<form method="post">
		Nome a ser atualizado:
		<input type="text" name="nome_atualizar" required />
		Nome novo:
		<input type="text" name="nome_novo" required />
		<input type="submit" name="acao_atualizar" value="Atualizar" />
	</form>
	<hr>
	<form method="post">
		Nome a ser removido:
		<input type="text" name="nome_remover" required />
		<input type="submit" name="acao_remover" value="Remover registro">
	</form>
	<hr>
	<br>
	</form>
	</body>

	<footer>
	</footer>
</html>

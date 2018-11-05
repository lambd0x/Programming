<?php
function mostrarNome($nome, $idade){
	echo "<h2>Nome eh $nome e tenho $idade anos</h2><br>";
}

function calculadora($num1 = 10,$num2 = 5){
	echo $num1+$num2;
}

function verdade(){
	return true;
}
/*
//mostrarNome("Nick", 23);
//calculadora();
$var = verdade();
echo $var . '<hr><br>';

// Define padrao de fuso horário
date_default_timezone_set('America/Sao_Paulo');

# Trabalhando com datas segundo o que trabalha-se no Brasil
$data = date('d/m/Y H:i:s');

echo $data;
 */
$nome_site = "Batatas poderosas!";
include('header.php');
?>

<h1> Conteudo da home</h1><br>

<?php
include('footer.php');
?>

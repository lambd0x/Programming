<?php
$variavel1 = "Joao";
$variavel2 = "Joao";
if($variavel1===$variavel2){
	echo '<div style="width:300px;height:300px;background:red;"></div>';
}else{
	echo 'A condicao nao bate<br>';
}

/*
#For
for($contador=0; $contador < 10; $contador++){
	echo "Hello world<hr>";
}

#While
$contador = 0;
while($contador < 10){
	echo "Hello world<hr>";
	$contador++;
}
echo "<br>"
 */

#Do while
$contador = 0;
do{
	echo "Hello world<br>";
	$contador++;
}while($contador<10);
?>

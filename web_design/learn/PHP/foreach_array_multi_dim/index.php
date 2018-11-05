<?php
#Foreach
$arr = array("Nick","Edu","Mario");
foreach($arr as $key => $value){
	echo "$key => $value<hr>";
}

#total do vetor
$total = count($arr);
echo $total;

# Arrays muldimensionais
$arrayMulti = array(array('Gui', 'Mer'), array(23,45));

echo "<br>";
echo $arrayMulti[0][0];
echo $arrayMulti[1][0];
?>

<?php

$Temperatura = $_GET['temp'];
$Humedad = $_GET['hum'];

echo "La Temperatura es: ".$Temperatura."<br>La Humedad es: ".$Humedad;

$usuario = "root";
$contrasena = "";
$servidor = "localhost";
$basededatos = "test";

$conexion = mysqli_connect( $servidor, $usuario, "" ) or die ("No se ha podido conectar al servidor de Base de dato");

$db = mysqli_select_db( $conexion, $basededatos) or die ("No se ha podido seleccionar la base de datos");

$fecha = time();

$consulta = "INSERT INTO iot_proyecto (Fecha, Temperatura, Humedad) VALUES ( ".$Fecha.",".$Temperatura.", ".$Humedad.")";

$resultado = mysqli_query( $conexion, $consulta);

?>

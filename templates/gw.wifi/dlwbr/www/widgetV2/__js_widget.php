<?
$salt = query("/runtime/widget/salt");
fwrite("/var/run/salt", $salt);
echo "<script>";
echo "var salt = \"".$salt."\";";
echo "</script>";
?>

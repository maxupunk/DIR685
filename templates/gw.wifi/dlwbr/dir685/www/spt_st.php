<?
/* vi: set sw=4 ts=4: ---------------------------------------------------------*/
$MY_NAME		="spt_st";
$MY_MSG_FILE	=$MY_NAME.".php";
$SPT_FILE_NAME	=$MY_NAME;
$CATEGORY		="spt";
/* --------------------------------------------------------------------------- */
$NO_SESSION_TIMEOUT=1;
//require("/www/locale/en/".$MY_NAME.".php"); 

//jana added: for multi-language
require("/www/model/__lang_msg.php"); 
require($LOCALE_PATH."/".$MY_NAME.".php"); 

$MY_TITLE		=$m_menu_top_st;
require("/www/model/__comm_spt.php");
?>

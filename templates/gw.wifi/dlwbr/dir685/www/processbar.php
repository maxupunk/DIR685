var result = <?

anchor("/runtime/scan_media");

$total_file		= query("total_file");
$total_scan_file		= query("total_scan_file");
$scan_done = query("/runtime/scan_media/scan_done");

?>new Array("<?=$total_file?>", "<?=$total_scan_file?>" , "<?=$scan_done?>");

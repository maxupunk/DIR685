<!-- === BEGIN SIDENAV === -->
<ul>
<?
$link_on="sidenavoff";

if($SUB_CATEGORY=="bsc_internet")
		{echo "<li><div id='".$link_on."'>".			$m_menu_bsc_internet.	"</div></li>\n";		}
else	{echo "<li><div><a href='/bsc_internet.php'>".	$m_menu_bsc_internet.	"</a></div></li>\n";	}

if($SUB_CATEGORY=="bsc_wlan")
		{echo "<li><div id='".$link_on."'>".			$m_menu_bsc_wlan.		"</div></li>\n";		}
else	{echo "<li><div><a href='/bsc_wlan_main.php'>".	$m_menu_bsc_wlan.		"</a></div></li>\n";	}

if($MY_NAME=="bsc_lan")
		{echo "<li><div id='".$link_on."'>".			$m_menu_bsc_lan.		"</div></li>\n";		}
else	{echo "<li><div><a href='/bsc_lan.php'>".		$m_menu_bsc_lan.		"</a></div></li>\n";	}

//+++jana
if($MY_NAME=="nas_lcd_setup")
		{echo "<li><div id='".$link_on."'>".				$m_menu_nas_lcd_setup.			"</div></li>\n";		}
else	{echo "<li><div><a href='/nas_lcd_setup.php'>".		$m_menu_nas_lcd_setup.			"</a></div></li>\n";	}
//---jana

?>
</ul>
<!-- === END SIDENAV === -->

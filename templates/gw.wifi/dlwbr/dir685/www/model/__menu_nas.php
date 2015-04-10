<!-- === BEGIN SIDENAV === -->
<ul>
<?
$link_on="sidenavoff";

if($MY_NAME=="nas_disk_management")
		{echo "<li><div id='".$link_on."'>".					$m_menu_nas_disk_management.			"</div></li>\n";		}
else	{echo "<li><div><a href='/nas_disk_management.php'>".	$m_menu_nas_disk_management.			"</a></div></li>\n";	}

/*if($MY_NAME=="nas_quota")
		{echo "<li><div id='".$link_on."'>".					$m_menu_nas_disk_management.			"</div></li>\n";		}
else	{echo "<li><div><a href='/nas_quota.php'>".	$m_menu_nas_disk_management.			"</a></div></li>\n";	}
*/
if($MY_NAME=="nas_user_group")
		{echo "<li><div id='".$link_on."'>".				$m_menu_nas_user_group.			"</div></li>\n";		}
else	{echo "<li><div><a href='/nas_user_group.php'>".	$m_menu_nas_user_group.			"</a></div></li>\n";	}

if($MY_NAME=="nas_nw_access")
		{echo "<li><div id='".$link_on."'>".				$m_menu_nas_nw_access.			"</div></li>\n";		}
else	{echo "<li><div><a href='/nas_nw_access.php'>".		$m_menu_nas_nw_access.			"</a></div></li>\n";	}

if($MY_NAME=="nas_ftp")
		{echo "<li><div id='".$link_on."'>".				$m_menu_nas_ftp.			"</div></li>\n";		}
else	{echo "<li><div><a href='/nas_ftp.php'>".			$m_menu_nas_ftp.			"</a></div></li>\n";	}

if($MY_NAME=="nas_upnp")
		{echo "<li><div id='".$link_on."'>".				$m_menu_nas_upnp.			"</div></li>\n";		}
else	{echo "<li><div><a href='/nas_upnp.php'>".			$m_menu_nas_upnp.			"</a></div></li>\n";	}

if($MY_NAME=="nas_iTunes")
		{echo "<li><div id='".$link_on."'>".				$m_menu_nas_iTunes.			"</div></li>\n";		}
else	{echo "<li><div><a href='/nas_iTunes.php'>".		$m_menu_nas_iTunes.			"</a></div></li>\n";	}

if($MY_NAME=="nas_bt")
		{echo "<li><div id='".$link_on."'>".				$m_menu_nas_bt.			"</div></li>\n";		}
else	{echo "<li><div><a href='/nas_bt.php'>".			$m_menu_nas_bt.			"</a></div></li>\n";	}

/*jana removed
if($MY_NAME=="nas_lcd_setup")
		{echo "<li><div id='".$link_on."'>".				$m_menu_nas_lcd_setup.			"</div></li>\n";		}
else	{echo "<li><div><a href='/nas_lcd_setup.php'>".		$m_menu_nas_lcd_setup.			"</a></div></li>\n";	}
*/
?>
</ul>
<!-- === END SIDENAV === -->

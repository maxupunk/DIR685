<!-- === BEGIN SIDENAV === -->
<ul>
<?
$link_on="sidenavoff";

if($MY_NAME=="spt_menu")
		{echo "<li><div id='".$link_on."'>".		$m_menu_spt_menu."</div></li>\n";		}
else	{echo "<li><div><a href='/spt_menu.php'>".	$m_menu_spt_menu."</a></div></li>\n";	}

if($MY_NAME=="spt_bsc")
		{echo "<li><div id='".$link_on."'>".		$m_menu_top_bsc."</div></li>\n";		}
else	{echo "<li><div><a href='/spt_bsc.php'>".	$m_menu_top_bsc."</a></div></li>\n";	}

if($MY_NAME=="spt_adv")
		{echo "<li><div id='".$link_on."'>".		$m_menu_top_adv."</div></li>\n";		}
else	{echo "<li><div><a href='/spt_adv.php'>".	$m_menu_top_adv."</a></div></li>\n";	}

if($MY_NAME=="spt_nas")
		{echo "<li><div id='".$link_on."'>".		$m_menu_top_storage."</div></li>\n";		}
else	{echo "<li><div><a href='/spt_nas.php'>".	$m_menu_top_storage."</a></div></li>\n";	}

if($MY_NAME=="spt_tools")
		{echo "<li><div id='".$link_on."'>".		$m_menu_top_tools."</div></li>\n";		}
else	{echo "<li><div><a href='/spt_tools.php'>".	$m_menu_top_tools."</a></div></li>\n";	}

if($MY_NAME=="spt_st")
		{echo "<li><div id='".$link_on."'>".		$m_menu_top_st."</div></li>\n";		}
else	{echo "<li><div><a href='/spt_st.php'>".	$m_menu_top_st."</a></div></li>\n";	}
?>
</ul>
<!-- === END SIDENAV === -->

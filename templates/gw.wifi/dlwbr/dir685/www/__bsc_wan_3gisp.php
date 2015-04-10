

var country = new Array(12);

var tw_fet = new Array("FarEasTone","","","*99#","internet");
var tw_cht = new Array("Chung Hwa Telecom","","","*99#","internet");
var tw_taiwan = new Array("Taiwan Mobile","","","*99#","internet");
var tw_vibo = new Array("Vibo","","","*99#","internet");
country[0] = new Array(2);
country[0][0] = "Taiwan";
country[0][1] = new Array(tw_fet,tw_cht,tw_taiwan,tw_vibo);

var sg_m1 = new Array("M1","","","*99***1#","sunsurf");
var sg_singtel = new Array("Singtel","","","*99***1#","e-ideas");
var sg_starthub = new Array("StarHub","","","*99***1#","");
var sg_powergrid = new Array("Power Grid","","","*99***1#","");
country[1] = new Array(2);
country[1][0] = "Singapore";
country[1][1] = new Array(sg_m1,sg_singtel,sg_starthub,sg_powergrid);

var id_im2 = new Array("IM2","","","*99#","indosatm2");
var id_indosat = new Array("INDOSAT","indodat","indosat","*99#","indosat3g");
var id_xl = new Array("XL","xlgprs","proxl","*99#","www.xlgprs.net");
var id_tel = new Array("Telkomsel Flash","","","*99#","flash");
country[2] = new Array(2);
country[2][0] = "indonesia";
country[2][1] = new Array(id_im2,id_indosat,id_xl,id_tel);

var ph_globe = new Array("Globe","","","*99***1#","internet.globe.com.ph");
country[3] = new Array(2);
country[3][0] = "Philippines";
country[3][1] = new Array(ph_globe);

var my_celcom = new Array("Celcom","","","*99***1#","celcom3g");
var my_maxis = new Array("Maxis","maxis","wap","*99***1#","unet");
var my_redtone = new Array("Red Tone","","","*99#","redtone");
var my_umobile = new Array("UMobile","","","*99#","my3g");
country[4] = new Array(2);
country[4][0] = "Malaysia";
country[4][1] = new Array(my_celcom,my_maxis,my_redtone,my_umobile);

var hk_smart = new Array("SmarTone-Vodafone","","","*99***1#","internet");
var hk_pccw = new Array("PCCW mobile","","","*99#","pccw");
var hk_three = new Array("3 Hong Kong","","","*99***1#","mobile.three.com.hk");
var hk_one2free = new Array("One2Free","","","*99***1#","internet");
country[5] = new Array(2);
country[5][0] = "Hong Kong";
country[5][1] = new Array(hk_smart,hk_pccw,hk_three,hk_one2free);

var za_mtn = new Array("MTN","","","","");
var za_vodacom = new Array("Vodacom","","","","");
country[6] = new Array(2);
country[6][0] = "South Africa";
country[6][1] = new Array(za_mtn,za_vodacom);

var dr_telmex = new Array("Telmex","claro","claro","*99#","internet.ideasclaro.com.do");
country[7] = new Array(2);
country[7][0] = "Dominican Republic";
country[7][1] = new Array(dr_telmex);

var sl_telmex = new Array("Telmex","","","*99#","internet.ideasclaro");
country[8] = new Array(2);
country[8][0] = "El Salvador";
country[8][1] = new Array(sl_telmex);

var au_telstra = new Array("Telstra","","","*99#","telstra.internet");
var au_optus = new Array("Optus","","","*99#","internet");
var au_bigpond = new Array("Bigpond","","","*99**#","telstra.bigpond");
var au_hutchison = new Array("Hutchison 3G","","","*99***1#","3netaccess");
var au_vodafone = new Array("Vodafone","","","*99***1#","vfinternet.au");
country[9] = new Array(2);
country[9][0] = "Australia";
country[9][1] = new Array(au_telstra,au_optus,au_bigpond,au_hutchison,au_vodafone);

var br_claro = new Array("Claro","claro","claro","*99***1#","bandalarga.claro.com.br");
country[10] = new Array(2);
country[10][0] = "Brasil";
country[10][1] = new Array(br_claro);

var mx_telcel = new Array("Telcel","webgprs","webgprs2002","*99#","Internet.itelcel.com");
country[11] = new Array(2);
country[11][0] = "Mexico";
country[11][1] = new Array(mx_telcel);


function init_country() {

var select_obj=document.getElementsByName("SearchCountry")[0];
for(i=select_obj.length;i>=1;i--)select_obj.remove(i);	
for(i=0;i<country.length;i++)
{ 
var option_obj=document.createElement("option");
option_obj.text=country[i][0];
option_obj.value=i;

if(i== <?=$cfg_wwan_country?>)
{
	option_obj.setAttribute('selected','selected');
}
try{ select_obj.add(option_obj,null); }catch(ex){ select_obj.add(option_obj);	}
}			

/*isp init*/
if(<?=$cfg_wwan_country?> != -1){
	var now=document.getElementsByName("SearchCountry")[0].value;
	var select_obj=document.getElementsByName("SearchISP")[0];
	for(i=select_obj.length;i>=1;i--)select_obj.remove(i);	
	var isplist=country[now][1];
	for(i=0;i<isplist.length;i++)
	{ 
		var option_obj=document.createElement("option");
		option_obj.text=isplist[i][0];
		option_obj.value=i;

		if(i== <?=$cfg_wwan_isp?>)
		{
			option_obj.setAttribute('selected','selected');
		}
	try{ select_obj.add(option_obj,null); }catch(ex){ select_obj.add(option_obj);	}
	}	
}
}
function change_country() {

var now=document.getElementsByName("SearchCountry")[0].value;

var select_obj=document.getElementsByName("SearchISP")[0];
for(i=select_obj.length;i>=1;i--)select_obj.remove(i);	
var isplist=country[now][1];
for(i=0;i<isplist.length;i++)
{ 
var option_obj=document.createElement("option");
option_obj.text=isplist[i][0];
option_obj.value=i;
try{ select_obj.add(option_obj,null); }catch(ex){ select_obj.add(option_obj);	}
}	
		
var f = get_obj("frm_wwan");
f.country.value=f.SearchCountry.value;

}

function change_isp() {

var now1=document.getElementsByName("SearchCountry")[0].value;
var now2=document.getElementsByName("SearchISP")[0].value;
var now=country[now1][1][now2];

///alert( "user="+now[1]+"\npass="+now[2]+"\ndialnum="+now[3]+"\nAPN="+now[4]);

var f = get_obj("frm_wwan");
f.username.value=now[1];
f.password.value=now[2];

/* mark vPassword for D-Link
f.password_v.value=now[2];
*/

f.dial_num.value=now[3];
f.apn.value		=now[4];

f.isp.value=f.SearchISP.value;
}



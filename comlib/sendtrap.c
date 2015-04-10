#include <stdlib.h> /*definition of NULL*/
#include <stdio.h> /*memory and string manupulation*/
#include <string.h> /* strncpy() */
#include <sendtrap.h>
#include <libxmldbc.h>
#include <../include/elbox_config.h>

#ifdef ELBOX_MODEL_DAP3520
struct specificTrap specificTrapTable[] =
{
    { 0, "1.3.6.1.4.1.171.10.37.35"},
    { 1, "1.3.6.1.4.1.171.10.37.35.5.7.1.1"},
    { 2, "1.3.6.1.4.1.171.10.37.35.5.7.1.2"},
    { 3, "1.3.6.1.4.1.171.10.37.35.5.7.1.3"},
    { 4, "1.3.6.1.4.1.171.10.37.35.5.7.1.4"},
    { 5, "1.3.6.1.4.1.171.10.37.35.5.7.1.5"},
    { 6, "1.3.6.1.4.1.171.10.37.35.5.7.1.6"},
    { 7, "1.3.6.1.4.1.171.10.37.35.5.7.1.7"},
    { 8, "1.3.6.1.4.1.171.10.37.35.5.7.1.8"},
    { 9, "1.3.6.1.4.1.171.10.37.35.5.7.1.9"},
    {10, "1.3.6.1.4.1.171.10.37.35.5.7.1.10"},
    {11, "1.3.6.1.4.1.171.10.37.35.5.7.1.11"},
    {12, "1.3.6.1.4.1.171.10.37.35.5.7.1.12"},
    {13, "1.3.6.1.4.1.171.10.37.35.5.7.1.13"},
    {14, "1.3.6.1.4.1.171.10.37.35.5.7.1.14"},
    {15, "1.3.6.1.4.1.171.10.37.35.5.7.1.15"}
};
#endif /*ELBOX_MODEL_DAP2553*/
#ifdef ELBOX_MODEL_DAP2553
struct specificTrap specificTrapTable[] =
{
    { 0, "1.3.6.1.4.1.171.10.37.35"},
    { 1, "1.3.6.1.4.1.171.10.37.35.5.7.1.1"},
    { 2, "1.3.6.1.4.1.171.10.37.35.5.7.1.2"},
    { 3, "1.3.6.1.4.1.171.10.37.35.5.7.1.3"},
    { 4, "1.3.6.1.4.1.171.10.37.35.5.7.1.4"},
    { 5, "1.3.6.1.4.1.171.10.37.35.5.7.1.5"},
    { 6, "1.3.6.1.4.1.171.10.37.35.5.7.1.6"},
    { 7, "1.3.6.1.4.1.171.10.37.35.5.7.1.7"},
    { 8, "1.3.6.1.4.1.171.10.37.35.5.7.1.8"},
    { 9, "1.3.6.1.4.1.171.10.37.35.5.7.1.9"},
    {10, "1.3.6.1.4.1.171.10.37.35.5.7.1.10"},
    {11, "1.3.6.1.4.1.171.10.37.35.5.7.1.11"},
    {12, "1.3.6.1.4.1.171.10.37.35.5.7.1.12"},
    {13, "1.3.6.1.4.1.171.10.37.35.5.7.1.13"},
    {14, "1.3.6.1.4.1.171.10.37.35.5.7.1.14"},
    {15, "1.3.6.1.4.1.171.10.37.35.5.7.1.15"}
};
#endif /*ELBOX_MODEL_DAP2553*/
#ifdef ELBOX_MODEL_DAP2590
struct specificTrap specificTrapTable[] =
{
    { 0, "1.3.6.1.4.1.171.10.37.36"},
    { 1, "1.3.6.1.4.1.171.10.37.36.5.7.2.1"},
    { 2, "1.3.6.1.4.1.171.10.37.36.5.7.2.2"},
    { 3, "1.3.6.1.4.1.171.10.37.36.5.7.2.3"},
    { 4, "1.3.6.1.4.1.171.10.37.36.5.7.2.4"},
    { 5, "1.3.6.1.4.1.171.10.37.36.5.7.2.5"},
    { 6, "1.3.6.1.4.1.171.10.37.36.5.7.2.6"},
    { 7, "1.3.6.1.4.1.171.10.37.36.5.7.2.7"},
    { 8, "1.3.6.1.4.1.171.10.37.36.5.7.2.8"},
    { 9, "1.3.6.1.4.1.171.10.37.36.5.7.2.9"},
    {10, "1.3.6.1.4.1.171.10.37.36.5.7.2.10"},
    {11, "1.3.6.1.4.1.171.10.37.36.5.7.2.11"},
    {12, "1.3.6.1.4.1.171.10.37.36.5.7.2.12"},
    {13, "1.3.6.1.4.1.171.10.37.36.5.7.2.13"},
    {14, "1.3.6.1.4.1.171.10.37.36.5.7.2.14"},
    {15, "1.3.6.1.4.1.171.10.37.36.5.7.2.15"}
};
#endif /*ELBOX_MODEL_DAP2590*/
#ifdef ELBOX_MODEL_DAP2690	/*joe, just copy table from above for make pass, maybe need be modified, 2008-11-06*/
struct specificTrap specificTrapTable[] =
{
    { 0, "1.3.6.1.4.1.171.10.37.36"},
    { 1, "1.3.6.1.4.1.171.10.37.36.5.7.1.1"},
    { 2, "1.3.6.1.4.1.171.10.37.36.5.7.1.2"},
    { 3, "1.3.6.1.4.1.171.10.37.36.5.7.1.3"},
	{ 4, "1.3.6.1.4.1.171.10.37.36.5.7.1.4"},
	{ 5, "1.3.6.1.4.1.171.10.37.36.5.7.1.5"},
	{ 6, "1.3.6.1.4.1.171.10.37.36.5.7.1.6"},
	{ 7, "1.3.6.1.4.1.171.10.37.36.5.7.1.7"},
	{ 8, "1.3.6.1.4.1.171.10.37.36.5.7.1.8"},
	{ 9, "1.3.6.1.4.1.171.10.37.36.5.7.1.9"},
	{10, "1.3.6.1.4.1.171.10.37.36.5.7.1.10"},
	{11, "1.3.6.1.4.1.171.10.37.36.5.7.1.11"},
	{12, "1.3.6.1.4.1.171.10.37.36.5.7.1.12"},
	{13, "1.3.6.1.4.1.171.10.37.36.5.7.1.13"},
	{14, "1.3.6.1.4.1.171.10.37.36.5.7.1.14"},
	{15, "1.3.6.1.4.1.171.10.37.36.5.7.1.15"}
};
#endif /*ELBOX_MODEL_DAP2690*/

#ifdef ELBOX_MODEL_DAP1353B
struct specificTrap specificTrapTable[] =
{
    { 0, "1.3.6.1.4.1.171.10.37.36"},
    { 1, "1.3.6.1.4.1.171.10.37.36.5.7.1.1"},
    { 2, "1.3.6.1.4.1.171.10.37.36.5.7.1.2"},
    { 3, "1.3.6.1.4.1.171.10.37.36.5.7.1.3"},
	{ 4, "1.3.6.1.4.1.171.10.37.36.5.7.1.4"},
	{ 5, "1.3.6.1.4.1.171.10.37.36.5.7.1.5"},
	{ 6, "1.3.6.1.4.1.171.10.37.36.5.7.1.6"},
	{ 7, "1.3.6.1.4.1.171.10.37.36.5.7.1.7"},
	{ 8, "1.3.6.1.4.1.171.10.37.36.5.7.1.8"},
	{ 9, "1.3.6.1.4.1.171.10.37.36.5.7.1.9"},
	{10, "1.3.6.1.4.1.171.10.37.36.5.7.1.10"},
	{11, "1.3.6.1.4.1.171.10.37.36.5.7.1.11"},
	{12, "1.3.6.1.4.1.171.10.37.36.5.7.1.12"},
	{13, "1.3.6.1.4.1.171.10.37.36.5.7.1.13"},
	{14, "1.3.6.1.4.1.171.10.37.36.5.7.1.14"},
	{15, "1.3.6.1.4.1.171.10.37.36.5.7.1.15"}
};
#endif /*ELBOX_MODEL_DAP1353B*/

void sendtrap(unsigned char* cmd){

    int trap, host=1;
    unsigned char *entOID = "1.3.6.1.4.1.171";
    unsigned char buff[30], host_buff[30], comm_buff[30], sec_buff[30], cmd_buff[100];

    memset(buff, 0x0, 30);
    xmldbc_get_wb(NULL, 0, "/sys/snmptrap/status" , buff, 29);
    trap = atoi(buff);
    /*Send out trap*/
    if(trap==1){
        if (strncmp(cmd, "[SNMP-TRAP]", 11)==0){
            cmd+=11;
            /*Generic trap*/
            if(strncmp(cmd, "[Generic=", 9)==0){
                cmd+=9;
                trap=atoi(cmd);

                /*Go through host table*/
                host=1;
                while(host<=10/*MAX_EPMADDR_ENTRIES*/){
                    /*Get host IP*/
                    memset(buff, 0x0, 30);
                    sprintf(buff, "%s%d", "/sys/snmpd/hostip:", host);
                    memset(host_buff, 0x0, 30);
                    xmldbc_get_wb(NULL, 0, buff, host_buff, 29);

                    if(strlen(host_buff)){
                        /*Get SNMP Version*/
                        memset(buff, 0x0, 30);
                        sprintf(buff, "%s%d", "/sys/snmpd/secumodel:", host);
                        memset(sec_buff, 0x0, 30);
                        xmldbc_get_wb(NULL, 0, buff, sec_buff, 29);
                        
                        /*SNMP v1*/
                        if(memcmp(sec_buff, "1", 1)==0){
                            memset(buff, 0x0, 30);
                            sprintf(buff, "%s%d", "/sys/snmpd/commorun:", host);
                            memset(comm_buff, 0x0, 30);
                            xmldbc_get_wb(NULL, 0, buff, comm_buff, 29);
                            memset(cmd_buff, 0x0, 100);
                            sprintf(cmd_buff, "snmptrap -v 1 -c %s %s %s \"\" %d 0 \"\"", comm_buff, host_buff, entOID, trap);
							/* eric fu, 2009/03/02, stdout&stderr to /dev/null */
							strcat(cmd_buff," 1>/dev/null 2>&1 ");
                            system(cmd_buff);
                        }else
                        /*SNMP v2c*/
                        if(memcmp(sec_buff, "2", 1)==0){
                        }else
                        /*SNMP v3*/
                        if(memcmp(sec_buff, "3", 1)==0){
                        }
                        host++;
                    }else{
                        host=11;
                    }
                }
            }else
            /*Specific trap*/
            if (strncmp(cmd, "[Specific=", 10)==0){
                cmd+=10;
                trap=atoi(cmd);
                /*Go through host table*/
                host=1;
                while(host<=10/*MAX_EPMADDR_ENTRIES*/){
                    /*Get host IP*/
                    memset(buff, 0x0, 30);
                    sprintf(buff, "%s%d", "/sys/snmpd/hostip:", host);
                    memset(host_buff, 0x0, 30);
                    xmldbc_get_wb(NULL, 0, buff, host_buff, 29);

                    if(strlen(host_buff)){
                        /*Get SNMP Version*/
                        memset(buff, 0x0, 30);
                        sprintf(buff, "%s%d", "/sys/snmpd/secumodel:", host);
                        memset(sec_buff, 0x0, 30);
                        xmldbc_get_wb(NULL, 0, buff, sec_buff, 29);
                        
                        /*SNMP v1*/
                        if(memcmp(sec_buff, "1", 1)==0){
                            memset(buff, 0x0, 30);
                            sprintf(buff, "%s%d", "/sys/snmpd/commorun:", host);
                            memset(comm_buff, 0x0, 30);
                            xmldbc_get_wb(NULL, 0, buff, comm_buff, 29);
                            memset(cmd_buff, 0x0, 100);
//                            sprintf(cmd_buff, "snmptrap -v 1 -c %s %s %s \"\" 6 %d \"\"", comm_buff, host_buff, entOID, trap);//paley for device send the wrong trap OID
                            sprintf(cmd_buff, "snmptrap -v 1 -c %s %s %s \"\" 6 %d \"\"", comm_buff, host_buff, specificTrapTable[trap].trapOID, trap);
							/* eric fu, 2009/03/02, stdout&stderr to /dev/null */
							strcat(cmd_buff," 1>/dev/null 2>&1 ");
                            system(cmd_buff);
                        }else
                        /*SNMP v2c*/
                        if(memcmp(sec_buff, "2", 1)==0){
                            memset(buff, 0x0, 30);
                            sprintf(buff, "%s%d", "/sys/snmpd/commorun:", host);
                            memset(comm_buff, 0x0, 30);
                            xmldbc_get_wb(NULL, 0, buff, comm_buff, 29);
                            memset(cmd_buff, 0x0, 100);
                            sprintf(cmd_buff, "snmptrap -v 2c -c %s %s \"\" %s", comm_buff, host_buff, specificTrapTable[trap].trapOID);
							/* eric fu, 2009/03/02, stdout&stderr to /dev/null */
							strcat(cmd_buff," 1>/dev/null 2>&1 ");
                            system(cmd_buff);
                        }else
                        /*SNMP v3*/
                        if(memcmp(sec_buff, "3", 1)==0){
                        }
                        host++;
                    }else{
                        host=11;
                    }
                }
            }
        }else{
            return;
        }
    }else{
        return;
    }
}



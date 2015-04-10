#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli_cfg.h"

int cli_show_all_commands(CLICMD_T *cmd);
CLICMD_T *cli_find_command(char *name, CLICMD_T *cmd);
static int nat_help_cmd(int argc, char ** argv);
static int nat_set_cmd(int argc, char ** argv);
static int nat_show_cmd(int argc, char ** argv);
static int nat_add_cmd(int argc, char ** argv);
static int nat_del_cmd(int argc, char ** argv);
int nat_del_help_cmd(int argc, char ** argv);
int nat_set_help_cmd(int argc, char ** argv);
int nat_show_help_cmd(int argc, char ** argv);
int nat_add_help_cmd(int argc, char ** argv);

CLICMD_T nat_main_cmds[] = {
    {"?",       nat_help_cmd,      "Help commands"},
    {"add",     nat_add_cmd,       "Add commands"},
    {"del",     nat_del_cmd,       "Del commands"},
    {"help",    nat_help_cmd,      "Help commands"},
    {"set",     nat_set_cmd,       "Set commands"},
    {"show",    nat_show_cmd,      "Show commands"},
    {0,0,0}
};

extern CLICMD_T nat_set_cmds[];
extern CLICMD_T nat_show_cmds[];
extern CLICMD_T nat_add_cmds[];
extern CLICMD_T nat_del_cmds[];

/*----------------------------------------------------------------------
* ROUTINE NAME - cli_show_all_commands
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : LICMD_T *cmd: points the first command table
* OUTPUT     : 0: SUCCESS 1:FAILED    
*----------------------------------------------------------------------*/
int cli_show_all_commands(CLICMD_T *cmd)
{

    fprintf(stderr,"[Command List]\n");

    while (cmd->name)
    {
        fprintf(stderr,"%s --- %s\n",cmd->name, cmd->help_msg);
        cmd++;
    }
    return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - cli_find_command
*-----------------------------------------------------------------------
* DESCRIPTION: Find the command in command table
* INPUT      : char *name
*              CLICMD_T *cmd
* OUTPUT     : CLICMD_T *cmd 
*              0: command is not found
*----------------------------------------------------------------------*/
CLICMD_T *cli_find_command(char *name, CLICMD_T *cmd)
{
    int i, total, len=strlen(name);
    CLICMD_T *me=NULL, *exact;
    
    exact=(CLICMD_T *)0;
    total=0;
    while (cmd->name)
    {
        char *srce=name;
        char *dest=cmd->name;
        for (i=0; i<len; i++)
        {
            if (tolower(*dest)!=tolower(*srce)) break;
            dest++; srce++;
        }
        if (i==len)
        {
            if (i==strlen(cmd->name))
                exact=cmd;
            total++;       
            me=cmd;
        }    
        cmd++;
    }
    
    if (total>1)
    {
        return((CLICMD_T *)exact);   // duplicate
    }        
    if (total==1)
        return(me);
    else    
        return((CLICMD_T *)0);
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_help_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED      
*----------------------------------------------------------------------*/
static int nat_help_cmd( int argc, char ** argv)
{
    cli_show_all_commands((CLICMD_T *)&nat_main_cmds[0]);
    return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_set_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED     
*----------------------------------------------------------------------*/
int nat_set_cmd(int argc, char **argv)
{
    CLICMD_T *cmd;
    int ret=-1;
    
    if (argc > 1)
    {
        cmd=cli_find_command(argv[1], (CLICMD_T *)&nat_set_cmds[0]);
        if (cmd && cmd->action)
           ret= cmd->action(argc-1,&argv[1]); // skip set argument
        else
           fprintf(stderr,"[%s] Command is not found!\n",argv[1]);
    }
    else
        nat_set_help_cmd(argc-1,&argv[1]);    // skip set argument

	return ret ;

    
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_set_help_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED 
*----------------------------------------------------------------------*/
int nat_set_help_cmd( int argc, char ** argv)
{
    cli_show_all_commands((CLICMD_T *)&nat_set_cmds[0]);
    return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_show_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED 
*----------------------------------------------------------------------*/
int nat_show_cmd(int argc, char **argv)
{
    CLICMD_T *cmd;
    int ret=-1;
    
    if (argc > 1)
    {
        cmd=cli_find_command(argv[1], (CLICMD_T *)&nat_show_cmds[0]);
        if (cmd && cmd->action)
          ret = cmd->action(argc-1,&argv[1]); // skip show argument
        else
           fprintf(stderr,"[%s] Command is not found!\n",argv[1]);
    }
    else
        nat_show_help_cmd(argc-1,&argv[1]);    // skip show argument

    return ret;

}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_show_help_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED  
*----------------------------------------------------------------------*/
int nat_show_help_cmd( int argc, char ** argv)
{
    cli_show_all_commands((CLICMD_T *)&nat_show_cmds[0]);
    return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_add_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED  
*----------------------------------------------------------------------*/
int nat_add_cmd(int argc, char **argv)
{
    CLICMD_T *cmd;
    int ret=-1;
    
    if (argc > 1)
    {
        cmd=cli_find_command(argv[1], (CLICMD_T *)&nat_add_cmds[0]);
        if (cmd && cmd->action)
            ret = cmd->action(argc-1,&argv[1]); // skip add argument
        else
           fprintf(stderr,"[%s] Command is not found!\n",argv[1]);
    }
    else
        nat_add_help_cmd(argc-1,&argv[1]);    // skip add argument
        

	return ret;

}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_add_help_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED 
*----------------------------------------------------------------------*/
int nat_add_help_cmd( int argc, char ** argv)
{
    cli_show_all_commands((CLICMD_T *)&nat_add_cmds[0]);

    return 0;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_del_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED   
*----------------------------------------------------------------------*/
int nat_del_cmd(int argc, char **argv)
{
    CLICMD_T *cmd;
    int ret =-1;
    
    if (argc > 1)
    {
        cmd=cli_find_command(argv[1], (CLICMD_T *)&nat_del_cmds[0]);
        if (cmd && cmd->action)
           ret = cmd->action(argc-1,&argv[1]); // skip del argument
        else
           fprintf(stderr,"[%s] Command is not found!\n",argv[1]);
    }
    else
        nat_del_help_cmd(argc-1,&argv[1]);    // skip del argument
	
	return ret;
}

/*----------------------------------------------------------------------
* ROUTINE NAME - nat_add_help_cmd
*-----------------------------------------------------------------------
* DESCRIPTION: 
* INPUT      : int argc, char ** argv
* OUTPUT     : 0: SUCCESS 1:FAILED 
*----------------------------------------------------------------------*/
int nat_del_help_cmd( int argc, char ** argv)
{
    cli_show_all_commands((CLICMD_T *)&nat_del_cmds[0]);
    return 0;
}


int main(int argc, char **argv)
{
	CLICMD_T *cmd;
	int ret=-1;

	if (argc == 1)
		cli_show_all_commands((CLICMD_T *)&nat_main_cmds[0]);
	else
	{
		cmd = cli_find_command(argv[1],(CLICMD_T *)&nat_main_cmds[0]);
		if (cmd)
		{
			ret =cmd->action(argc-1, &argv[1]);
		}
		else
            fprintf(stderr,"[%s] Command is not found!\n",argv[1]);
	}
	return ret;
}

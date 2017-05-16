
#ifndef SXCONCMD_H
#define SXCONCMD_H

#include "sxcore.h"
#include <common/AssotiativeArray.h>

#define CONSOLE_PORT "59705" /*!< ����������� ���� ��� ����������� ������� */
#define COMMAND_PORT "59706" /*!< ����������� ���� ��� ������ */

enum ConCmdType
{
	CMD_DEFAULT = 0,
	CMD_ARG,
	CMD_CLS,
	CMD_CLS_ARG
};

struct ConCmd
{
	ConCmdType type;
	ConCmdStub * cls;
	union
	{
		void * cmd;
		SXCONCMDCLS clscmd;
		SXCONCMDCLSARG clscmdarg;
	} cmd;
	char * szDesc;
};

void ConsoleRegisterCmds();

#endif

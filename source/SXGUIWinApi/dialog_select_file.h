
#ifndef __DIALOG_SELECT_FILE_H
#define __DIALOG_SELECT_FILE_H

#include "sxgui.h"
#include <common/file_utils.h>


//! ������ ������ ������� ������ ����������
#define DIALOG_OWN_SELFILE_WIDTH		735

//! ������ ������ ������� ������ ����������
#define DIALOG_OWN_SELFILE_HEIGHT	450

#define DIALOG_OWN_SELFILE_PREVIEW_SIZE	256


//! ������������� ������ ������� ������ �����
void DialogOwnSelectFileInit();

//! ������ ������ ������� ������ �����
bool DialogOwnSelectFileRun(char *szOutName, char *szOutPath, const char *szStartPath, const char *szFilterExt, const char *szDialogName = 0, bool canExplore = true, const char *szDownPath = 0, HWND hWndLock = 0, HandlerDialogOwndGetPreview2 lpfnHandlerPreview = 0, HandlerDialogOwndGetInfo lpfnHandlerInfo = 0);


#endif
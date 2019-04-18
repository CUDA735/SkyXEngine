#ifndef _GUIMAIN_H_
#define _GUIMAIN_H_

#include <graphix/graphix.h>
#include <Windows.h>
#include <common/array.h>
#include <common/MemAlloc.h>
#include <common/stack.h>
#include <common/assotiativearray.h>
#include <common/string.h>
#include <common/Math.h>

#include "IFont.h"

#ifndef GUI_DLL
#	include "IDesktop.h"
#endif

namespace gui
{
	class IEvent;
	class IDesktop;
	typedef void(*GUI_CALLBACK)(IEvent * ev);
	typedef void(*GUI_CALLBACK_WC)(const WCHAR * cb_name, IEvent * ev);

	class IGUI
	{
	public:
		virtual ~IGUI()
		{
		}


		//############################
		//#      ������� ������      #
		//############################

		/** ��������� �����
			���������� �� ����� ��������� ��������� ����
		*/
		virtual BOOL putMessage(UINT msg, WPARAM wParam, LPARAM lParam) = 0;

		/**	����������
			�������� ���������� �� �����
		*/
		virtual void update() = 0;

		/**	�������������
			������ ���� ������� � ���� ������������� �������
		*/
		virtual void syncronize() = 0;

		/**	���������
			������ ���� ������� ������ � ��������� ������ �������
		*/
		virtual void render() = 0;

		/** ��������� ������ ����������
			
		*/
		virtual void onResetDevice() = 0;
		virtual void onLostDevice() = 0;


		/** �����������

		*/
		virtual void release() = 0;



		//############################
		//#        ������ GUI        #
		//############################

		//�������� Desktop'�
		virtual IDesktop * createDesktopA(const char * name, const char * file) = 0;
		virtual IDesktop * createDesktopW(const WCHAR * name, const WCHAR * file) = 0;

		//��������� ��������� Desktop'�
		virtual void setActiveDesktop(IDesktop * d, BOOL clearStack=TRUE) = 0;
		virtual void setActiveDesktopA(const char * name) = 0;
		virtual void setActiveDesktopW(const WCHAR * name) = 0;

		//�������� ������� �������� Desktop
		virtual IDesktop * getActiveDesktop() = 0;

		//�������� Desktop �� �����
		virtual IDesktop * getDesktopA(const char * name) = 0;
		virtual IDesktop * getDesktopW(const WCHAR * name) = 0;

		//����������� �����������
		virtual void registerCallback(const char * cbName, GUI_CALLBACK cb) = 0;

		//����������� ����������� �� ���������
		virtual void registerCallbackDefault(GUI_CALLBACK_WC cb, BOOL greedy = FALSE) = 0;

		virtual GUI_CALLBACK getCallbackByName(const char * cbName) = 0;
		virtual GUI_CALLBACK getCallbackByName(const StringW & cbName) = 0;


		virtual void messageBox(const WCHAR * title, const WCHAR * text, ...) = 0;
		virtual void pushDesktop(IDesktop *) = 0;
		virtual IDesktop * popDesktop() = 0;

		virtual const SMMATRIX &getTransformViewProj() = 0;

		virtual IFont *getFont(const WCHAR * szName, UINT size, IFont::STYLE style, int iBlurRadius) = 0;
	};

	typedef IGUI*(*PFNINITINSTANCE)(IGXContext*, const char*, HWND);
};

#ifdef SX_STATIC_BUILD
gui::IGUI * GUI_InitInstance(IGXContext * pDev, const char * szResPath, HWND hWnd);
#endif

#endif

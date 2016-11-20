#ifndef _GUIMAIN_H_
#define _GUIMAIN_H_

#include <d3d9.h>
#include <Windows.h>
#include <core/array.h>
#include <core/memalloc.h>
#include <core/stack.h>
#include <core/assotiativearray.h>
#include <string/string.h>
#include <SXMath.h>

#ifndef GUI_DLL
#	include "IDesktop.h"
#endif

#ifdef MessageBox
#undef MessageBox
#endif

namespace GUI
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
		virtual BOOL PutMessage(UINT msg, WPARAM wParam, LPARAM lParam) = 0;

		/**	����������
			�������� ���������� �� �����
		*/
		virtual void Update() = 0;

		/**	�������������
			������ ���� ������� � ���� ������������� �������
		*/
		virtual void Syncronize() = 0;

		/**	���������
			������ ���� ������� ������ � ��������� ������ �������
		*/
		virtual void Render() = 0;

		/** ��������� ������ ����������
			
		*/
		virtual void OnResetDevice() = 0;
		virtual void OnLostDevice() = 0;


		/** �����������

		*/
		virtual void Release() = 0;



		//############################
		//#        ������ GUI        #
		//############################

		//�������� Desktop'�
		virtual IDesktop * CreateDesktopA(const char * name, const char * file) = 0;
		virtual IDesktop * CreateDesktopW(const WCHAR * name, const WCHAR * file) = 0;

		//��������� ��������� Desktop'�
		virtual void SetActiveDesktop(IDesktop * d, BOOL clearStack=TRUE) = 0;
		virtual void SetActiveDesktopA(const char * name) = 0;
		virtual void SetActiveDesktopW(const WCHAR * name) = 0;

		//�������� ������� �������� Desktop
		virtual IDesktop * GetActiveDesktop() = 0;

		//�������� Desktop �� �����
		virtual IDesktop * GetDesktopA(const char * name) = 0;
		virtual IDesktop * GetDesktopW(const WCHAR * name) = 0;

		//����������� �����������
		virtual void RegisterCallback(const char * cbName, GUI_CALLBACK cb) = 0;

		//����������� ����������� �� ���������
		virtual void RegisterCallbackDefault(GUI_CALLBACK_WC cb, BOOL greedy = FALSE) = 0;

		virtual GUI_CALLBACK GetCallbackByName(const char * cbName) = 0;
		virtual GUI_CALLBACK GetCallbackByName(const StringW & cbName) = 0;


		virtual void MessageBox(const WCHAR * title, const WCHAR * text, ...) = 0;
		virtual void PushDesktop(IDesktop *) = 0;
		virtual IDesktop * PopDesktop() = 0;
	};

	typedef IGUI*(*PFNINITINSTANCE)(IDirect3DDevice9*, const char*, HWND);
};

#endif

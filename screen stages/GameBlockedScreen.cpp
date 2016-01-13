/****************************************************************************
**
** GameBlockedGump.cpp
**
** Copyright (C) September 2015 Hotride
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
*****************************************************************************
*/
//---------------------------------------------------------------------------
#include "stdafx.h"

TGameBlockedScreen *GameBlockedScreen = NULL;
//---------------------------------------------------------------------------
TGameBlockedScreen::TGameBlockedScreen()
: TBaseScreen(), m_Code(0)
{
}
//---------------------------------------------------------------------------
TGameBlockedScreen::~TGameBlockedScreen()
{
}
//---------------------------------------------------------------------------
void TGameBlockedScreen::Init()
{
	m_Code = 0;
}
//---------------------------------------------------------------------------
int TGameBlockedScreen::Render(bool mode)
{
	if (mode)
	{
		GumpManager->Draw(mode, true);
		
		InitTooltip();

		MouseManager.Draw(0x2073); //Main Gump mouse cursor
	}
	else
	{
		g_LastSelectedObject = 0;
		g_LastObjectType = SOT_NO_OBJECT;
		g_LastSelectedGump = 0;
		
		GumpManager->Draw(mode, true);

		return g_LastSelectedObject;
	}

	return 0;
}
//---------------------------------------------------------------------------
void TGameBlockedScreen::OnLeftMouseDown()
{
	g_LastSelectedGump = 0;

	Render(false);

	if (g_LastSelectedGump)
		GumpManager->OnLeftMouseDown(true);
}
//---------------------------------------------------------------------------
void TGameBlockedScreen::OnLeftMouseUp()
{
	Render(false);

	if (g_LeftMouseDown && g_LastGumpLeftMouseDown)
		GumpManager->OnLeftMouseUp(true);
}
//---------------------------------------------------------------------------
void TGameBlockedScreen::OnCharPress(WPARAM wparam, LPARAM lparam)
{
	if (EntryPointer == NULL || EntryPointer == GameConsole)
		return;

	GumpManager->OnCharPress(wparam, lparam, true);
}
//---------------------------------------------------------------------------
void TGameBlockedScreen::OnKeyPress(WPARAM wparam, LPARAM lparam)
{
	TGumpNotify *notify = (TGumpNotify*)GumpManager->GetGump(0,0, GT_NOTIFY);

	if (EntryPointer == NULL || EntryPointer == GameConsole)
	{
		if (wparam == VK_RETURN && notify != NULL)
			notify->OnKeyPress(wparam, lparam);
	}
	else
	{
		TGump *gump = GumpManager->GetTextEntryOwner();

		if (gump != NULL && gump->GumpType == GT_TEXT_ENTRY_DIALOG)
			gump->OnKeyPress(wparam, lparam);
		else if (notify != NULL)
			notify->OnKeyPress(wparam, lparam);
	}
}
//---------------------------------------------------------------------------

void GCActivateAllElems(bool bf)
{
	SXLevelEditor::StaticName->Visible(bf);
	SXLevelEditor::EditName->Visible(bf);
	SXLevelEditor::EditName->SetText("");

	SXLevelEditor::StaticModel->Visible(bf);
	SXLevelEditor::EditModel->Visible(bf);
	SXLevelEditor::EditModel->SetText("");
	SXLevelEditor::ButtonModel->Visible(bf);

	SXLevelEditor::StaticLod1->Visible(bf);
	SXLevelEditor::EditLod1->Visible(bf);
	SXLevelEditor::EditLod1->SetText("");
	SXLevelEditor::ButtonLod1->Visible(bf);
	
	SXLevelEditor::StaticLod2->Visible(bf);
	SXLevelEditor::EditLod2->Visible(bf);
	SXLevelEditor::EditLod2->SetText("");
	SXLevelEditor::ButtonLod2->Visible(bf);

	SXLevelEditor::StaticMask->Visible(bf);
	SXLevelEditor::EditMask->Visible(bf);
	SXLevelEditor::EditMask->SetText("");
	SXLevelEditor::ButtonMask->Visible(bf);

	SXLevelEditor::ButtonGenerate->Visible(bf);

	SXLevelEditor::TrackBarDensity->Visible(bf);
	SXLevelEditor::TrackBarDensity->SetPos(0);

	SXLevelEditor::StaticDensityVal->Visible(bf);
	SXLevelEditor::StaticDensityText->Visible(bf);
}

void GCActivateCreatingElems(bool bf)
{
	SXLevelEditor::StaticMask->Enable(bf);
	SXLevelEditor::EditMask->Enable(bf);
	SXLevelEditor::ButtonMask->Enable(bf);

	SXLevelEditor::ButtonGenerate->Visible(bf);

	SXLevelEditor::TrackBarDensity->Visible(bf);
	SXLevelEditor::TrackBarDensity->SetPos(0);

	SXLevelEditor::StaticDensityVal->Visible(bf);
	SXLevelEditor::StaticDensityText->Visible(bf);
}

void GCInitElemsSelModel(int sel)
{
	if (sel >= 0 && sel < GData::StaticGreen->GetCountGreen())
	{
		GCActivateCreatingElems(false);

		SXLevelEditor::EditModel->SetText(GData::StaticGreen->GetGreenModel(sel));
		SXLevelEditor::EditLod1->SetText((GData::StaticGreen->GetGreenLod1(sel) ? GData::StaticGreen->GetGreenLod1(sel) : ""));
		SXLevelEditor::EditLod2->SetText((GData::StaticGreen->GetGreenLod2(sel) ? GData::StaticGreen->GetGreenLod2(sel) : ""));
		SXLevelEditor::EditMask->SetText(GData::StaticGreen->GetGreenMask(sel));
		SXLevelEditor::EditName->SetText(GData::StaticGreen->GetGreenName(sel));
	}
}



LRESULT SXLevelEditor_TrackBarDensity_MouseMove(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char freqstr[64];
	int pos = SXLevelEditor::TrackBarDensity->GetPos();
	sprintf(freqstr, "%d%", pos * 10);
	SXLevelEditor::StaticDensityVal->SetText(freqstr);
	return 0;
}

LRESULT SXLevelEditor_ButtonLod2_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char tmppath[1024];
	tmppath[0] = 0;
	char tmpname[1024];
	DialogLoadMesh(tmppath);
	if (def_str_validate(tmppath))
	{
		StrCutMesh(tmppath, tmpname);
		SXLevelEditor::EditLod2->SetText(tmpname);
		if (SXLevelEditor::HowActivateType == 2)
		{
			int sel = SXLevelEditor::ListBoxList->GetSel();
			//GData::Geometry->SetModelLodPath(sel, tmppath);
		}
	}
	return 0;
}

LRESULT SXLevelEditor_ButtonMask_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char tmppath[1024];
	tmppath[0] = 0;
	char tmpname[1024];
	DialogSelectTexture(tmppath);
	if (def_str_validate(tmppath))
	{
		StrCutName(tmppath, tmpname);
		SXLevelEditor::EditMask->SetText(tmpname);
	}
	return 0;
}

LRESULT SXLevelEditor_ButtonGenerate_Click(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (GData::Geometry->GetCountModel() == 0)
	{
		MessageBox(0, "���������� ������� ��������� ������, � ������ ����� ���� ��������� ��������������!", "��� �������", 0);
		return 0;
	}

	char tmp_name[1024];
	tmp_name[0] = 0;
	char path_tex[1024];
	path_tex[0] = 0;
	char path_model[1024];
	path_model[0] = 0;
	char path_lod1[1024];
	path_lod1[0] = 0;
	char path_lod2[1024];
	path_lod2[0] = 0;

	char tmp_tex[1024];
	tmp_tex[0] = 0;
	char tmp_model[1024];
	tmp_model[0] = 0;
	char tmp_lod1[1024];
	tmp_lod1[0] = 0;
	char tmp_lod2[1024];
	tmp_lod2[0] = 0;

	int greentype = GREEN_TYPE_TREE;

	SXLevelEditor::EditName->GetText(tmp_name, 1024);
	SXLevelEditor::EditMask->GetText(tmp_tex, 1024);
	SXLevelEditor::EditModel->GetText(tmp_model, 1024);
	SXLevelEditor::EditLod1->GetText(tmp_lod1, 1024);
	SXLevelEditor::EditLod2->GetText(tmp_lod2, 1024);

	if (tmp_lod1[0] == 0 && tmp_lod2[0] == 0)
		greentype = GREEN_TYPE_GRASS;

	if (tmp_tex[0] != 0)
		sprintf(path_tex,"%s%s",GData::Pathes::Textures,tmp_tex);

	if (tmp_model[0] != 0)
		sprintf(path_model, "%s%s", GData::Pathes::Meshes, tmp_model);

	if (tmp_lod1[0] != 0)
		sprintf(path_lod1, "%s%s", GData::Pathes::Meshes, tmp_lod1);

	if (tmp_lod2[0] != 0)
		sprintf(path_lod2, "%s%s", GData::Pathes::Meshes, tmp_lod2);
	
	/*if (!Core_0FileExists(path_tex))
	{
		char tmpstr[2048];
		sprintf(tmpstr, "%s%s%s", "�������� [", path_tex, "] �� ����������");
		MessageBox(0, tmpstr, 0, 0);
		return 0;
	}*/

	if (!Core_0FileExists(path_model))
	{
		char tmpstr[2048];
		sprintf(tmpstr, "%s%s%s", "������ [", path_model, "] �� ����������");
		MessageBox(0, tmpstr, 0, 0);
		return 0;
	}

	if (greentype == GREEN_TYPE_TREE)
	{
		if (!Core_0FileExists(path_lod1))
		{
			char tmpstr[2048];
			sprintf(tmpstr, "%s%s%s", "������ [", path_lod1, "] �� ����������");
			MessageBox(0, tmpstr, 0, 0);
			return 0;
		}

		if (!Core_0FileExists(path_lod2))
		{
			char tmpstr[2048];
			sprintf(tmpstr, "%s%s%s", "������ [", path_lod2, "] �� ����������");
			MessageBox(0, tmpstr, 0, 0);
			return 0;
		}
	}

	if (!def_str_validate(tmp_name))
	{
		if (MessageBox(0, "��� ����� � ������, ������ ��� ����� �������������?", 0, MB_YESNO | MB_ICONWARNING | MB_TASKMODAL) == IDYES)
		{
			for (int i = 0; i<strlen(path_model); i++)
			{
				if (path_model[strlen(path_model) - i] == '\\')
				{
					sprintf(tmp_name, "%s", path_model + strlen(path_model) - (i - 1));
					break;
				}
			}
		}
		else
			return 0;
	}

	float pos = SXLevelEditor::TrackBarDensity->GetPos();

	GData::StaticGreen->Init(GData::Geometry, tmp_name,
		tmp_tex,
		pos,
		tmp_model,
		(tmp_lod1[0] ? tmp_lod1 : 0),
		(tmp_lod2[0] ? tmp_lod2 : 0),
		50);

	char tmpnamecountpoly[1024];
		sprintf(tmpnamecountpoly, "%s | %s | %d",
			GData::StaticGreen->GetGreenName(GData::StaticGreen->GetCountGreen()-1),
			(GData::StaticGreen->GetGreenTypeCountGen(GData::StaticGreen->GetCountGreen() - 1) == GREEN_TYPE_GRASS ? "grass" : "tree/shrub"),
			GData::StaticGreen->GetGreenCountGen(GData::StaticGreen->GetCountGreen() - 1));
		SXLevelEditor::ListBoxList->AddItem(tmpnamecountpoly);

	GCActivateCreatingElems(false);
	SXLevelEditor::ListBoxList->SetSel(SXLevelEditor::ListBoxList->GetCountItem() - 1);
	SXLevelEditor::HowActivateType = 2;

	GCInitElemsSelModel(SXLevelEditor::ListBoxList->GetCountItem() - 1);

	return 0;
}
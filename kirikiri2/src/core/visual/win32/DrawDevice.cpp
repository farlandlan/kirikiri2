//---------------------------------------------------------------------------
/*
	TVP2 ( T Visual Presenter 2 )  A script authoring tool
	Copyright (C) 2000-2007 W.Dee <dee@kikyou.info> and contributors

	See details of license at "license.txt"
*/
//---------------------------------------------------------------------------
//!@file �`��f�o�C�X�Ǘ�
//---------------------------------------------------------------------------

#include "tjsCommHead.h"
#include "DrawDevice.h"
#include "LayerIntf.h"


//---------------------------------------------------------------------------
tTVPDrawDevice::tTVPDrawDevice()
{
	// �R���X�g���N�^
	PrimaryLayerManagerIndex = 0;
	DestRect.clear();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
tTVPDrawDevice::~tTVPDrawDevice()
{
	// ���ׂĂ� managers ���J������
	for(std::vector<tTVPLayerManager *>::iterator i = Managers.begin(); i != Managers.end(); i++)
		(*i)->Release();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
bool tTVPDrawDevice::TransformToPrimaryLayerManager(tjs_int &x, tjs_int &y)
{
	tTVPLayerManager * manager = GetLayerManagerAt(PrimaryLayerManagerIndex);
	if(!manager) return false;

	// �v���C�}�����C���}�l�[�W���̃v���C�}�����C���̃T�C�Y�𓾂�
	tjs_int pl_w, pl_h;
	if(!manager->GetPrimaryLayerSize(pl_w, pl_h)) return false;

	// x , y �� DestRect �� 0, 0 �����_�Ƃ������W�Ƃ��ēn����Ă��Ă���
	x = x * pl_w / DestRect.get_width();
	y = y * pl_h / DestRect.get_height();

	return true;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPDrawDevice::Destruct()
{
	delete this;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPDrawDevice::SetDestRectangle(const tTVPRect & rect)
{
	DestRect = rect;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPDrawDevice::OnClick(tjs_int x, tjs_int y)
{
	if(!TransformToPrimaryLayerManager(x, y)) return;
	tTVPLayerManager * manager = GetLayerManagerAt(PrimaryLayerManagerIndex);
	if(!manager) return;

	manager->NotifyClick(x, y);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPDrawDevice::OnDoubleClick(tjs_int x, tjs_int y)
{
	if(!TransformToPrimaryLayerManager(x, y)) return;
	tTVPLayerManager * manager = GetLayerManagerAt(PrimaryLayerManagerIndex);
	if(!manager) return;

	manager->NotifyDoubleClick(x, y);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPDrawDevice::OnMouseDown(tjs_int x, tjs_int y, tTVPMouseButton mb, tjs_uint32 flags)
{
	if(!TransformToPrimaryLayerManager(x, y)) return;
	tTVPLayerManager * manager = GetLayerManagerAt(PrimaryLayerManagerIndex);
	if(!manager) return;

	manager->NotifyDoubleClick(x, y);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPDrawDevice::OnMouseUp(tjs_int x, tjs_int y, tTVPMouseButton mb, tjs_uint32 flags)
{
	if(!TransformToPrimaryLayerManager(x, y)) return;
	tTVPLayerManager * manager = GetLayerManagerAt(PrimaryLayerManagerIndex);
	if(!manager) return;

	manager->NotifyMouseUp(x, y, mb, flags);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPDrawDevice::OnMouseMove(tjs_int x, tjs_int y, tjs_uint32 flags)
{
	if(!TransformToPrimaryLayerManager(x, y)) return;
	tTVPLayerManager * manager = GetLayerManagerAt(PrimaryLayerManagerIndex);
	if(!manager) return;

	manager->NotifyMouseMove(x, y, flags);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPDrawDevice::OnReleaseCapture()
{
	tTVPLayerManager * manager = GetLayerManagerAt(PrimaryLayerManagerIndex);
	if(!manager) return;

	manager->ReleaseCapture();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPDrawDevice::OnMouseOutOfWindow()
{
	tTVPLayerManager * manager = GetLayerManagerAt(PrimaryLayerManagerIndex);
	if(!manager) return;

	manager->NotifyMouseOutOfWindow();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPDrawDevice::OnKeyDown(tjs_uint key, tjs_uint32 shift)
{
	tTVPLayerManager * manager = GetLayerManagerAt(PrimaryLayerManagerIndex);
	if(!manager) return;

	manager->NotifyKeyDown(key, shift);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPDrawDevice::OnKeyUp(tjs_uint key, tjs_uint32 shift)
{
	tTVPLayerManager * manager = GetLayerManagerAt(PrimaryLayerManagerIndex);
	if(!manager) return;

	manager->NotifyKeyUp(key, shift);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPDrawDevice::OnKeyPress(tjs_char key)
{
	tTVPLayerManager * manager = GetLayerManagerAt(PrimaryLayerManagerIndex);
	if(!manager) return;

	manager->NotifyKeyPress(key);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPDrawDevice::OnMouseWheel(tjs_uint32 shift, tjs_int delta, tjs_int x, tjs_int y)
{
	if(!TransformToPrimaryLayerManager(x, y)) return;
	tTVPLayerManager * manager = GetLayerManagerAt(PrimaryLayerManagerIndex);
	if(!manager) return;

	manager->NotifyMouseWheel(shift, delta, x, y);
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void TJS_INTF_METHOD tTVPDrawDevice::AddLayerManager(tTVPLayerManager * manager)
{
	// Managers �� manager �� push ����BAddRef����̂�Y��Ȃ����ƁB
	Managers.push_back(manager);
	manager->AddRef();
}
//---------------------------------------------------------------------------

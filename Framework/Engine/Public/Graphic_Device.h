#pragma once

#include "Base.h"

/* DirectX SDK���� �������ִ� �پ��� �Լ��� ����� �̿��ϱ����� �ʱ�ȭ�ϴ� ����. */
/* �ʱ�ȭ�� �� ���ƴٶ�� IDirect3DDevice9 => LPDIRECT3DDEVICE9�� ���ؼ� �������� �Լ��� ȣ���� �����س����� �ȴ�. */

BEGIN(Engine)

class CGraphic_Device : public CBase
{
private:
	explicit CGraphic_Device();
	virtual ~CGraphic_Device() = default;

public:
	HRESULT			Ready_GraphicDev(HWND hWnd, WINMODE eMode, const int iSizeX, const int iSizeY, LPDIRECT3DDEVICE9* ppOut);
	
	void			Render_Begin(D3DXCOLOR Color);
	void			Render_End(HWND hWnd = 0);
		
private:
	void			Set_Parameters(D3DPRESENT_PARAMETERS& d3dpp, HWND hWnd, WINMODE eMode, const int iSizeX, const int iSizeY);

private:
	LPDIRECT3D9				m_pSDK;
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	LPD3DXSPRITE			m_pSprite;

public:
	static CGraphic_Device* Create(HWND hWnd, WINMODE eMode, const int iSizeX, const int iSizeY, LPDIRECT3DDEVICE9* ppOut);
	virtual void	Free();

};

END
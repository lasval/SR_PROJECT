#pragma once

#include "Base.h"

BEGIN(Engine)

class CFont_Manager final : public CBase
{
private:
	CFont_Manager(LPDIRECT3DDEVICE9 pGraphic_Device);
	~CFont_Manager() = default;

public:
    HRESULT Add_Font_FromFile(
        const _wstring& strTag,
        const _wstring& strFontPath,
        const _wstring& strFontName,
        int iFontSize);

    void Render_Text(const _wstring& strTag,
        const _wstring& strText,
        const RECT& rc,
        D3DCOLOR color,
        DWORD dwFormat = DT_LEFT | DT_TOP);

private:
    unordered_map<_wstring, ID3DXFont*> m_mFont;
    vector<_wstring>                    m_vLoadedFontPaths;
    LPDIRECT3DDEVICE9			        m_pGraphic_Device = { nullptr };

public:
	static CFont_Manager* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual void Free() override;


};

END
#pragma once

#include "Base.h"

BEGIN(Engine)

class CFont_Manager final : public CBase
{
private:
    CFont_Manager();
    virtual ~CFont_Manager() = default;

public:
    HRESULT Ready_Font(LPDIRECT3DDEVICE9 pGraphicDev,
        const _wstring& strFontTag,
        const _wstring& strFontPath,
        const _wstring& strFontName,
        const _uint& iWidth,
        const _uint& iHeight,
        const _uint& iWeight);

    void Render_Font(const wstring& strFontTag,
        const _wstring& strText,
        const _float2* pVec2Pos,
        D3DXCOLOR d3dxColor,
        DWORD dwFormat = DT_NOCLIP);

private:
    class CFont* Find_Font(const wstring& strFontTag);
    map<wstring, class CFont*> m_mapFont;

public:
    static CFont_Manager* Create();
    virtual void Free() override;
};

END

#include "Font_Manager.h"

CFont_Manager::CFont_Manager(LPDIRECT3DDEVICE9 pGraphic_Device)
    : m_pGraphic_Device{ pGraphic_Device }
{
}

HRESULT CFont_Manager::Add_Font_FromFile(const _wstring& strTag, const _wstring& strFontPath, const _wstring& strFontName, int iFontSize)
{
    // 이미 등록된 태그인지 확인
    if (m_mFont.find(strTag) != m_mFont.end())
        return S_OK; // 중복 등록 방지

    // 시스템에 폰트 등록 (임시, 비공개)
    if (AddFontResourceEx(strFontPath.c_str(), FR_PRIVATE, 0) == 0)
        return E_FAIL;

    D3DXFONT_DESC desc{};
    desc.Height = iFontSize;
    wcscpy_s(desc.FaceName, strFontName.c_str());
    desc.Weight = FW_NORMAL;
    desc.CharSet = DEFAULT_CHARSET;
    desc.OutputPrecision = OUT_DEFAULT_PRECIS;
    desc.Quality = DEFAULT_QUALITY;
    desc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;

    ID3DXFont* pFont = nullptr;
    if (FAILED(D3DXCreateFontIndirect(m_pGraphic_Device, &desc, &pFont)))
        return E_FAIL;

    m_mFont[strTag] = pFont;
    m_vLoadedFontPaths.push_back(strFontPath); // 나중에 해제용

    return S_OK;
}

void CFont_Manager::Render_Text(const _wstring& strTag, const _wstring& strText, const RECT& rc, D3DCOLOR color, DWORD dwFormat)
{
    auto it = m_mFont.find(strTag);
    if (it != m_mFont.end() && it->second)
        it->second->DrawTextW(nullptr, strText.c_str(), -1, const_cast<RECT*>(&rc), dwFormat, color);
}

CFont_Manager* CFont_Manager::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
    return new CFont_Manager(pGraphic_Device);
}

void CFont_Manager::Free()
{
    __super::Free();
    for (auto& font : m_mFont)
    {
        Safe_Release(font.second);
    }
    m_mFont.clear();
    m_vLoadedFontPaths.clear();
    Safe_Release(m_pGraphic_Device);
}

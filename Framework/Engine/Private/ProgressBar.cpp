#include "ProgressBar.h"
#include "GameInstance.h"

CProgressBar::CProgressBar(LPDIRECT3DDEVICE9 pGraphic_Device) : CComponent(pGraphic_Device)
{
}

CProgressBar::CProgressBar(const CProgressBar& Prototype) : CComponent(Prototype)
{
}

HRESULT CProgressBar::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CProgressBar::Initialize(void* pArg)
{
	return S_OK;
}

HRESULT CProgressBar::Setting_Componets(class CTransform* pTransform, const _uint iCulNumber, const _uint iMaxNumber)
{
	if (pTransform == nullptr)
	{
		MSG_BOX(TEXT("Failed to Setting : CProgressBar"));
		return E_FAIL;
	}
	m_pTransformCom = pTransform;
	Safe_AddRef(m_pTransformCom);

	m_iCulNumber = iCulNumber;
	m_iPreNumber = m_iCulNumber;
	m_iMaxNumber = iMaxNumber;

	return S_OK;
}

CProgressBar* CProgressBar::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CProgressBar* pInstance = new CProgressBar(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Create : CProgressBar"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent* CProgressBar::Clone(void* pArg)
{
	CProgressBar* pInstance = new CProgressBar(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Clone : CProgressBar"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CProgressBar::Free()
{
	__super::Free();
	Safe_Release(m_pTransformCom);
}

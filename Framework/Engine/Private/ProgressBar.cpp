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
	if (nullptr == pArg)
		return E_FAIL;
	PROGRESSBAR_DESC* pDesc = static_cast<PROGRESSBAR_DESC*>(pArg);

	m_iMaxValue = pDesc->iMaxValue;
	m_iCulValue = pDesc->iCulValue;

	m_pTransformCom = pDesc->pTransformCom;
	Safe_AddRef(m_pTransformCom);

	return S_OK;
}

void CProgressBar::Progress_UpdateX(_uint iCulValue, const _float3 vOriginPos, const _float3 vOriginSize)
{
	m_iCulValue = iCulValue;
	if (m_iPreValue != m_iCulValue)
	{
		
		_float fRatio{};

		if (m_iCulValue >= m_iMaxValue)
		{
			m_iCulValue = m_iMaxValue;
			fRatio = m_iMaxValue / m_iCulValue;
		}
		else if (m_iCulValue <= 0)
		{
			m_iCulValue = 0;
			fRatio = m_iMaxValue / 0.1;
		}
		else
		{
			fRatio = m_iMaxValue / m_iCulValue;
		}
		_float fOffsetX = (1.f - fRatio) * vOriginPos.x * 0.5f;

		m_pTransformCom->Scaling(vOriginSize.x * fRatio, vOriginSize.y, vOriginSize.z);
		m_pTransformCom->Set_State(STATE::POSITION, _float3{ vOriginPos.x + fOffsetX, vOriginPos.y, vOriginPos.z });

		m_iPreValue = m_iCulValue;
	}
}

void CProgressBar::MaxValue_UpdateX(_uint iMaxValue, const _float3 vOriginPos, const _float3 vOriginSize)
{
	if (m_iMaxValue == iMaxValue)
	{
		m_iMaxValue == iMaxValue;
		_float fRatio = m_iMaxValue / m_iCulValue;
		m_pTransformCom->Scaling(vOriginPos.x * fRatio, vOriginPos.y, vOriginPos.z);

		_float fOffsetX = (1.f - fRatio) * vOriginPos.x * 0.5f;
		m_pTransformCom->Set_State(STATE::POSITION, _float3{ fOffsetX, vOriginPos.y, vOriginPos.z });
	}
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

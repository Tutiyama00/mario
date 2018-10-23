#pragma once

#include"RenderObj.h"
#include<vector>

template<class T> class Characters : public RenderObj
{
public:
	Characters(ID3D11Device* pDevice, const wchar_t* pTextureFileName, LPCWSTR pVSFileName, LPCWSTR pPSFileName);
	~Characters();

	//---RenderObj---
	void ThisObjRender(ID3D11DeviceContext* pDeviceContext, UINT strides, UINT offsets);
	void ThisObjCreateBuffer(ID3D11Device* pDevice);

public:
	std::vector<T*> m_ObjectVector;

private:
	void SetVertexIndex();
	void UpdateVIBuffer(ID3D11DeviceContext* pDeviceContext);
	void ClearVArray();

	//---RenderObj---
	void Abstract();

private:
	vertex*                   m_pVertexArray    = nullptr;
	UINT                      m_VertexArraySize = 0;
	WORD*                     m_pIndexArray     = nullptr;
	UINT                      m_IndexArraySize  = 0;
};
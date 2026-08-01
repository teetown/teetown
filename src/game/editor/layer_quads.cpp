/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include "editor.h"

#include <base/color.h>
#include <base/math.h>

#include <engine/console.h>
#include <engine/graphics.h>

#include <generated/client_data.h>

#include <game/client/localization.h>
#include <game/client/render.h>

CLayerQuads::CLayerQuads()
{
	m_Type = LAYERTYPE_QUADS;
	str_copy(m_aName, "Quads", sizeof(m_aName));
	m_Image = -1;
}

CLayerQuads::~CLayerQuads()
{
}

void CLayerQuads::Render()
{
	Graphics()->TextureClear();
	if(m_Image >= 0 && m_Image < (int)m_pEditor->m_Map.m_vImages.size())
		Graphics()->TextureSet(m_pEditor->m_Map.m_vImages[m_Image]->m_Texture);

	//Graphics()->BlendNone();
	//m_pEditor->RenderTools()->RenderQuads(m_lQuads.base_ptr(), m_lQuads.size(), LAYERRENDERFLAG_OPAQUE, m_pEditor->EnvelopeEval, m_pEditor);
	Graphics()->BlendNormal();
	m_pEditor->RenderTools()->RenderQuads(m_vQuads.data(), (int)m_vQuads.size(), LAYERRENDERFLAG_TRANSPARENT, m_pEditor->EnvelopeEval, m_pEditor);
}

CQuad *CLayerQuads::NewQuad()
{
	m_pEditor->m_Map.m_Modified = true;

	CQuad NewQuad;

	NewQuad.m_PosEnv = -1;
	NewQuad.m_ColorEnv = -1;
	NewQuad.m_PosEnvOffset = 0;
	NewQuad.m_ColorEnvOffset = 0;
	int x = 0, y = 0;
	NewQuad.m_aPoints[0].x = i2fx(x);
	NewQuad.m_aPoints[0].y = i2fx(y);
	NewQuad.m_aPoints[1].x = i2fx(x + 64);
	NewQuad.m_aPoints[1].y = i2fx(y);
	NewQuad.m_aPoints[2].x = i2fx(x);
	NewQuad.m_aPoints[2].y = i2fx(y + 64);
	NewQuad.m_aPoints[3].x = i2fx(x + 64);
	NewQuad.m_aPoints[3].y = i2fx(y + 64);

	NewQuad.m_aPoints[4].x = i2fx(x + 32); // pivot
	NewQuad.m_aPoints[4].y = i2fx(y + 32);

	NewQuad.m_aTexcoords[0].x = i2fx(0);
	NewQuad.m_aTexcoords[0].y = i2fx(0);

	NewQuad.m_aTexcoords[1].x = i2fx(1);
	NewQuad.m_aTexcoords[1].y = i2fx(0);

	NewQuad.m_aTexcoords[2].x = i2fx(0);
	NewQuad.m_aTexcoords[2].y = i2fx(1);

	NewQuad.m_aTexcoords[3].x = i2fx(1);
	NewQuad.m_aTexcoords[3].y = i2fx(1);

	NewQuad.m_aColors[0].r = 255;
	NewQuad.m_aColors[0].g = 255;
	NewQuad.m_aColors[0].b = 255;
	NewQuad.m_aColors[0].a = 255;
	NewQuad.m_aColors[1].r = 255;
	NewQuad.m_aColors[1].g = 255;
	NewQuad.m_aColors[1].b = 255;
	NewQuad.m_aColors[1].a = 255;
	NewQuad.m_aColors[2].r = 255;
	NewQuad.m_aColors[2].g = 255;
	NewQuad.m_aColors[2].b = 255;
	NewQuad.m_aColors[2].a = 255;
	NewQuad.m_aColors[3].r = 255;
	NewQuad.m_aColors[3].g = 255;
	NewQuad.m_aColors[3].b = 255;
	NewQuad.m_aColors[3].a = 255;

	m_vQuads.push_back(NewQuad);

	return &m_vQuads.back();
}

void CLayerQuads::BrushSelecting(CUIRect Rect)
{
	// draw selection rectangle
	vec4 RectColor = HexToRgba(m_pEditor->Config()->m_EdColorSelectionQuad);
	IGraphics::CLineItem Array[4] = {
		IGraphics::CLineItem(Rect.x, Rect.y, Rect.x + Rect.w, Rect.y),
		IGraphics::CLineItem(Rect.x + Rect.w, Rect.y, Rect.x + Rect.w, Rect.y + Rect.h),
		IGraphics::CLineItem(Rect.x + Rect.w, Rect.y + Rect.h, Rect.x, Rect.y + Rect.h),
		IGraphics::CLineItem(Rect.x, Rect.y + Rect.h, Rect.x, Rect.y)};
	Graphics()->TextureClear();
	Graphics()->LinesBegin();
	Graphics()->SetColor(RectColor.r * RectColor.a, RectColor.g * RectColor.a, RectColor.b * RectColor.a, RectColor.a);
	Graphics()->LinesDraw(Array, 4);
	Graphics()->LinesEnd();
}

int CLayerQuads::BrushGrab(CLayerGroup *pBrush, CUIRect Rect)
{
	// create new layers
	CLayerQuads *pGrabbed = new CLayerQuads();
	pGrabbed->m_pEditor = m_pEditor;
	pGrabbed->m_Image = m_Image;
	pBrush->AddLayer(pGrabbed);

	//dbg_msg("", "%f %f %f %f", rect.x, rect.y, rect.w, rect.h);
	for(const CQuad &Quad : m_vQuads)
	{
		float px = fx2f(Quad.m_aPoints[4].x);
		float py = fx2f(Quad.m_aPoints[4].y);

		if(px > Rect.x && px < Rect.x + Rect.w && py > Rect.y && py < Rect.y + Rect.h)
		{
			CQuad n;
			n = Quad;

			for(int p = 0; p < 5; p++)
			{
				n.m_aPoints[p].x -= f2fx(Rect.x);
				n.m_aPoints[p].y -= f2fx(Rect.y);
			}

			pGrabbed->m_vQuads.push_back(n);
		}
	}

	return pGrabbed->m_vQuads.empty() ? 0 : 1;
}

void CLayerQuads::BrushPlace(CLayer *pBrush, float wx, float wy)
{
	CLayerQuads *l = (CLayerQuads *)pBrush;
	for(const CQuad &Quad : l->m_vQuads)
	{
		CQuad n = Quad;

		for(int p = 0; p < 5; p++)
		{
			n.m_aPoints[p].x += f2fx(wx);
			n.m_aPoints[p].y += f2fx(wy);
		}

		m_vQuads.push_back(n);
	}
	m_pEditor->m_Map.m_Modified = true;
}

void CLayerQuads::BrushFlipX()
{
}

void CLayerQuads::BrushFlipY()
{
}

void Rotate(vec2 *pCenter, vec2 *pPoint, float Rotation)
{
	float x = pPoint->x - pCenter->x;
	float y = pPoint->y - pCenter->y;
	pPoint->x = x * cosf(Rotation) - y * sinf(Rotation) + pCenter->x;
	pPoint->y = x * sinf(Rotation) + y * cosf(Rotation) + pCenter->y;
}

void CLayerQuads::BrushRotate(float Amount)
{
	vec2 Center;
	GetSize(&Center.x, &Center.y);
	Center.x /= 2;
	Center.y /= 2;

	for(CQuad &Quad : m_vQuads)
	{
		for(int p = 0; p < 5; p++)
		{
			vec2 Pos(fx2f(Quad.m_aPoints[p].x), fx2f(Quad.m_aPoints[p].y));
			Rotate(&Center, &Pos, Amount);
			Quad.m_aPoints[p].x = f2fx(Pos.x);
			Quad.m_aPoints[p].y = f2fx(Pos.y);
		}
	}
}

void CLayerQuads::GetSize(float *w, float *h) const
{
	*w = 0;
	*h = 0;

	for(const CQuad &Quad : m_vQuads)
	{
		for(int p = 0; p < 5; p++)
		{
			*w = maximum(*w, fx2f(Quad.m_aPoints[p].x));
			*h = maximum(*h, fx2f(Quad.m_aPoints[p].y));
		}
	}
}

int CLayerQuads::RenderProperties(CUIRect *pToolBox)
{
	// layer props
	enum
	{
		PROP_IMAGE = 0,
		NUM_PROPS,
	};

	CProperty aProps[] = {
		{"Image", m_Image, PROPTYPE_IMAGE, -1, 0},
		{0},
	};

	static int s_aIds[NUM_PROPS] = {0};
	int NewVal = 0;
	int Prop = m_pEditor->DoProperties(pToolBox, aProps, s_aIds, &NewVal);
	if(Prop != -1)
		m_pEditor->m_Map.m_Modified = true;

	if(Prop == PROP_IMAGE)
	{
		if(NewVal >= 0)
			m_Image = NewVal % (int)m_pEditor->m_Map.m_vImages.size();
		else
			m_Image = -1;
	}

	return 0;
}

void CLayerQuads::ModifyImageIndex(INDEX_MODIFY_FUNC Func)
{
	Func(&m_Image);
}

void CLayerQuads::ModifyEnvelopeIndex(INDEX_MODIFY_FUNC Func)
{
	for(CQuad &Quad : m_vQuads)
	{
		Func(&Quad.m_PosEnv);
		Func(&Quad.m_ColorEnv);
	}
}

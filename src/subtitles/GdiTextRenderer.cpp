
/************************************************************************
 *
 * File: GdiTextRenderer.cpp
 *
 * Description: 
 * 
 * 
 *  This file is part of the Microsoft Windows SDK Code Samples.
 * 
 *  Copyright (C) Microsoft Corporation.  All rights reserved.
 * 
 * This source code is intended only as a supplement to Microsoft
 * Development Tools and/or on-line documentation.  See these other
 * materials for detailed information regarding Microsoft code samples.
 * 
 * THIS CODE AND INFORMATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 * 
 ************************************************************************/

#include "stdafx.h"
#include "GdiTextRenderer.h"

/******************************************************************
*                                                                 *
*  GdiTextRenderer::GdiTextRenderer                               *
*                                                                 *
*  The constructor stores render target and the rendering params. *
*                                                                 *
******************************************************************/

GdiTextRenderer::GdiTextRenderer(
    IDWriteFactory* dw_factory
    )
:
cRefCount_(0), 
_dw_factory(dw_factory)
{
    _dw_factory->AddRef();
}

/******************************************************************
*                                                                 *
*  GdiTextRenderer::GdiTextRenderer                               *
*                                                                 *
*  Destructor releases the interfaces passed when the class was   *
*  created.                                                       *
*                                                                 *
******************************************************************/

GdiTextRenderer::~GdiTextRenderer()
{
    SafeRelease(&_dw_factory);
}


/******************************************************************
*                                                                 *
*  GdiTextRenderer::DrawGlyphRun                                  *
*                                                                 *
*  Gets GlyphRun outlines via IDWriteFontFace::GetGlyphRunOutline *
*  and then draws and fills them using Direct2D path geometries   *
*                                                                 *
******************************************************************/
STDMETHODIMP GdiTextRenderer::DrawGlyphRun(
    __maybenull void* clientDrawingContext,
    FLOAT baselineOriginX,
    FLOAT baselineOriginY,
    DWRITE_MEASURING_MODE measuringMode,
    __in DWRITE_GLYPH_RUN const* glyphRun,
    __in DWRITE_GLYPH_RUN_DESCRIPTION const* glyphRunDescription,
    IUnknown* clientDrawingEffect
    )
{
    HRESULT hr;
    IDWriteFontCollection* font_coll = NULL;
    IDWriteFont** font = (IDWriteFont**)clientDrawingContext;

    hr = this->_dw_factory->GetSystemFontCollection(&font_coll, FALSE);
    if (FAILED(hr))
        return E_FAIL;

    hr = font_coll->GetFontFromFontFace(glyphRun->fontFace, font);
    if (FAILED(hr))
        return E_FAIL;

    return S_OK;
}

/******************************************************************
*                                                                 *
*  GdiTextRenderer::DrawUnderline                                 *
*                                                                 *
*  This function is not implemented for the purposes of this      *
*  sample.                                                        *
*                                                                 *
******************************************************************/

STDMETHODIMP GdiTextRenderer::DrawUnderline(
    __maybenull void* clientDrawingContext,
    FLOAT baselineOriginX,
    FLOAT baselineOriginY,
    __in DWRITE_UNDERLINE const* underline,
    IUnknown* clientDrawingEffect
    )
{
    return S_OK;
}

/******************************************************************
*                                                                 *
*  GdiTextRenderer::DrawStrikethrough                             *
*                                                                 *
*  This function is not implemented for the purposes of this      *
*  sample.                                                        *
*                                                                 *
******************************************************************/

STDMETHODIMP GdiTextRenderer::DrawStrikethrough(
    __maybenull void* clientDrawingContext,
    FLOAT baselineOriginX,
    FLOAT baselineOriginY,
    __in DWRITE_STRIKETHROUGH const* strikethrough,
    IUnknown* clientDrawingEffect
    )
{
    return S_OK;
}

/******************************************************************
*                                                                 *
*  GdiTextRenderer::DrawInlineObject                              *
*                                                                 *
*  This function is not implemented for the purposes of this      *
*  sample.                                                        *
*                                                                 *
******************************************************************/

STDMETHODIMP GdiTextRenderer::DrawInlineObject(
    __maybenull void* clientDrawingContext,
    FLOAT originX,
    FLOAT originY,
    IDWriteInlineObject* inlineObject,
    BOOL isSideways,
    BOOL isRightToLeft,
    IUnknown* clientDrawingEffect
    )
{
    return S_OK;
}

/******************************************************************
*                                                                 *
*  GdiTextRenderer::AddRef                                        *
*                                                                 *
*  Increments the ref count                                       *
*                                                                 *
******************************************************************/

STDMETHODIMP_(unsigned long) GdiTextRenderer::AddRef()
{
    return InterlockedIncrement(&cRefCount_);
}

/******************************************************************
*                                                                 *
*  GdiTextRenderer::Release                                       *
*                                                                 *
*  Decrements the ref count and deletes the instance if the ref   *
*  count becomes 0                                                *
*                                                                 *
******************************************************************/

STDMETHODIMP_(unsigned long) GdiTextRenderer::Release()
{
    long newCount = InterlockedDecrement(&cRefCount_);

    if (newCount == 0)
    {
        delete this;
        return 0;
    }
    return newCount;
}

/******************************************************************
*                                                                 *
*  GdiTextRenderer::IsPixelSnappingDisabled                       *
*                                                                 *
*  Determines whether pixel snapping is disabled. The recommended *
*  default is FALSE, unless doing animation that requires         *
*  subpixel vertical placement.                                   *
*                                                                 *
******************************************************************/

STDMETHODIMP GdiTextRenderer::IsPixelSnappingDisabled(
    __maybenull void* clientDrawingContext,
    __out BOOL* isDisabled
    )
{
    *isDisabled = FALSE;
    return S_OK;
}

/******************************************************************
*                                                                 *
*  GdiTextRenderer::GetCurrentTransform                           *
*                                                                 *
*  Returns the current transform applied to the render target..   *
*                                                                 *
******************************************************************/

STDMETHODIMP GdiTextRenderer::GetCurrentTransform(
    __maybenull void* clientDrawingContext,
    __out DWRITE_MATRIX* transform
    )
{
    return S_OK;
}

/******************************************************************
*                                                                 *
*  GdiTextRenderer::GetPixelsPerDip                               *
*                                                                 *
*  This returns the number of pixels per DIP.                     *
*                                                                 *
******************************************************************/

STDMETHODIMP GdiTextRenderer::GetPixelsPerDip(
    __maybenull void* clientDrawingContext,
    __out FLOAT* pixelsPerDip
    )
{
    return S_OK;
}

/******************************************************************
*                                                                 *
*  GdiTextRenderer::QueryInterface                                *
*                                                                 *
*  Query interface implementation                                 *
*                                                                 *
******************************************************************/

STDMETHODIMP GdiTextRenderer::QueryInterface(
    IID const& riid,
    void** ppvObject
    )
{
    if (__uuidof(IDWriteTextRenderer) == riid
        || __uuidof(IDWritePixelSnapping) == riid
        || __uuidof(IUnknown) == riid) {
        *ppvObject = this;
    }
    else {
        *ppvObject = NULL;
        return E_FAIL;
    }

    AddRef();
    return S_OK;
}


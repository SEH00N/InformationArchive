#include "pch.h"
#include "SelectGDI.h"
#include "Core.h"

SelectGDI::SelectGDI(HDC dc, PenType ePen)
    : hDC(dc)
    , hDefaultBrush(nullptr)
    , hDefaultPen(nullptr)
    , hDefaultFont(nullptr)
    , hFont(nullptr)
{
    HPEN hColorPen = Core::GetInstance()->GetPen(ePen);
    hDefaultPen = (HPEN)SelectObject(dc, hColorPen);
}
SelectGDI::SelectGDI(HDC dc, BrushType eBrush)
    : hDC(dc)
    , hDefaultBrush(nullptr)
    , hDefaultPen(nullptr)
    , hDefaultFont(nullptr)
    , hFont(nullptr)
{
    HBRUSH hColorBrush = Core::GetInstance()->GetBrush(eBrush);
    hDefaultBrush = (HBRUSH)SelectObject(dc, hColorBrush);
}
SelectGDI::SelectGDI(HDC dc, HFONT font)
    : hDC(dc)
    , hDefaultBrush(nullptr)
    , hDefaultPen(nullptr)
    , hDefaultFont(nullptr)
    , hFont(nullptr)
{
    hFont = font;
    hDefaultFont = (HFONT)SelectObject(dc, hFont);
}
SelectGDI::~SelectGDI()
{
    SelectObject(hDC, hDefaultPen);
    SelectObject(hDC, hDefaultBrush);
    SelectObject(hDC, hDefaultFont);
    if (nullptr != hFont)
        DeleteObject(hFont);
}
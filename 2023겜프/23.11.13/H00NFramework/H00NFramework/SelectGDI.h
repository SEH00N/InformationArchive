class SelectGDI
{
public:
    SelectGDI(HDC dc, PenType ePen);
    SelectGDI(HDC dc, BrushType eBrush);
    SelectGDI(HDC dc, HFONT font);
    ~SelectGDI();
private:
    HDC     hDC;
    HPEN    hDefaultPen;
    HBRUSH  hDefaultBrush;
    HFONT   hDefaultFont;
    HFONT   hFont;
};
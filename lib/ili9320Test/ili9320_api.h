u16 GUI_Color565(u32 RGB);
void GUI_Text(u16 x, u16 y, u8 *str, u16 len,u16 Color, u16 bkColor,u8 mode);
void GUI_Line(u16 x0, u16 y0, u16 x1, u16 y1,u16 color);
void GUI_Circle(u16 cx,u16 cy,u16 r,u16 color,u8 fill);
void GUI_Rectangle(u16 x0, u16 y0, u16 x1, u16 y1,u16 color,u8 fill);
void  GUI_Square(u16 x0, u16 y0, u16 with, u16 color,u8 fill);

void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p,u16 Color, u16 bkColor,u8 mode);
void GUI_Message(u8 *disD,u16 addrX,u16 addrY,u16 minX,u16 maxX,u16 Color, u16 bkColor,u8 mode);

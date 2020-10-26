#include <core/gui.h>

namespace cap
{
    // --------- Class Widget -------------------------------//
    GUIWidget::GUIWidget(string name, int type)
        : m_name(name), m_type(type), m_rel_values(0)
    {
    
    }

    void GUIWidget::setStyle(int key, const Color& value)
    {
        m_styles[key] = value;
    }

    bool GUIWidget::hasStyle(int key) const
    {
        return m_styles.find(key) != m_styles.end();
    }

    // --------- Class Form -------------------------------//
    GUIForm::GUIForm(string name) : GUIWidget(name, CAP_GUI_FORM) 
    {
        m_flags = 0;
        m_size = Point(100, 100);
    }

    void GUIForm::setTitle(string title)
    {
        m_title = title;
    }

    void GUIForm::addWidget(GUIWidget* widget)
    {
        widgets.push_back(widget);
    }

    void GUIForm::draw(RenderTarget& target, RenderStates states) const
    {
        // Fetting values
        Point pos = m_pos;
        Point size = m_size;
        Point window_size = target.getSize();

        // Converting values
        if (m_rel_values & CAP_REL_WIDTH) size.x *= window_size.x;
        if (m_rel_values & CAP_REL_HEIGHT) size.y *= window_size.y;
        if (m_rel_values & CAP_REL_X) pos.x *= window_size.x - size.x;
        if (m_rel_values & CAP_REL_Y) pos.y *= window_size.y - size.y;

        // Widget rect
        Point screen_pos = Point(target.getView().getCenter()) - Point(target.getView().getSize()) / 2;
        pos = pos + screen_pos.round();
        Rect rect = Rect(pos, size);

        // Draw window
        ConvexShape window(4);

        window.setPoint(0, rect.getLeftTop());
        window.setPoint(1, rect.getRightTop());
        window.setPoint(2, rect.getRightBottom());
        window.setPoint(3, rect.getLeftBottom());
        
        // Set background
        if (hasStyle(GUI_STYLE_BACKGROUND_COLOR))
        {
            Color style = getStyle<Color>(GUI_STYLE_BACKGROUND_COLOR);
            window.setFillColor(style);
        }
        window.setOutlineColor(Color::Red);
        window.setOutlineThickness(4);

        target.draw(window);
        
        //for(size_t i=0; i< widgets.size(); i++) target.draw(*widgets[i], states);
    }

    void GUIForm::setPosition(Point pos, int relative)
    {
        m_rel_values = (m_rel_values & (CAP_REL_HEIGHT | CAP_REL_WIDTH)) | (relative & (CAP_REL_X | CAP_REL_Y));
        m_pos = pos;
    }

    void GUIForm::setSize(Point size, int relative)
    {
        m_rel_values = (m_rel_values & (CAP_REL_X | CAP_REL_Y)) | (relative & (CAP_REL_HEIGHT | CAP_REL_WIDTH));
        m_size = size;
    }

    // --------- Class Button -------------------------------//
    GUIButton::GUIButton(string name) : GUIWidget(name, CAP_GUI_BUTTON) 
    {
        onClick = Script::newRef();
    }

    void GUIButton::setText(string title)
    {
        m_title = title;
    }

    void GUIButton::draw(RenderTarget& target, RenderStates states) const
    {
        // ??????????? //
    }

    // --------- Class Label -------------------------------//
    GUILabel::GUILabel(string name) : GUIWidget(name, CAP_GUI_LABEL)
    {
        
    }

    void  GUILabel::setText(string title)
    {
        m_title = title;
    }

    void GUILabel::draw(RenderTarget& target, RenderStates states) const
    {   
        // ??????????????????? //
    }

    // --------- Class Text -------------------------------//
    GUIText::GUIText(string name) : GUIWidget(name, CAP_GUI_TEXT)
    {

    }
    void GUIText::draw(RenderTarget& target, RenderStates states) const
    {
        // ??????????????? //
    }

    void GUIText::setText(string title)
    {
        m_title = title;
    }
}

#include <core/gui.h>

namespace cap
{
    // --------- Class Widget -------------------------------//
    GUIWidget::GUIWidget(string name, int type)
        : m_name(name), m_type(type), m_rel_values(0){}

    // --------- Class Form -------------------------------//
    GUIForm::GUIForm(string name) : GUIWidget(name, CAP_GUI_FORM) 
    {
        this->flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove;
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

        // Draw window
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0);
        ImGui::Begin(m_title.c_str(), 0, flags);
        ImGui::SetWindowPos(pos);
        ImGui::SetWindowSize(size);
        
        for(size_t i=0; i< widgets.size(); i++) target.draw(*widgets[i], states);

        ImGui::End();
        ImGui::PopStyleVar();
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
        ImGui::SetCursorPosX((ImGui::GetCursorPosX() + ImGui::GetColumnWidth() - ImGui::CalcTextSize(m_title.c_str()).x + ImGui::GetStyle().ItemSpacing.x) / 2);
        if(ImGui::Button(m_title.c_str()))
        {
            if(onClick.isFunction()) onClick();
        }
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
        ImGui::SetCursorPosX((ImGui::GetCursorPosX() + ImGui::GetColumnWidth() - ImGui::CalcTextSize(m_title.c_str()).x + ImGui::GetStyle().ItemSpacing.x) / 2);
        ImGui::Text(m_title.c_str());
    }

    // --------- Class Text -------------------------------//
    GUIText::GUIText(string name) : GUIWidget(name, CAP_GUI_TEXT)
    {

    }
    void GUIText::draw(RenderTarget& target, RenderStates states) const
    {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), m_title.c_str());
    }

    void GUIText::setText(string title)
    {
        m_title = title;
    }
}

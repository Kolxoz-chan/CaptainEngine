#include <core/gui.h>

namespace cap
{
    // --------- Class Widget -------------------------------//
    GUIWidget::GUIWidget(string name, int type)
        : m_name(name), m_type(type){}

    void GUIWidget::setPosition(Point pos)
    {
        m_pos = pos;
    }


    // --------- Class Form -------------------------------//
    GUIForm::GUIForm(string name) : GUIWidget(name, CAP_GUI_FORM) 
    {
        this->flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove;
    }

    void GUIForm::setTitle(string title)
    {
        m_title = title;
    }

    void GUIForm::addWidget(GUIWidget* widget)
    {
        widgets.push_back(widget);
    }

    void GUIForm::draw()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0);
        ImGui::Begin(m_title.c_str(), 0, flags);
        ImGui::SetWindowPos({ 40, 40 });
        ImGui::SetWindowSize({ 100, 100 });
        
        for(size_t i=0; i< widgets.size(); i++) widgets[i]->draw();

        ImGui::End();
        ImGui::PopStyleVar();
    }

    // --------- Class Button -------------------------------//
    GUIButton::GUIButton(string name) : GUIWidget(name, CAP_GUI_BUTTON) 
    {
        onClick = Script::newRef();
    }

    void GUIButton::setTitle(string title)
    {
        m_title = title;
    }

    void GUIButton::draw()
    {
        if(ImGui::Button(m_title.c_str()))//, ImVec2(0.5f, 0.0f)))
        {
            if(onClick.isFunction()) onClick();
        }
    }

    // --------- Class Label -------------------------------//
    GUILabel::GUILabel(string name) : GUIWidget(name, CAP_GUI_LABEL)
    {
        
    }

    void  GUILabel::setTitle(string title)
    {
        m_title = title;
    }

    void GUILabel::draw()
    {
        ImGui::Text(m_title.c_str());
    }
}

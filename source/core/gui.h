#ifndef GUI_H
#define GUI_H

#include <core/constants.h>
#include <core/script.h>
#include <core/types.h>

#include <libraries/std.hpp>
#include <libraries/gui.hpp>

namespace cap
{
    // --------- Class Widget -------------------------------//
    class GUIWidget
    {
    private:
        Point m_pos, m_size;

        string m_name;
        int m_type;

    public:
        GUIWidget(string name, int type);

        virtual void setPosition(Point pos);

        virtual void draw() = 0;
    };

    // --------- Class Form -------------------------------//
    class GUIForm : public GUIWidget
    {
    private:
       string m_title;
       int flags;
       vector<GUIWidget*> widgets;

    public:
        GUIForm(string name = string());

        void addWidget(GUIWidget* widget);

        void setTitle(string title);

        void draw();
    };

    // --------- Class Button -------------------------------//
    class GUIButton : public GUIWidget
    {
    private:
        string m_title;

    public:
        // Callback
        LuaRef onClick = 0;

        // Methods
        GUIButton(string name = string());

        void setTitle(string title);
        void draw();
    };

    // --------- Class Label -------------------------------//
    class GUILabel : public GUIWidget
    {
    private:
        string m_title;

    public:
        GUILabel(string name = string());

        void setTitle(string title);
        void draw();

    };
}

#endif // GUI_H

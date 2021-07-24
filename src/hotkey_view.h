#ifndef HOTKEY_VIEW_H
#define HOTKEY_VIEW_H

#include <QLineEdit>

class HotkeyView : public QLineEdit {
    public:
        HotkeyView();
        void focusInEvent(QFocusEvent *event);
        void focusOutEvent(QFocusEvent *event);
};
#endif
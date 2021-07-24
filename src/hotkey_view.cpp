#include "hotkey_view.h"
#include "hotkey.h"

HotkeyView::HotkeyView() {
    setObjectName("hotkeyInput");
    setFocusPolicy(Qt::ClickFocus);
    setReadOnly(true);
}

void HotkeyView::focusInEvent(QFocusEvent *event) {
    Hotkey::getInstance().gettingFocus();
}

void HotkeyView::focusOutEvent(QFocusEvent *event) {
    Hotkey::getInstance().losingFocus();
}
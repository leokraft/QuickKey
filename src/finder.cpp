#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QClipboard>
#include <QApplication>
#include <iostream>

#include "windows.h"
#include "finder.h"
#include "flowlayout.h"
#include "main_window.h"

Finder::Finder(QWidget *parent) : QWidget(parent)  {

    searchBar = new QLineEdit;
    searchBar->setObjectName("search");
    searchBar->setFocus();
    connect(searchBar, &QLineEdit::returnPressed,
            this, &Finder::copyFirstItem);
    connect(searchBar, &QLineEdit::textChanged,
            this, &Finder::applySearch);

    QHBoxLayout *headerLayout = new QHBoxLayout;
    headerLayout->setContentsMargins(8, 8, 4, 8);
    headerLayout->addWidget(searchBar);

    QWidget *header = new QWidget;
    header->setObjectName("header");
    header->setLayout(headerLayout);

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setObjectName("scroll");

    QWidget *scrollAreaContent = new QWidget;

    contentLayout = new QVBoxLayout;
    contentLayout->setContentsMargins(0, 0, 0, 0);
    // add strech to prevent growth of child elements
    contentLayout->addStretch();
    scrollAreaContent->setLayout(contentLayout);
    // apply empty search to fill content
    applySearch("");

    scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    scrollArea->setWidgetResizable(true);

    scrollArea->setWidget(scrollAreaContent);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(header);
    mainLayout->addWidget(scrollArea);

    setLayout(mainLayout);
    setWindowTitle("QuickKey");

    loader = Loader();
};

void Finder::setSearchBarFocus() {
    searchBar->setFocus();
}

void Finder::copyFirstItem() {

    QLayoutItem *child;
    if (!(child = contentLayout->itemAt(0))) {
        return;
    }

    QWidget *firstGroup = child->widget();

    QLayout *layout = firstGroup->layout();
    if (!(child = layout->itemAt(0))) {
        return;
    }

    QWidget *firstButton = child->widget();

    // simulate click event
    dynamic_cast<QPushButton*>(firstButton)->clicked();
}

void Finder::applySearch(const QString &searchText) {

    QWidget *resultBox = new QWidget();
    resultBox->setObjectName("selector");
    
    FlowLayout *flow = new FlowLayout;

    QStringList tags = searchText.split(" ", Qt::SkipEmptyParts);

    loader.setFilter(tags);

    QString searchResult = loader.next();
    int i = 0;

    while (!searchResult.isNull() && i < 100) {

        QPushButton *button = new QPushButton(searchResult);

        // copies string to clipboard on button press
        connect(button, &QPushButton::clicked,
        [this, searchResult]() {
            QApplication::clipboard()->setText(searchResult);
            static_cast<MainWindow*>(this->window())->hide();
            searchBar->clear();
            simulatedPasteKeybind();
        });

        flow->addWidget(button);

        i++;
        searchResult = loader.next();
    }

    resultBox->setLayout(flow);
    deleteOldItems();
    contentLayout->addWidget(resultBox);
    contentLayout->addStretch();

};

void Finder::deleteOldItems() {
    QLayoutItem *child;
    while ((child = contentLayout->takeAt(0)) != 0) {
        QWidget *widget = child->widget();
        if (widget) {

            delete widget;
        }
    }
};

void Finder::simulatedPasteKeybind(){
    INPUT ctrlV [4];
    ZeroMemory(ctrlV, sizeof ctrlV);

    ctrlV [0].type = INPUT_KEYBOARD;
    ctrlV [0].ki.wVk = VK_LCONTROL;

    ctrlV [1].type = INPUT_KEYBOARD;
    ctrlV [1].ki.wVk = 'V'; //assuming ASCII

    ctrlV [2].type = INPUT_KEYBOARD;
    ctrlV [2].ki.wVk = 'V'; //assuming ASCII
    ctrlV [2].ki.dwFlags = KEYEVENTF_KEYUP;

    ctrlV [3].type = INPUT_KEYBOARD;
    ctrlV [3].ki.wVk = VK_LCONTROL;
    ctrlV [3].ki.dwFlags = KEYEVENTF_KEYUP;
    
    SendInput (4, ctrlV, sizeof (INPUT));
}

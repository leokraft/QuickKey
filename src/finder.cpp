#include <QtWidgets>
#include "finder.h"

Finder::Finder(QWidget *parent) : QWidget(parent) {

    searchLine = new QLineEdit;
    settingsButton = new QPushButton;

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(searchLine);
    topLayout->addWidget(settingsButton);

    QScrollArea *scrollArea = new QScrollArea;
    QWidget *scrollAreaContent = new QWidget;

    contentLayout = new QVBoxLayout;
    contentLayout->addStretch();

    scrollAreaContent->setLayout(contentLayout);

    scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    scrollArea->setWidgetResizable(true);

    scrollArea->setWidget(scrollAreaContent);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(scrollArea);

    setLayout(mainLayout);
    setWindowTitle(tr("QuickKey"));
};

void Finder::addGroupBox(QGroupBox *group) {
    // second last since the last is a strech
    int insertIndex = contentLayout->count() - 1;
    contentLayout->insertWidget(insertIndex, group);
}
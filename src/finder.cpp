#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QClipboard>
#include <QApplication>
#include <iostream>

#include "loader.h"
#include "finder.h"
#include "flowlayout.h"
#include "mainwindow.h"

Finder::Finder(QWidget *parent) : QWidget(parent)  {

    searchBar = new QLineEdit;
    searchBar->setFocus();
    connect(searchBar, &QLineEdit::returnPressed,
            this, &Finder::copyFirstItem);
    connect(searchBar, &QLineEdit::textChanged,
            this, &Finder::applySearch);

    settingsButton = new QPushButton;

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(searchBar);
    topLayout->addWidget(settingsButton);

    QScrollArea *scrollArea = new QScrollArea;
    QWidget *scrollAreaContent = new QWidget;

    contentLayout = new QVBoxLayout;
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
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(scrollArea);

    setLayout(mainLayout);
    setWindowTitle(tr("QuickKey"));
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

    QGroupBox *resultBox = new QGroupBox("Search results");
    FlowLayout *flow = new FlowLayout;

    QStringList tags = searchText.split(" ");

    QStringList searchMatches;

    Loader loader(tags);

    int i = 0;
    while (loader.hasNext() && i < 100) {
        searchMatches.push_back(loader.next());
        i++;
    }

    for (QString character : searchMatches) {
        QPushButton *button = new QPushButton(character);
        // copies string to clipboard on button press
        connect(button, &QPushButton::clicked,
        [this, character](){
            QApplication::clipboard()->setText(character);
            static_cast<MainWindow*>(this->window())->hide();
            searchBar->clear();
        });
        
        flow->addWidget(button);
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

#include <QtWidgets>
#include "finder.h"
#include "flowlayout.h"

Finder::Finder(QWidget *parent) : QWidget(parent) {

    characters = new Characters;

    searchLine = new QLineEdit;
    searchLine->setFocus();
    connect(searchLine, &QLineEdit::returnPressed,
            this, &Finder::copyFirstItem);
    connect(searchLine, &QLineEdit::textChanged,
            this, &Finder::applySearch);

    settingsButton = new QPushButton;

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(searchLine);
    topLayout->addWidget(settingsButton);

    QScrollArea *scrollArea = new QScrollArea;
    QWidget *scrollAreaContent = new QWidget;

    contentLayout = new QVBoxLayout;
    // add strech to prevent growth of child elements
    contentLayout->addStretch();
    // apply empty search to fill content
    applySearch("");
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
    QStringList chars = characters->getByTags(tags);

    for (QString character : chars) {
        QPushButton *button = new QPushButton(character);
        // copies string to clipboard on button press
        connect(button, &QPushButton::clicked,
        [this, character](){
            QApplication::clipboard()->setText(character);
        });
        
        flow->addWidget(button);
    }

    resultBox->setLayout(flow);
    deleteOldItems();
    addGroupBox(resultBox);
};

void Finder::deleteOldItems() {
    QLayoutItem *child;
    while ((child = contentLayout->takeAt(0)) != 0) {
        QWidget *widget = child->widget();
        if (widget) {
            // widget is deleted if parent is set to NULL
            widget->setParent(NULL);
        }
        
    }
}

void Finder::addGroupBox(QGroupBox *group) {
    // second last since the last is a strech
    int insertIndex = contentLayout->count() - 1;
    contentLayout->insertWidget(insertIndex, group);
};
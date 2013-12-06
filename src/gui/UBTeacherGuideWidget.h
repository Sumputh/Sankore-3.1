/*
 * Copyright (C) 2010-2013 Groupement d'Intérêt Public pour l'Education Numérique en Afrique (GIP ENA)
 *
 * This file is part of Open-Sankoré.
 *
 * Open-Sankoré is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License,
 * with a specific linking exception for the OpenSSL project's
 * "OpenSSL" library (or with modified versions of it that use the
 * same license as the "OpenSSL" library).
 *
 * Open-Sankoré is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Open-Sankoré.  If not, see <http://www.gnu.org/licenses/>.
 */



#ifndef UBTEACHERGUIDEWIDGET_H
#define UBTEACHERGUIDEWIDGET_H

class QTreeWidget;
class QHeaderView;
class QLabel;
class QVBoxLayout;
class QPushButton;
class UBDocumentProxy;
class UBGraphicsTextItem;
class QScrollArea;
class QDomDocument;

#include "UBTeacherGuideWidgetsTools.h"

#include "interfaces/IDataStorage.h"

typedef enum
{
    tUBTGZeroPageMode_EDITION,
    tUBTGZeroPageMode_PRESENTATION
}tUBTGZeroPageMode;

#define LOWER_RESIZE_WIDTH 50

/***************************************************************************
 *               class    UBTeacherGuideEditionWidget                      *
 ***************************************************************************/
class UBTeacherGuideEditionWidget : public QWidget , public IDataStorage
{
    Q_OBJECT
public:
    explicit UBTeacherGuideEditionWidget(QWidget* parent = 0, const char* name="UBTeacherGuideEditionWidget");
    ~UBTeacherGuideEditionWidget();
    void cleanData();
    QVector<tUBGEElementNode*> getData();

    void load(QDomDocument element);
    QVector<tIDataStorage*> save(int pageIndex);

    bool isModified();

public slots:
    void onAddItemClicked(QTreeWidgetItem* widget, int column, QDomElement* element = 0);
    void onActiveSceneChanged();
    void showEvent(QShowEvent* event);

private:
    QList<QTreeWidgetItem*> getChildrenList(QTreeWidgetItem* widgetItem);
    QVector<tUBGEElementNode*> getPageAndCommentData();

    QVBoxLayout* mpLayout;
    QLabel* mpDocumentTitle;
    QLabel* mpPageNumberLabel;
    UBTGAdaptableText* mpPageTitle;
    UBTGAdaptableText* mpComment;
    QFrame* mpSeparator;
    QTreeWidget* mpTreeWidget;
    QTreeWidgetItem* mpRootWidgetItem;
    UBAddItem* mpAddAnActionItem;
    UBAddItem* mpAddAMediaItem;
    UBAddItem* mpAddALinkItem;

private slots:
    void onActiveDocumentChanged();
#ifdef Q_WS_MACX
    void onSliderMoved(int size);
#endif
};


/***************************************************************************
 *           class    UBTeacherGuidePresentationWidget                     *
 ***************************************************************************/
class UBTeacherGuidePresentationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UBTeacherGuidePresentationWidget(QWidget* parent, const char* name = "UBTeacherGuidePresentationName");
    ~UBTeacherGuidePresentationWidget();
    void showData(QVector<tUBGEElementNode*>data);
    void cleanData();

public slots:
    void onAddItemClicked(QTreeWidgetItem* widget, int column);
    void onActiveSceneChanged();

private:
    bool eventFilter(QObject* object, QEvent* event);

    void createMediaButtonItem();

    UBTGAdaptableText* mpPageTitle;
    UBTGAdaptableText* mpComment;
    QVBoxLayout* mpLayout;
    QHBoxLayout* mpButtonTitleLayout;
    QLabel* mpDocumentTitle;
    QLabel* mpPageNumberLabel;
    QFrame* mpSeparator;
    QPushButton* mpModePushButton;
    UBTGDraggableTreeItem* mpTreeWidget;
    QTreeWidgetItem* mpRootWidgetItem;
    QTreeWidgetItem* mpMediaSwitchItem;


#ifdef Q_WS_MACX
private slots:
    void onSliderMoved(int size);
#endif

};

/***************************************************************************
 *                  class    UBTeacherGuidePageZeroWidget                  *
 ***************************************************************************/
class UBTeacherGuidePageZeroWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UBTeacherGuidePageZeroWidget(QWidget* parent, const char* name = "UBTeacherGuidePageZeroEditionWidget");
    ~UBTeacherGuidePageZeroWidget();

    QVector<tUBGEElementNode*> getData();
    bool isModified();

signals:
    void resized();

public slots:
    void onActiveSceneChanged();
    void switchToMode(tUBTGZeroPageMode mode = tUBTGZeroPageMode_EDITION);

    //issue 1517 - NNE - 20131206
    /**
      * Signals used when the user click on the licence logo
      */
    void onClickLicence();

protected:
    void resizeEvent(QResizeEvent* ev);

private:
    void fillComboBoxes();
    void loadData();
    void hideEvent(QHideEvent* event);
    bool eventFilter(QObject* object, QEvent* event);
    void updateSceneTitle();

    QVBoxLayout* mpLayout;
    QHBoxLayout* mpButtonTitleLayout;
    QVBoxLayout* mpContainerWidgetLayout;
    QPushButton* mpModePushButton;
    QLabel* mpPageNumberLabel;

    QScrollArea* mpScrollArea;
    QWidget* mpContainerWidget;

    UBTGAdaptableText* mpSessionTitle;
    QFrame* mpSeparatorSessionTitle;

    QLabel* mpAuthorsLabel;
    UBTGAdaptableText* mpAuthors;
    QFrame* mpSeparatorAuthors;

    QLabel* mpCreationLabel;
    QLabel* mpLastModifiedLabel;
    QLabel* mpObjectivesLabel;
    UBTGAdaptableText* mpObjectives;
    QFrame* mpSeparatorObjectives;

    QLabel* mpIndexLabel;
    QLabel* mpKeywordsLabel;
    UBTGAdaptableText* mpKeywords;

    QLabel* mpSchoolLevelItemLabel;
    QComboBox* mpSchoolLevelBox;
    QLabel* mpSchoolLevelValueLabel;

    QLabel* mpSchoolSubjectsItemLabel;
    QComboBox* mpSchoolSubjectsBox;
    QLabel* mpSchoolSubjectsValueLabel;

    QLabel* mpSchoolTypeItemLabel;
    QComboBox* mpSchoolTypeBox;
    QLabel* mpSchoolTypeValueLabel;
    QFrame* mpSeparatorIndex;

    QLabel* mpLicenceLabel;
    QComboBox* mpLicenceBox;
    QLabel* mpLicenceValueLabel;
    QLabel* mpLicenceIcon;
    QVBoxLayout* mpLicenceLayout; // Issue 1517 - ALTI/AOU - 20131206 : change le layout Horizontal en Vertical.

    UBGraphicsTextItem* mpSceneItemSessionTitle;

    QMap<QString,QString> mGradeLevelsMap;
    QMap<QString,QStringList> mSubjects;

    UBDocumentProxy* mCurrentDocument;

private slots:
    void onSchoolLevelChanged(QString schoolLevel);
    void persistData();
};

//issue 1517 - NNE - 20131206 : Make the QLabel class clickable
/**
  * \class UBClickableLabel
  *
  * A simple class wich override the QLabel to make it clickable
  */
class UBClickableLabel : public QLabel
{
    Q_OBJECT

public:
    UBClickableLabel(QWidget * parent = 0, Qt::WindowFlags f = 0):
        QLabel(parent, f)
    {

    }

protected:
    void mousePressEvent(QMouseEvent * ev)
    {
        QLabel::mousePressEvent(ev);
        emit clicked();
    }

signals:
    void clicked();
};
//issue 1517 - NNE - 20131206 : END

/***************************************************************************
 *                    class    UBTeacherGuideWidget                        *
 ***************************************************************************/

class UBTeacherGuideWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit UBTeacherGuideWidget(QWidget* parent = 0, const char* name="UBTeacherGuideWidget");
    ~UBTeacherGuideWidget();

    bool isModified();

public slots:
    void changeMode();
    void showPresentationMode();
    void connectToStylusPalette();
    void onActiveSceneChanged();

private:
    UBTeacherGuidePageZeroWidget* mpPageZeroWidget;
    UBTeacherGuideEditionWidget* mpEditionWidget;
    UBTeacherGuidePresentationWidget* mpPresentationWidget;
    QVector<tUBGEElementNode*>mCurrentData;
    bool mKeyboardActionFired;

private slots:
    void onTriggeredAction(bool checked);
    void onTriggeredKeyboardAction(bool checked);
};

#endif // UBTEACHERGUIDEWIDGET_H

#include "display.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QScrollBar>
#include<QFrame>
#include<QMenu>
#include <QToolBar>
#include <QBoxLayout>
#include <QFormLayout>
#include <QDesktopServices>
#include <QCheckBox>
#include <QCompleter>
#include <QTime>

Display::Display(QWidget *parent):QMainWindow(parent) {

    //set default user
    actor.m_username = "James25";
    actor.m_password = "12345";
    actor.m_firstName = "James";
    actor.m_lastName = "Miller";

    //set fonts
    QFont serifFontFeed("Arial", 8, QFont::Bold);
    serifFontFeed.setCapitalization(QFont::AllUppercase);
    serifFontFeed.setUnderline(true);

    QFont serifFontCat("Arial", 8, QFont::DemiBold);
    serifFontCat.setCapitalization(QFont::AllUppercase);

    //set favourites list
    favlists[0][0] = "Canadian News";
    favlists[0][1] = "Interesting";
    favlists[0][2] = "Covid";
    favlists[0][3] = "Fashion 2020";
    favlists[0][4] = "";
    favlists[0][5] = "";
    favlists[0][6] = "";
    favlists[0][7] = "";
    favlists[0][8] = "";
    favlists[0][9] = "";
    favlists[0][10] = "";
    favlists[0][11] = "";
    favlists[0][12] = "";
    favlists[0][13] = "";
    favlists[0][14] = "";
    favlists[0][15] = "";
    favlists[0][16] = "";
    favlists[0][17] = "";
    favlists[0][18] = "";
    favlists[0][19] = "";

    favlists[1][0] = "Trudeau unveils new net-zero emissions plan to meet climate change targets.";
    favlists[2][0] = "Canadian youth sports groups are losing millions of dollars to fraud and theft";
    favlists[1][2] = "Trudeau to address Canadians on COVID-19 as Tam releases sobering new projections";

    //header toolbar to be displayed on every layout/page
     toolbar = addToolBar("main toolbar");
     toolbar->setFixedHeight(70);
     toolbar->setContentsMargins(0,0,0,0);
     toolbar->setIconSize(QSize(70, 100));
     toolbar->setStyleSheet("QToolBar{background-color: #1F4A8A}");

     //make header components
     //new reader logo
     QLabel *logo = new QLabel("News Reader");
     logo->setStyleSheet("QLabel{color: #FFFFFF; font-size: 20px; font-weight: bold;}");
     logo->setContentsMargins(15, 15, 50, 15);

     //add auto completion functionality
     QStringList wordList;
     wordList << "greece" << "world" << "sports" << "covid-19"
                  << "fashion" << "entertainment" << "technology" << "politics"
                      << "weather" << "trudeau" << "military" << "current news"
                          << "canada" << "world" << "u.s election" << "toronto"
                              << "trump" << "stock market" << "u.s politics" << "u.s"
                                    << "donald trump" << "biden" << "art" << "economy"
                                        << "economics" << "canadian economy" << "canadian politics" << "canada covid-19"
                                            << "top stories" << "fashion 2020" << "u.s sports" << "international news"
                                                << "ontario" << "canadian police" << "local" << "videos"
                                                    << "vaccine" << "news" << "home depot" << "job bank"
                                                        << "kenya news" << "kelly" << "kijiji ontario" << "joe biden"
                                                         << "roblox" << "questrade" << "amazon" << "kijiji"
                                                             << "youtube" << "walmart" << "rogers" << "rbc bank"
                                                                 << "xbox" << "zoom" << "zara canada" << "covid-19 world";

     //search bar
     toolbar->addWidget(logo);
     searchbar = new QLineEdit();
     searchbar->setFixedWidth(200);
     searchbar->setPlaceholderText("Search");
     toolbar->addWidget(searchbar);

     QCompleter *completer = new QCompleter(wordList, this);
     completer->setCaseSensitivity(Qt::CaseInsensitive);
     searchbar->setCompleter(completer);

     // Spacer
     QWidget *spacer = new QWidget();
     spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
     toolbar->addWidget(spacer);

    //favourites icon
    QPixmap favpix(":/fav.jpg");
    QAction *favourites = new QAction(QIcon(favpix), "&Favourites");
    toolbar->addAction(favourites);

    //settings icon
    QPixmap settingspix(":/settings.jpg");
    QAction *settings = new QAction(QIcon(settingspix), tr("&Settings"));
    toolbar->addAction(settings);

    toolbar->addSeparator();

    //user icon
    QLabel *signedIn = new QLabel("Signed In");
    signedIn->setStyleSheet("QLabel{color: #FFFFFF; font-size: 12px; font-weight: bold;}");
    signedIn->setContentsMargins(20, 0, 0, 0);
    toolbar->addWidget(signedIn);
    QPixmap userpix(":/user.jpg");
    QAction *user = new QAction(QIcon(userpix), tr("&User"));
    toolbar->addAction(user);

    //second toolbar to be displayed on every layout/page
    addToolBarBreak();
    toolbar2 = addToolBar("second toolbar");
    toolbar2->setFixedHeight(40);

    myFeed = new QAction("&My Feed");
    myFeed->setFont(serifFontFeed);
    QAction *canada = new QAction("&Canada");
    canada->setFont(serifFontCat);
    QAction *world = new QAction("&World");
    world->setFont(serifFontCat);
    QAction *sports = new QAction("&Sports");
    sports->setFont(serifFontCat);
    QAction *covid = new QAction("&Covid-19");
    covid->setFont(serifFontCat);
    QAction *fashion = new QAction("&Fashion");
    fashion->setFont(serifFontCat);
    QAction *entertainment = new QAction("&Entertainment");
    entertainment->setFont(serifFontCat);
    QAction *technology = new QAction("&Technology");
    technology->setFont(serifFontCat);
    QAction *politics = new QAction("&Politics");
    politics->setFont(serifFontCat);
    QAction *weather = new QAction("&Weather");
    weather->setFont(serifFontCat);

    toolbar2->addAction(myFeed);
    toolbar2->addAction(canada);
    toolbar2->addAction(world);
    toolbar2->addAction(sports);
    toolbar2->addAction(covid);
    toolbar2->addAction(fashion);
    toolbar2->addAction(entertainment);
    toolbar2->addAction(technology);
    toolbar2->addAction(politics);
    toolbar2->addAction(weather);

    //read entire articles file to one QString
     QFile file(":/articles.txt");
    file.open(QIODevice::ReadOnly);
       if (!file.isOpen())
            return;

    QTextStream stream(&file);
    QString allArticles = stream.readAll();
    file.close();

    //parsing articles string
    QString::SectionFlag flag = QString::SectionSkipEmpty;
    articles[0].m_title = allArticles.section('*', 0, 0, flag);
    articles[0].m_text = allArticles.section('*', 1, 1, flag);
    articles[1].m_title = allArticles.section('*', 2, 2, flag);
    articles[1].m_text = allArticles.section('*', 3, 3, flag);
    articles[2].m_title = allArticles.section('*', 4, 4, flag);
    articles[2].m_text = allArticles.section('*', 5, 5, flag);
    articles[3].m_title = allArticles.section('*', 6, 6, flag);
    articles[3].m_text = allArticles.section('*', 7, 7, flag);
    articles[4].m_title = allArticles.section('*', 8, 8, flag);
    articles[4].m_text = allArticles.section('*', 9, 9, flag);
    articles[5].m_title = allArticles.section('*', 10, 10, flag);
    articles[5].m_text = allArticles.section('*', 11, 11, flag);
    articles[6].m_title = allArticles.section('*', 12, 12, flag);
    articles[6].m_text = allArticles.section('*', 13, 13, flag);
    articles[7].m_title = allArticles.section('*', 14, 14, flag);
    articles[7].m_text = allArticles.section('*', 15, 15, flag);
    articles[8].m_title = allArticles.section('*', 16, 16, flag);
    articles[8].m_text = allArticles.section('*', 17, 17, flag);
    articles[9].m_title = allArticles.section('*', 18, 18, flag);
    articles[9].m_text = allArticles.section('*', 19, 19, flag);

    //get article links
    //read entire links file to one QString
     QFile file2(":/links.txt");
    file2.open(QIODevice::ReadOnly);
       if (!file2.isOpen())
            return;

    QTextStream stream2(&file2);
    QString allLinks = stream2.readAll();
    file2.close();

    //parsing articles string
    links[0] = allLinks.section('*', 0, 0, flag);
    links[1] = allLinks.section('*', 1, 1, flag);
    links[2] = allLinks.section('*', 2, 2, flag);
    links[3] = allLinks.section('*', 3, 3, flag);
    links[4] = allLinks.section('*', 4, 4, flag);
    links[5] = allLinks.section('*', 5, 5, flag);
    links[6] = allLinks.section('*', 6, 6, flag);
    links[7] = allLinks.section('*', 7, 7, flag);
    links[8] = allLinks.section('*', 8, 8, flag);
    links[9] = allLinks.section('*', 9, 9, flag);

    //make main view layout
    vlayout = new QVBoxLayout();
    feedlayout = new QHBoxLayout();
    topNewslayout = new QHBoxLayout();

    //top news stories -- on top of feed
    leftArrow = new QPushButton();
    leftArrow->setStyleSheet("QPushButton {border-image:url(:/leftArrow.jpg);}");
    leftArrow->setFlat(true);
    leftArrow->setMaximumWidth(35);
    leftArrow->setMinimumHeight(60);

    article9 = new QPushButton();
    article9->setStyleSheet("QPushButton {border-image:url(:/thumbnail9.jpg);}");
    article9->setFlat(true);
    article9->setMaximumWidth(600);
    article9->setMinimumHeight(330);

    article10 = new QPushButton();
    article10->setStyleSheet("QPushButton {border-image:url(:/thumbnail10.jpg);}");
    article10->setFlat(true);
    article10->setMaximumWidth(600);
    article10->setMinimumHeight(330);

    article5top  = new QPushButton();
    article5top->setStyleSheet("QPushButton {border-image:url(:/thumbnail5top.jpg);}");
    article5top->setFlat(true);
    article5top->setMaximumWidth(600);
    article5top->setMinimumHeight(330);

    //make stack widget to flip through
    stackedTopnews = new QStackedWidget;
    stackedTopnews->addWidget(article5top);
    stackedTopnews->addWidget(article9);
    stackedTopnews->addWidget(article10);
    stackedTopnews->setCurrentWidget(article5top);
    stackedTopnews->setMaximumWidth(600);

    rightArrow = new QPushButton();
    rightArrow->setStyleSheet("QPushButton {border-image:url(:/rightArrow.jpg);}");
    rightArrow->setFlat(true);
    rightArrow->setMaximumWidth(35);
    rightArrow->setMinimumHeight(60);

    topNewslayout->setSpacing(30);
    topNewslayout->setMargin(30);
    topNewslayout->addWidget(leftArrow, 0, Qt::AlignRight );
    topNewslayout->addWidget(stackedTopnews);
    topNewslayout->addWidget(rightArrow, 0, Qt::AlignLeft );

    //my feed news stories -- on bottom of feed
    leftArrow2 = new QPushButton();
    leftArrow2->setStyleSheet("QPushButton {border-image:url(:/leftArrow.jpg);}");
    leftArrow2->setFlat(true);
    leftArrow2->setMaximumWidth(35);
    leftArrow2->setMinimumHeight(60);

    //FIRST STACK - 8 thumnails a's

    //first article thumbnail
    articlelayout1a = new QVBoxLayout();
    iconlayout1a = new QHBoxLayout();
    article1a = new QPushButton();
    article1a->setStyleSheet("QPushButton {border-image:url(:/thumbnail1.jpg);}");
    article1a->setFlat(true);
    article1a->setMaximumWidth(260);
    article1a->setMinimumHeight(430);
    heart1a = new QPushButton();
    heart1a->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart1a->setMaximumWidth(20);
    plus1a = new QPushButton();
    plus1a->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus1a->setMaximumWidth(20);
    share1tha = new QPushButton();
    share1tha->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share1tha->setMaximumWidth(20);
    iconlayout1a->addWidget(heart1a);
    spacinga = new QLabel();
    spacinga->setMaximumWidth(200);
    iconlayout1a->addWidget(spacinga);
    iconlayout1a->addWidget(plus1a);
    iconlayout1a->addWidget(share1tha);
    articlelayout1a->addWidget(article1a);
    articlelayout1a->addLayout(iconlayout1a);
    articlelayout1a->setMargin(0);
    QFrame *border1a = new QFrame();
    border1a->setMaximumWidth(260);
    border1a->setMinimumHeight(460);
    border1a->setLayout(articlelayout1a);
    border1a->setFrameStyle(QFrame::Box | QFrame::Plain);
    border1a->setLineWidth(2);

    //second article thumbnail
    articlelayout2a = new QVBoxLayout();
    iconlayout2a = new QHBoxLayout();
    article2a = new QPushButton();
    article2a->setStyleSheet("QPushButton {border-image:url(:/thumbnail2.jpg);}");
    article2a->setFlat(true);
    article2a->setMaximumWidth(260);
    article2a->setMinimumHeight(430);
    heart2a = new QPushButton();
    heart2a->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart2a->setMaximumWidth(20);
    plus2a = new QPushButton();
    plus2a->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus2a->setMaximumWidth(20);
    share2tha = new QPushButton();
    share2tha->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share2tha->setMaximumWidth(20);
    iconlayout2a->addWidget(heart2a);
    spacing2a = new QLabel();
    spacing2a->setMaximumWidth(200);
    iconlayout2a->addWidget(spacing2a);
    iconlayout2a->addWidget(plus2a);
    iconlayout2a->addWidget(share2tha);
    articlelayout2a->addWidget(article2a);
    articlelayout2a->addLayout(iconlayout2a);
    articlelayout2a->setMargin(0);
    QFrame *border2a = new QFrame();
    border2a->setMaximumWidth(260);
    border2a->setMinimumHeight(460);
    border2a->setLayout(articlelayout2a);
    border2a->setFrameStyle(QFrame::Box | QFrame::Plain);
    border2a->setLineWidth(2);

    //third article thumbnail
    articlelayout3a = new QVBoxLayout();
    iconlayout3a = new QHBoxLayout();
    article3a = new QPushButton();
    article3a->setStyleSheet("QPushButton {border-image:url(:/thumbnail3.jpg);}");
    article3a->setFlat(true);
    article3a->setMaximumWidth(260);
    article3a->setMinimumHeight(430);
    heart3a = new QPushButton();
    heart3a->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart3a->setMaximumWidth(20);
    plus3a = new QPushButton();
    plus3a->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus3a->setMaximumWidth(20);
    share3tha = new QPushButton();
    share3tha->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share3tha->setMaximumWidth(20);
    iconlayout3a->addWidget(heart3a);
    spacing3a = new QLabel();
    spacing3a->setMaximumWidth(200);
    iconlayout3a->addWidget(spacing3a);
    iconlayout3a->addWidget(plus3a);
    iconlayout3a->addWidget(share3tha);
    articlelayout3a->addWidget(article3a);
    articlelayout3a->addLayout(iconlayout3a);
    articlelayout3a->setMargin(0);
    QFrame *border3a = new QFrame();
    border3a->setMaximumWidth(260);
    border3a->setMinimumHeight(460);
    border3a->setLayout(articlelayout3a);
    border3a->setFrameStyle(QFrame::Box | QFrame::Plain);
    border3a->setLineWidth(2);

    //fourth article thumbnail
    articlelayout4a = new QVBoxLayout();
    iconlayout4a = new QHBoxLayout();
    article4a = new QPushButton();
    article4a->setStyleSheet("QPushButton {border-image:url(:/thumbnail4.jpg);}");
    article4a->setFlat(true);
    article4a->setMaximumWidth(260);
    article4a->setMinimumHeight(430);
    heart4a = new QPushButton();
    heart4a->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart4a->setMaximumWidth(20);
    plus4a = new QPushButton();
    plus4a->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus4a->setMaximumWidth(20);
    share4tha = new QPushButton();
    share4tha->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share4tha->setMaximumWidth(20);
    iconlayout4a->addWidget(heart4a);
    spacing4a = new QLabel();
    spacing4a->setMaximumWidth(200);
    iconlayout4a->addWidget(spacing4a);
    iconlayout4a->addWidget(plus4a);
    iconlayout4a->addWidget(share4tha);
    articlelayout4a->addWidget(article4a);
    articlelayout4a->addLayout(iconlayout4a);
    articlelayout4a->setMargin(0);
    QFrame *border4a = new QFrame();
    border4a->setMaximumWidth(260);
    border4a->setMinimumHeight(460);
    border4a->setLayout(articlelayout4a);
    border4a->setFrameStyle(QFrame::Box | QFrame::Plain);
    border4a->setLineWidth(2);

    //fifth article thumbnail
    articlelayout5a = new QVBoxLayout();
    iconlayout5a = new QHBoxLayout();
    article5a = new QPushButton();
    article5a->setStyleSheet("QPushButton {border-image:url(:/thumbnail5.jpg);}");
    article5a->setFlat(true);
    article5a->setMaximumWidth(260);
    article5a->setMinimumHeight(430);
    heart5a = new QPushButton();
    heart5a->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart5a->setMaximumWidth(20);
    plus5a = new QPushButton();
    plus5a->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus5a->setMaximumWidth(20);
    share5tha = new QPushButton();
    share5tha->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share5tha->setMaximumWidth(20);
    iconlayout5a->addWidget(heart5a);
    spacing5a = new QLabel();
    spacing5a->setMaximumWidth(200);
    iconlayout5a->addWidget(spacing5a);
    iconlayout5a->addWidget(plus5a);
    iconlayout5a->addWidget(share5tha);
    articlelayout5a->addWidget(article5a);
    articlelayout5a->addLayout(iconlayout5a);
    articlelayout5a->setMargin(0);
    QFrame *border5a = new QFrame();
    border5a->setMaximumWidth(260);
    border5a->setMinimumHeight(460);
    border5a->setLayout(articlelayout5a);
    border5a->setFrameStyle(QFrame::Box | QFrame::Plain);
    border5a->setLineWidth(2);

    //sixth article thumbnail
    articlelayout6a = new QVBoxLayout();
    iconlayout6a = new QHBoxLayout();
    article6a = new QPushButton();
    article6a->setStyleSheet("QPushButton {border-image:url(:/thumbnail6.jpg);}");
    article6a->setFlat(true);
    article6a->setMaximumWidth(260);
    article6a->setMinimumHeight(430);
    heart6a = new QPushButton();
    heart6a->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart6a->setMaximumWidth(20);
    plus6a = new QPushButton();
    plus6a->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus6a->setMaximumWidth(20);
    share6tha = new QPushButton();
    share6tha->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share6tha->setMaximumWidth(20);
    iconlayout6a->addWidget(heart6a);
    spacing6a = new QLabel();
    spacing6a->setMaximumWidth(200);
    iconlayout6a->addWidget(spacing6a);
    iconlayout6a->addWidget(plus6a);
    iconlayout6a->addWidget(share6tha);
    articlelayout6a->addWidget(article6a);
    articlelayout6a->addLayout(iconlayout6a);
    articlelayout6a->setMargin(0);
    QFrame *border6a = new QFrame();
    border6a->setMaximumWidth(260);
    border6a->setMinimumHeight(460);
    border6a->setLayout(articlelayout6a);
    border6a->setFrameStyle(QFrame::Box | QFrame::Plain);
    border6a->setLineWidth(2);

    //seventh article thumbnail
    articlelayout7a = new QVBoxLayout();
    iconlayout7a = new QHBoxLayout();
    article7a = new QPushButton();
    article7a->setStyleSheet("QPushButton {border-image:url(:/thumbnail7.jpg);}");
    article7a->setFlat(true);
    article7a->setMaximumWidth(260);
    article7a->setMinimumHeight(430);
    heart7a = new QPushButton();
    heart7a->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart7a->setMaximumWidth(20);
    plus7a = new QPushButton();
    plus7a->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus7a->setMaximumWidth(20);
    share7tha = new QPushButton();
    share7tha->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share7tha->setMaximumWidth(20);
    iconlayout7a->addWidget(heart7a);
    spacing7a = new QLabel();
    spacing7a->setMaximumWidth(200);
    iconlayout7a->addWidget(spacing7a);
    iconlayout7a->addWidget(plus7a);
    iconlayout7a->addWidget(share7tha);
    articlelayout7a->addWidget(article7a);
    articlelayout7a->addLayout(iconlayout7a);
    articlelayout7a->setMargin(0);
    QFrame *border7a = new QFrame();
    border7a->setMaximumWidth(260);
    border7a->setMinimumHeight(460);
    border7a->setLayout(articlelayout7a);
    border7a->setFrameStyle(QFrame::Box | QFrame::Plain);
    border7a->setLineWidth(2);

    //eight article thumbnail
   articlelayout8a = new QVBoxLayout();
    iconlayout8a = new QHBoxLayout();
    article8a = new QPushButton();
    article8a->setStyleSheet("QPushButton {border-image:url(:/thumbnail8.jpg);}");
    article8a->setFlat(true);
    article8a->setMaximumWidth(260);
    article8a->setMinimumHeight(430);
    heart8a = new QPushButton();
    heart8a->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart8a->setMaximumWidth(20);
    plus8a = new QPushButton();
    plus8a->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus8a->setMaximumWidth(20);
    share8tha = new QPushButton();
    share8tha->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share8tha->setMaximumWidth(20);
    iconlayout8a->addWidget(heart8a);
    spacing8a = new QLabel();
    spacing8a->setMaximumWidth(200);
    iconlayout8a->addWidget(spacing8a);
    iconlayout8a->addWidget(plus8a);
    iconlayout8a->addWidget(share8tha);
    articlelayout8a->addWidget(article8a);
    articlelayout8a->addLayout(iconlayout8a);
    articlelayout8a->setMargin(0);
    QFrame *border8a = new QFrame();
    border8a->setMaximumWidth(260);
    border8a->setMinimumHeight(460);
    border8a->setLayout(articlelayout8a);
    border8a->setFrameStyle(QFrame::Box | QFrame::Plain);
    border8a->setLineWidth(2);

    //SECOND STACK - 8 thumnails b's

    //first article thumbnail
    articlelayout1b = new QVBoxLayout();
    iconlayout1b = new QHBoxLayout();
    article1b = new QPushButton();
    article1b->setStyleSheet("QPushButton {border-image:url(:/thumbnail1.jpg);}");
    article1b->setFlat(true);
    article1b->setMaximumWidth(260);
    article1b->setMinimumHeight(430);
    heart1b = new QPushButton();
    heart1b->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart1b->setMaximumWidth(20);
    plus1b = new QPushButton();
    plus1b->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus1b->setMaximumWidth(20);
    share1thb = new QPushButton();
    share1thb->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share1thb->setMaximumWidth(20);
    iconlayout1b->addWidget(heart1b);
    spacingb = new QLabel();
    spacingb->setMaximumWidth(200);
    iconlayout1b->addWidget(spacingb);
    iconlayout1b->addWidget(plus1b);
    iconlayout1b->addWidget(share1thb);
    articlelayout1b->addWidget(article1b);
    articlelayout1b->addLayout(iconlayout1b);
    articlelayout1b->setMargin(0);
    QFrame *border1b = new QFrame();
    border1b->setMaximumWidth(260);
    border1b->setMinimumHeight(460);
    border1b->setLayout(articlelayout1b);
    border1b->setFrameStyle(QFrame::Box | QFrame::Plain);
    border1b->setLineWidth(2);

    //second article thumbnail
    articlelayout2b = new QVBoxLayout();
    iconlayout2b = new QHBoxLayout();
    article2b = new QPushButton();
    article2b->setStyleSheet("QPushButton {border-image:url(:/thumbnail2.jpg);}");
    article2b->setFlat(true);
    article2b->setMaximumWidth(260);
    article2b->setMinimumHeight(430);
    heart2b = new QPushButton();
    heart2b->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart2b->setMaximumWidth(20);
    plus2b = new QPushButton();
    plus2b->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus2b->setMaximumWidth(20);
    share2thb = new QPushButton();
    share2thb->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share2thb->setMaximumWidth(20);
    iconlayout2b->addWidget(heart2b);
    spacing2b = new QLabel();
    spacing2b->setMaximumWidth(200);
    iconlayout2b->addWidget(spacing2b);
    iconlayout2b->addWidget(plus2b);
    iconlayout2b->addWidget(share2thb);
    articlelayout2b->addWidget(article2b);
    articlelayout2b->addLayout(iconlayout2b);
    articlelayout2b->setMargin(0);
    QFrame *border2b = new QFrame();
    border2b->setMaximumWidth(260);
    border2b->setMinimumHeight(460);
    border2b->setLayout(articlelayout2b);
    border2b->setFrameStyle(QFrame::Box | QFrame::Plain);
    border2b->setLineWidth(2);

    //third article thumbnail
    articlelayout3b = new QVBoxLayout();
    iconlayout3b = new QHBoxLayout();
    article3b = new QPushButton();
    article3b->setStyleSheet("QPushButton {border-image:url(:/thumbnail3.jpg);}");
    article3b->setFlat(true);
    article3b->setMaximumWidth(260);
    article3b->setMinimumHeight(430);
    heart3b = new QPushButton();
    heart3b->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart3b->setMaximumWidth(20);
    plus3b = new QPushButton();
    plus3b->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus3b->setMaximumWidth(20);
    share3thb = new QPushButton();
    share3thb->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share3thb->setMaximumWidth(20);
    iconlayout3b->addWidget(heart3b);
    spacing3b = new QLabel();
    spacing3b->setMaximumWidth(200);
    iconlayout3b->addWidget(spacing3b);
    iconlayout3b->addWidget(plus3b);
    iconlayout3b->addWidget(share3thb);
    articlelayout3b->addWidget(article3b);
    articlelayout3b->addLayout(iconlayout3b);
    articlelayout3b->setMargin(0);
    QFrame *border3b = new QFrame();
    border3b->setMaximumWidth(260);
    border3b->setMinimumHeight(460);
    border3b->setLayout(articlelayout3b);
    border3b->setFrameStyle(QFrame::Box | QFrame::Plain);
    border3b->setLineWidth(2);

    //fourth article thumbnail
    articlelayout4b = new QVBoxLayout();
    iconlayout4b = new QHBoxLayout();
    article4b = new QPushButton();
    article4b->setStyleSheet("QPushButton {border-image:url(:/thumbnail4.jpg);}");
    article4b->setFlat(true);
    article4b->setMaximumWidth(260);
    article4b->setMinimumHeight(430);
    heart4b = new QPushButton();
    heart4b->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart4b->setMaximumWidth(20);
    plus4b = new QPushButton();
    plus4b->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus4b->setMaximumWidth(20);
    share4thb = new QPushButton();
    share4thb->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share4thb->setMaximumWidth(20);
    iconlayout4b->addWidget(heart4b);
    spacing4b = new QLabel();
    spacing4b->setMaximumWidth(200);
    iconlayout4b->addWidget(spacing4b);
    iconlayout4b->addWidget(plus4b);
    iconlayout4b->addWidget(share4thb);
    articlelayout4b->addWidget(article4b);
    articlelayout4b->addLayout(iconlayout4b);
    articlelayout4b->setMargin(0);
    QFrame *border4b = new QFrame();
    border4b->setMaximumWidth(260);
    border4b->setMinimumHeight(460);
    border4b->setLayout(articlelayout4b);
    border4b->setFrameStyle(QFrame::Box | QFrame::Plain);
    border4b->setLineWidth(2);

    //fifth article thumbnail
    articlelayout5b = new QVBoxLayout();
    iconlayout5b = new QHBoxLayout();
    article5b = new QPushButton();
    article5b->setStyleSheet("QPushButton {border-image:url(:/thumbnail5.jpg);}");
    article5b->setFlat(true);
    article5b->setMaximumWidth(260);
    article5b->setMinimumHeight(430);
    heart5b = new QPushButton();
    heart5b->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart5b->setMaximumWidth(20);
    plus5b = new QPushButton();
    plus5b->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus5b->setMaximumWidth(20);
    share5thb = new QPushButton();
    share5thb->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share5thb->setMaximumWidth(20);
    iconlayout5b->addWidget(heart5b);
    spacing5b = new QLabel();
    spacing5b->setMaximumWidth(200);
    iconlayout5b->addWidget(spacing5b);
    iconlayout5b->addWidget(plus5b);
    iconlayout5b->addWidget(share5thb);
    articlelayout5b->addWidget(article5b);
    articlelayout5b->addLayout(iconlayout5b);
    articlelayout5b->setMargin(0);
    QFrame *border5b = new QFrame();
    border5b->setMaximumWidth(260);
    border5b->setMinimumHeight(460);
    border5b->setLayout(articlelayout5b);
    border5b->setFrameStyle(QFrame::Box | QFrame::Plain);
    border5b->setLineWidth(2);

    //sixth article thumbnail
    articlelayout6b = new QVBoxLayout();
    iconlayout6b = new QHBoxLayout();
    article6b = new QPushButton();
    article6b->setStyleSheet("QPushButton {border-image:url(:/thumbnail6.jpg);}");
    article6b->setFlat(true);
    article6b->setMaximumWidth(260);
    article6b->setMinimumHeight(430);
    heart6b = new QPushButton();
    heart6b->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart6b->setMaximumWidth(20);
    plus6b = new QPushButton();
    plus6b->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus6b->setMaximumWidth(20);
    share6thb = new QPushButton();
    share6thb->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share6thb->setMaximumWidth(20);
    iconlayout6b->addWidget(heart6b);
    spacing6b = new QLabel();
    spacing6b->setMaximumWidth(200);
    iconlayout6b->addWidget(spacing6b);
    iconlayout6b->addWidget(plus6b);
    iconlayout6b->addWidget(share6thb);
    articlelayout6b->addWidget(article6b);
    articlelayout6b->addLayout(iconlayout6b);
    articlelayout6b->setMargin(0);
    QFrame *border6b = new QFrame();
    border6b->setMaximumWidth(260);
    border6b->setMinimumHeight(460);
    border6b->setLayout(articlelayout6b);
    border6b->setFrameStyle(QFrame::Box | QFrame::Plain);
    border6b->setLineWidth(2);

    //seventh article thumbnail
    articlelayout7b = new QVBoxLayout();
    iconlayout7b = new QHBoxLayout();
    article7b = new QPushButton();
    article7b->setStyleSheet("QPushButton {border-image:url(:/thumbnail7.jpg);}");
    article7b->setFlat(true);
    article7b->setMaximumWidth(260);
    article7b->setMinimumHeight(430);
    heart7b = new QPushButton();
    heart7b->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart7b->setMaximumWidth(20);
    plus7b = new QPushButton();
    plus7b->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus7b->setMaximumWidth(20);
    share7thb = new QPushButton();
    share7thb->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share7thb->setMaximumWidth(20);
    iconlayout7b->addWidget(heart7b);
    spacing7b = new QLabel();
    spacing7b->setMaximumWidth(200);
    iconlayout7b->addWidget(spacing7b);
    iconlayout7b->addWidget(plus7b);
    iconlayout7b->addWidget(share7thb);
    articlelayout7b->addWidget(article7b);
    articlelayout7b->addLayout(iconlayout7b);
    articlelayout7b->setMargin(0);
    QFrame *border7b = new QFrame();
    border7b->setMaximumWidth(260);
    border7b->setMinimumHeight(460);
    border7b->setLayout(articlelayout7b);
    border7b->setFrameStyle(QFrame::Box | QFrame::Plain);
    border7b->setLineWidth(2);

    //eight article thumbnail
   articlelayout8b = new QVBoxLayout();
    iconlayout8b = new QHBoxLayout();
    article8b = new QPushButton();
    article8b->setStyleSheet("QPushButton {border-image:url(:/thumbnail8.jpg);}");
    article8b->setFlat(true);
    article8b->setMaximumWidth(260);
    article8b->setMinimumHeight(430);
    heart8b = new QPushButton();
    heart8b->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart8b->setMaximumWidth(20);
    plus8b = new QPushButton();
    plus8b->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus8b->setMaximumWidth(20);
    share8thb = new QPushButton();
    share8thb->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share8thb->setMaximumWidth(20);
    iconlayout8b->addWidget(heart8b);
    spacing8b = new QLabel();
    spacing8b->setMaximumWidth(200);
    iconlayout8b->addWidget(spacing8b);
    iconlayout8b->addWidget(plus8b);
    iconlayout8b->addWidget(share8thb);
    articlelayout8b->addWidget(article8b);
    articlelayout8b->addLayout(iconlayout8b);
    articlelayout8b->setMargin(0);
    QFrame *border8b = new QFrame();
    border8b->setMaximumWidth(260);
    border8b->setMinimumHeight(460);
    border8b->setLayout(articlelayout8b);
    border8b->setFrameStyle(QFrame::Box | QFrame::Plain);
    border8b->setLineWidth(2);

    //THIRD STACK - 8 thumnails c's

    //first article thumbnail
    articlelayout1c = new QVBoxLayout();
    iconlayout1c = new QHBoxLayout();
    article1c = new QPushButton();
    article1c->setStyleSheet("QPushButton {border-image:url(:/thumbnail1.jpg);}");
    article1c->setFlat(true);
    article1c->setMaximumWidth(260);
    article1c->setMinimumHeight(430);
    heart1c = new QPushButton();
    heart1c->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart1c->setMaximumWidth(20);
    plus1c = new QPushButton();
    plus1c->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus1c->setMaximumWidth(20);
    share1thc = new QPushButton();
    share1thc->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share1thc->setMaximumWidth(20);
    iconlayout1c->addWidget(heart1c);
    spacingc = new QLabel();
    spacingc->setMaximumWidth(200);
    iconlayout1c->addWidget(spacingc);
    iconlayout1c->addWidget(plus1c);
    iconlayout1c->addWidget(share1thc);
    articlelayout1c->addWidget(article1c);
    articlelayout1c->addLayout(iconlayout1c);
    articlelayout1c->setMargin(0);
    QFrame *border1c = new QFrame();
    border1c->setMaximumWidth(260);
    border1c->setMinimumHeight(460);
    border1c->setLayout(articlelayout1c);
    border1c->setFrameStyle(QFrame::Box | QFrame::Plain);
    border1c->setLineWidth(2);

    //second article thumbnail
    articlelayout2c = new QVBoxLayout();
    iconlayout2c = new QHBoxLayout();
    article2c = new QPushButton();
    article2c->setStyleSheet("QPushButton {border-image:url(:/thumbnail2.jpg);}");
    article2c->setFlat(true);
    article2c->setMaximumWidth(260);
    article2c->setMinimumHeight(430);
    heart2c = new QPushButton();
    heart2c->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart2c->setMaximumWidth(20);
    plus2c = new QPushButton();
    plus2c->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus2c->setMaximumWidth(20);
    share2thc = new QPushButton();
    share2thc->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share2thc->setMaximumWidth(20);
    iconlayout2c->addWidget(heart2c);
    spacing2c = new QLabel();
    spacing2c->setMaximumWidth(200);
    iconlayout2c->addWidget(spacing2c);
    iconlayout2c->addWidget(plus2c);
    iconlayout2c->addWidget(share2thc);
    articlelayout2c->addWidget(article2c);
    articlelayout2c->addLayout(iconlayout2c);
    articlelayout2c->setMargin(0);
    QFrame *border2c = new QFrame();
    border2c->setMaximumWidth(260);
    border2c->setMinimumHeight(460);
    border2c->setLayout(articlelayout2c);
    border2c->setFrameStyle(QFrame::Box | QFrame::Plain);
    border2c->setLineWidth(2);

    //third article thumbnail
    articlelayout3c = new QVBoxLayout();
    iconlayout3c = new QHBoxLayout();
    article3c = new QPushButton();
    article3c->setStyleSheet("QPushButton {border-image:url(:/thumbnail3.jpg);}");
    article3c->setFlat(true);
    article3c->setMaximumWidth(260);
    article3c->setMinimumHeight(430);
    heart3c = new QPushButton();
    heart3c->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart3c->setMaximumWidth(20);
    plus3c = new QPushButton();
    plus3c->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus3c->setMaximumWidth(20);
    share3thc = new QPushButton();
    share3thc->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share3thc->setMaximumWidth(20);
    iconlayout3c->addWidget(heart3c);
    spacing3c = new QLabel();
    spacing3c->setMaximumWidth(200);
    iconlayout3c->addWidget(spacing3c);
    iconlayout3c->addWidget(plus3c);
    iconlayout3c->addWidget(share3thc);
    articlelayout3c->addWidget(article3c);
    articlelayout3c->addLayout(iconlayout3c);
    articlelayout3c->setMargin(0);
    QFrame *border3c = new QFrame();
    border3c->setMaximumWidth(260);
    border3c->setMinimumHeight(460);
    border3c->setLayout(articlelayout3c);
    border3c->setFrameStyle(QFrame::Box | QFrame::Plain);
    border3c->setLineWidth(2);

    //fourth article thumbnail
    articlelayout4c = new QVBoxLayout();
    iconlayout4c = new QHBoxLayout();
    article4c = new QPushButton();
    article4c->setStyleSheet("QPushButton {border-image:url(:/thumbnail4.jpg);}");
    article4c->setFlat(true);
    article4c->setMaximumWidth(260);
    article4c->setMinimumHeight(430);
    heart4c = new QPushButton();
    heart4c->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart4c->setMaximumWidth(20);
    plus4c = new QPushButton();
    plus4c->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus4c->setMaximumWidth(20);
    share4thc = new QPushButton();
    share4thc->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share4thc->setMaximumWidth(20);
    iconlayout4c->addWidget(heart4c);
    spacing4c = new QLabel();
    spacing4c->setMaximumWidth(200);
    iconlayout4c->addWidget(spacing4c);
    iconlayout4c->addWidget(plus4c);
    iconlayout4c->addWidget(share4thc);
    articlelayout4c->addWidget(article4c);
    articlelayout4c->addLayout(iconlayout4c);
    articlelayout4c->setMargin(0);
    QFrame *border4c = new QFrame();
    border4c->setMaximumWidth(260);
    border4c->setMinimumHeight(460);
    border4c->setLayout(articlelayout4c);
    border4c->setFrameStyle(QFrame::Box | QFrame::Plain);
    border4c->setLineWidth(2);

    //fifth article thumbnail
    articlelayout5c = new QVBoxLayout();
    iconlayout5c = new QHBoxLayout();
    article5c = new QPushButton();
    article5c->setStyleSheet("QPushButton {border-image:url(:/thumbnail5.jpg);}");
    article5c->setFlat(true);
    article5c->setMaximumWidth(260);
    article5c->setMinimumHeight(430);
    heart5c = new QPushButton();
    heart5c->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart5c->setMaximumWidth(20);
    plus5c = new QPushButton();
    plus5c->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus5c->setMaximumWidth(20);
    share5thc = new QPushButton();
    share5thc->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share5thc->setMaximumWidth(20);
    iconlayout5c->addWidget(heart5c);
    spacing5c = new QLabel();
    spacing5c->setMaximumWidth(200);
    iconlayout5c->addWidget(spacing5c);
    iconlayout5c->addWidget(plus5c);
    iconlayout5c->addWidget(share5thc);
    articlelayout5c->addWidget(article5c);
    articlelayout5c->addLayout(iconlayout5c);
    articlelayout5c->setMargin(0);
    QFrame *border5c = new QFrame();
    border5c->setMaximumWidth(260);
    border5c->setMinimumHeight(460);
    border5c->setLayout(articlelayout5c);
    border5c->setFrameStyle(QFrame::Box | QFrame::Plain);
    border5c->setLineWidth(2);

    //sixth article thumbnail
    articlelayout6c = new QVBoxLayout();
    iconlayout6c = new QHBoxLayout();
    article6c = new QPushButton();
    article6c->setStyleSheet("QPushButton {border-image:url(:/thumbnail6.jpg);}");
    article6c->setFlat(true);
    article6c->setMaximumWidth(260);
    article6c->setMinimumHeight(430);
    heart6c = new QPushButton();
    heart6c->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart6c->setMaximumWidth(20);
    plus6c = new QPushButton();
    plus6c->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus6c->setMaximumWidth(20);
    share6thc = new QPushButton();
    share6thc->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share6thc->setMaximumWidth(20);
    iconlayout6c->addWidget(heart6c);
    spacing6c = new QLabel();
    spacing6c->setMaximumWidth(200);
    iconlayout6c->addWidget(spacing6c);
    iconlayout6c->addWidget(plus6c);
    iconlayout6c->addWidget(share6thc);
    articlelayout6c->addWidget(article6c);
    articlelayout6c->addLayout(iconlayout6c);
    articlelayout6c->setMargin(0);
    QFrame *border6c = new QFrame();
    border6c->setMaximumWidth(260);
    border6c->setMinimumHeight(460);
    border6c->setLayout(articlelayout6c);
    border6c->setFrameStyle(QFrame::Box | QFrame::Plain);
    border6c->setLineWidth(2);

    //seventh article thumbnail
    articlelayout7c = new QVBoxLayout();
    iconlayout7c = new QHBoxLayout();
    article7c = new QPushButton();
    article7c->setStyleSheet("QPushButton {border-image:url(:/thumbnail7.jpg);}");
    article7c->setFlat(true);
    article7c->setMaximumWidth(260);
    article7c->setMinimumHeight(430);
    heart7c = new QPushButton();
    heart7c->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart7c->setMaximumWidth(20);
    plus7c= new QPushButton();
    plus7c->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus7c->setMaximumWidth(20);
    share7thc = new QPushButton();
    share7thc->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share7thc->setMaximumWidth(20);
    iconlayout7c->addWidget(heart7c);
    spacing7c = new QLabel();
    spacing7c->setMaximumWidth(200);
    iconlayout7c->addWidget(spacing7c);
    iconlayout7c->addWidget(plus7c);
    iconlayout7c->addWidget(share7thc);
    articlelayout7c->addWidget(article7c);
    articlelayout7c->addLayout(iconlayout7c);
    articlelayout7c->setMargin(0);
    QFrame *border7c = new QFrame();
    border7c->setMaximumWidth(260);
    border7c->setMinimumHeight(460);
    border7c->setLayout(articlelayout7c);
    border7c->setFrameStyle(QFrame::Box | QFrame::Plain);
    border7c->setLineWidth(2);

    //eight article thumbnail
   articlelayout8c = new QVBoxLayout();
    iconlayout8c = new QHBoxLayout();
    article8c = new QPushButton();
    article8c->setStyleSheet("QPushButton {border-image:url(:/thumbnail8.jpg);}");
    article8c->setFlat(true);
    article8c->setMaximumWidth(260);
    article8c->setMinimumHeight(430);
    heart8c = new QPushButton();
    heart8c->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart8c->setMaximumWidth(20);
    plus8c = new QPushButton();
    plus8c->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus8c->setMaximumWidth(20);
    share8thc = new QPushButton();
    share8thc->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share8thc->setMaximumWidth(20);
    iconlayout8c->addWidget(heart8c);
    spacing8c = new QLabel();
    spacing8c->setMaximumWidth(200);
    iconlayout8c->addWidget(spacing8c);
    iconlayout8c->addWidget(plus8c);
    iconlayout8c->addWidget(share8thc);
    articlelayout8c->addWidget(article8c);
    articlelayout8c->addLayout(iconlayout8c);
    articlelayout8c->setMargin(0);
    QFrame *border8c = new QFrame();
    border8c->setMaximumWidth(260);
    border8c->setMinimumHeight(460);
    border8c->setLayout(articlelayout8c);
    border8c->setFrameStyle(QFrame::Box | QFrame::Plain);
    border8c->setLineWidth(2);

    //FOURTH STACK - 8 thumnails d's

    //first article thumbnail
    articlelayout1d = new QVBoxLayout();
    iconlayout1d = new QHBoxLayout();
    article1d = new QPushButton();
    article1d->setStyleSheet("QPushButton {border-image:url(:/thumbnail1.jpg);}");
    article1d->setFlat(true);
    article1d->setMaximumWidth(260);
    article1d->setMinimumHeight(430);
    heart1d = new QPushButton();
    heart1d->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart1d->setMaximumWidth(20);
    plus1d = new QPushButton();
    plus1d->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus1d->setMaximumWidth(20);
    share1thd = new QPushButton();
    share1thd->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share1thd->setMaximumWidth(20);
    iconlayout1d->addWidget(heart1d);
    spacingd = new QLabel();
    spacingd->setMaximumWidth(200);
    iconlayout1d->addWidget(spacingd);
    iconlayout1d->addWidget(plus1d);
    iconlayout1d->addWidget(share1thd);
    articlelayout1d->addWidget(article1d);
    articlelayout1d->addLayout(iconlayout1d);
    articlelayout1d->setMargin(0);
    QFrame *border1d = new QFrame();
    border1d->setMaximumWidth(260);
    border1d->setMinimumHeight(460);
    border1d->setLayout(articlelayout1d);
    border1d->setFrameStyle(QFrame::Box | QFrame::Plain);
    border1d->setLineWidth(2);

    //second article thumbnail
    articlelayout2d = new QVBoxLayout();
    iconlayout2d = new QHBoxLayout();
    article2d = new QPushButton();
    article2d->setStyleSheet("QPushButton {border-image:url(:/thumbnail2.jpg);}");
    article2d->setFlat(true);
    article2d->setMaximumWidth(260);
    article2d->setMinimumHeight(430);
    heart2d = new QPushButton();
    heart2d->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart2d->setMaximumWidth(20);
    plus2d = new QPushButton();
    plus2d->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus2d->setMaximumWidth(20);
    share2thd = new QPushButton();
    share2thd->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share2thd->setMaximumWidth(20);
    iconlayout2d->addWidget(heart2d);
    spacing2d = new QLabel();
    spacing2d->setMaximumWidth(200);
    iconlayout2d->addWidget(spacing2d);
    iconlayout2d->addWidget(plus2d);
    iconlayout2d->addWidget(share2thd);
    articlelayout2d->addWidget(article2d);
    articlelayout2d->addLayout(iconlayout2d);
    articlelayout2d->setMargin(0);
    QFrame *border2d = new QFrame();
    border2d->setMaximumWidth(260);
    border2d->setMinimumHeight(460);
    border2d->setLayout(articlelayout2d);
    border2d->setFrameStyle(QFrame::Box | QFrame::Plain);
    border2d->setLineWidth(2);

    //third article thumbnail
    articlelayout3d = new QVBoxLayout();
    iconlayout3d = new QHBoxLayout();
    article3d = new QPushButton();
    article3d->setStyleSheet("QPushButton {border-image:url(:/thumbnail3.jpg);}");
    article3d->setFlat(true);
    article3d->setMaximumWidth(260);
    article3d->setMinimumHeight(430);
    heart3d = new QPushButton();
    heart3d->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart3d->setMaximumWidth(20);
    plus3d = new QPushButton();
    plus3d->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus3d->setMaximumWidth(20);
    share3thd = new QPushButton();
    share3thd->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share3thd->setMaximumWidth(20);
    iconlayout3d->addWidget(heart3d);
    spacing3d = new QLabel();
    spacing3d->setMaximumWidth(200);
    iconlayout3d->addWidget(spacing3d);
    iconlayout3d->addWidget(plus3d);
    iconlayout3d->addWidget(share3thd);
    articlelayout3d->addWidget(article3d);
    articlelayout3d->addLayout(iconlayout3d);
    articlelayout3d->setMargin(0);
    QFrame *border3d = new QFrame();
    border3d->setMaximumWidth(260);
    border3d->setMinimumHeight(460);
    border3d->setLayout(articlelayout3d);
    border3d->setFrameStyle(QFrame::Box | QFrame::Plain);
    border3d->setLineWidth(2);

    //fourth article thumbnail
    articlelayout4d = new QVBoxLayout();
    iconlayout4d = new QHBoxLayout();
    article4d = new QPushButton();
    article4d->setStyleSheet("QPushButton {border-image:url(:/thumbnail4.jpg);}");
    article4d->setFlat(true);
    article4d->setMaximumWidth(260);
    article4d->setMinimumHeight(430);
    heart4d = new QPushButton();
    heart4d->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart4d->setMaximumWidth(20);
    plus4d = new QPushButton();
    plus4d->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus4d->setMaximumWidth(20);
    share4thd = new QPushButton();
    share4thd->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share4thd->setMaximumWidth(20);
    iconlayout4d->addWidget(heart4d);
    spacing4d = new QLabel();
    spacing4d->setMaximumWidth(200);
    iconlayout4d->addWidget(spacing4d);
    iconlayout4d->addWidget(plus4d);
    iconlayout4d->addWidget(share4thd);
    articlelayout4d->addWidget(article4d);
    articlelayout4d->addLayout(iconlayout4d);
    articlelayout4d->setMargin(0);
    QFrame *border4d = new QFrame();
    border4d->setMaximumWidth(260);
    border4d->setMinimumHeight(460);
    border4d->setLayout(articlelayout4d);
    border4d->setFrameStyle(QFrame::Box | QFrame::Plain);
    border4d->setLineWidth(2);

    //fifth article thumbnail
    articlelayout5d = new QVBoxLayout();
    iconlayout5d = new QHBoxLayout();
    article5d = new QPushButton();
    article5d->setStyleSheet("QPushButton {border-image:url(:/thumbnail5.jpg);}");
    article5d->setFlat(true);
    article5d->setMaximumWidth(260);
    article5d->setMinimumHeight(430);
    heart5d = new QPushButton();
    heart5d->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart5d->setMaximumWidth(20);
    plus5d = new QPushButton();
    plus5d->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus5d->setMaximumWidth(20);
    share5thd = new QPushButton();
    share5thd->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share5thd->setMaximumWidth(20);
    iconlayout5d->addWidget(heart5d);
    spacing5d = new QLabel();
    spacing5d->setMaximumWidth(200);
    iconlayout5d->addWidget(spacing5d);
    iconlayout5d->addWidget(plus5d);
    iconlayout5d->addWidget(share5thd);
    articlelayout5d->addWidget(article5d);
    articlelayout5d->addLayout(iconlayout5d);
    articlelayout5d->setMargin(0);
    QFrame *border5d = new QFrame();
    border5d->setMaximumWidth(260);
    border5d->setMinimumHeight(460);
    border5d->setLayout(articlelayout5d);
    border5d->setFrameStyle(QFrame::Box | QFrame::Plain);
    border5d->setLineWidth(2);

    //sixth article thumbnail
    articlelayout6d = new QVBoxLayout();
    iconlayout6d = new QHBoxLayout();
    article6d = new QPushButton();
    article6d->setStyleSheet("QPushButton {border-image:url(:/thumbnail6.jpg);}");
    article6d->setFlat(true);
    article6d->setMaximumWidth(260);
    article6d->setMinimumHeight(430);
    heart6d = new QPushButton();
    heart6d->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart6d->setMaximumWidth(20);
    plus6d = new QPushButton();
    plus6d->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus6d->setMaximumWidth(20);
    share6thd = new QPushButton();
    share6thd->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share6thd->setMaximumWidth(20);
    iconlayout6d->addWidget(heart6d);
    spacing6d = new QLabel();
    spacing6d->setMaximumWidth(200);
    iconlayout6d->addWidget(spacing6d);
    iconlayout6d->addWidget(plus6d);
    iconlayout6d->addWidget(share6thd);
    articlelayout6d->addWidget(article6d);
    articlelayout6d->addLayout(iconlayout6d);
    articlelayout6d->setMargin(0);
    QFrame *border6d = new QFrame();
    border6d->setMaximumWidth(260);
    border6d->setMinimumHeight(460);
    border6d->setLayout(articlelayout6d);
    border6d->setFrameStyle(QFrame::Box | QFrame::Plain);
    border6d->setLineWidth(2);

    //seventh article thumbnail
    articlelayout7d = new QVBoxLayout();
    iconlayout7d = new QHBoxLayout();
    article7d = new QPushButton();
    article7d->setStyleSheet("QPushButton {border-image:url(:/thumbnail7.jpg);}");
    article7d->setFlat(true);
    article7d->setMaximumWidth(260);
    article7d->setMinimumHeight(430);
    heart7d = new QPushButton();
    heart7d->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart7d->setMaximumWidth(20);
    plus7d = new QPushButton();
    plus7d->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus7d->setMaximumWidth(20);
    share7thd = new QPushButton();
    share7thd->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share7thd->setMaximumWidth(20);
    iconlayout7d->addWidget(heart7d);
    spacing7d = new QLabel();
    spacing7d->setMaximumWidth(200);
    iconlayout7d->addWidget(spacing7d);
    iconlayout7d->addWidget(plus7d);
    iconlayout7d->addWidget(share7thd);
    articlelayout7d->addWidget(article7d);
    articlelayout7d->addLayout(iconlayout7d);
    articlelayout7d->setMargin(0);
    QFrame *border7d = new QFrame();
    border7d->setMaximumWidth(260);
    border7d->setMinimumHeight(460);
    border7d->setLayout(articlelayout7d);
    border7d->setFrameStyle(QFrame::Box | QFrame::Plain);
    border7d->setLineWidth(2);

    //eight article thumbnail
   articlelayout8d = new QVBoxLayout();
    iconlayout8d = new QHBoxLayout();
    article8d = new QPushButton();
    article8d->setStyleSheet("QPushButton {border-image:url(:/thumbnail8.jpg);}");
    article8d->setFlat(true);
    article8d->setMaximumWidth(260);
    article8d->setMinimumHeight(430);
    heart8d = new QPushButton();
    heart8d->setStyleSheet("QPushButton {border-image:url(:/heart.jpg);}");
    heart8d->setMaximumWidth(20);
    plus8d = new QPushButton();
    plus8d->setStyleSheet("QPushButton {border-image:url(:/add.jpg);}");
    plus8d->setMaximumWidth(20);
    share8thd = new QPushButton();
    share8thd->setStyleSheet("QPushButton {border-image:url(:/share.jpg);}");
    share8thd->setMaximumWidth(20);
    iconlayout8d->addWidget(heart8d);
    spacing8d = new QLabel();
    spacing8d->setMaximumWidth(200);
    iconlayout8d->addWidget(spacing8d);
    iconlayout8d->addWidget(plus8d);
    iconlayout8d->addWidget(share8thd);
    articlelayout8d->addWidget(article8d);
    articlelayout8d->addLayout(iconlayout8d);
    articlelayout8d->setMargin(0);
    QFrame *border8d = new QFrame();
    border8d->setMaximumWidth(260);
    border8d->setMinimumHeight(460);
    border8d->setLayout(articlelayout8d);
    border8d->setFrameStyle(QFrame::Box | QFrame::Plain);
    border8d->setLineWidth(2);

    rightArrow2 = new QPushButton();
    rightArrow2->setStyleSheet("QPushButton {border-image:url(:/rightArrow.jpg);}");
    rightArrow2->setFlat(true);
    rightArrow2->setMaximumWidth(35);
    rightArrow2->setMinimumHeight(60);

    //make 4 stacked layouts for my feed
    stackedFeed1 = new QStackedWidget;
    stackedFeed1->addWidget(border1a);
    stackedFeed1->addWidget(border2a);
    stackedFeed1->addWidget(border3a);
    stackedFeed1->addWidget(border4a);
    stackedFeed1->addWidget(border5a);
    stackedFeed1->addWidget(border6a);
    stackedFeed1->addWidget(border7a);
    stackedFeed1->addWidget(border8a);
    stackedFeed1->setCurrentWidget(border1a);

    //make 4 stacked layouts for my feed
    stackedFeed2 = new QStackedWidget;
    stackedFeed2->addWidget(border1b);
    stackedFeed2->addWidget(border2b);
    stackedFeed2->addWidget(border3b);
    stackedFeed2->addWidget(border4b);
    stackedFeed2->addWidget(border5b);
    stackedFeed2->addWidget(border6b);
    stackedFeed2->addWidget(border7b);
    stackedFeed2->addWidget(border8b);
    stackedFeed2->setCurrentWidget(border2b);

    //make 4 stacked layouts for my feed
    stackedFeed3 = new QStackedWidget;
    stackedFeed3->addWidget(border1c);
    stackedFeed3->addWidget(border2c);
    stackedFeed3->addWidget(border3c);
    stackedFeed3->addWidget(border4c);
    stackedFeed3->addWidget(border5c);
    stackedFeed3->addWidget(border6c);
    stackedFeed3->addWidget(border7c);
    stackedFeed3->addWidget(border8c);
    stackedFeed3->setCurrentWidget(border3c);

    //make 4 stacked layouts for my feed
    stackedFeed4 = new QStackedWidget;
    stackedFeed4->addWidget(border1d);
    stackedFeed4->addWidget(border2d);
    stackedFeed4->addWidget(border3d);
    stackedFeed4->addWidget(border4d);
    stackedFeed4->addWidget(border5d);
    stackedFeed4->addWidget(border6d);
    stackedFeed4->addWidget(border7d);
    stackedFeed4->addWidget(border8d);
    stackedFeed4->setCurrentWidget(border4d);

    feedlayout->setSpacing(100);
    feedlayout->setMargin(100);
    feedlayout->addWidget(leftArrow2, 0, Qt::AlignRight );
    feedlayout->addWidget(stackedFeed1);
    feedlayout->addWidget(stackedFeed2);
    feedlayout->addWidget(stackedFeed3);
    feedlayout->addWidget(stackedFeed4);
    feedlayout->addWidget(rightArrow2, 0, Qt::AlignLeft );

    topnewslabel = new QLabel("TOP NEWS");
    topnewslabel->setStyleSheet("QLabel{font-size: 30px; font-weight: bold;}");
    topnewslabel->setContentsMargins(550,30,30,30);
    vlayout->addWidget(topnewslabel);
    vlayout->addLayout(topNewslayout);
    spacingFeeds = new QLabel();
    spacingFeeds2 = new QLabel();
    spacingFeeds3 = new QLabel();
    vlayout->addWidget(spacingFeeds);
    vlayout->addWidget(spacingFeeds2);
    vlayout->addWidget(spacingFeeds3);
    myfeedlabel = new QLabel("YOUR FEED");
    myfeedlabel->setStyleSheet("QLabel{font-size: 20px; font-weight: bold;}");
    myfeedlabel->setContentsMargins(100, 0,30,30);
    vlayout->addWidget(myfeedlabel);
    vlayout->addLayout(feedlayout);

    //setting pages to keep track of current page that is being viewed
    //main page with feed of articles for user to select
    stackedWidget = new QStackedWidget;
    mainPageWidget = new QScrollArea;
    //mainPageWidget->setLayout(vlayout);
    //mainPageWidget->setStyleSheet("QWidget{background-color: white;}");
    stackedWidget->addWidget(mainPageWidget);

    articlePageWidget1 = new QScrollArea;
    stackedWidget->addWidget(articlePageWidget1);
    articlePageWidget2 = new QScrollArea;
    stackedWidget->addWidget(articlePageWidget2);
    articlePageWidget3 = new QScrollArea;
    stackedWidget->addWidget(articlePageWidget3);
    articlePageWidget4 = new QScrollArea;
    stackedWidget->addWidget(articlePageWidget4);
    articlePageWidget5 = new QScrollArea;
    stackedWidget->addWidget(articlePageWidget5);
    articlePageWidget6 = new QScrollArea;
    stackedWidget->addWidget(articlePageWidget6);
    articlePageWidget7 = new QScrollArea;
    stackedWidget->addWidget(articlePageWidget7);
    articlePageWidget8 = new QScrollArea;
    stackedWidget->addWidget(articlePageWidget8);
    articlePageWidget9 = new QScrollArea;
    stackedWidget->addWidget(articlePageWidget9);
    articlePageWidget10 = new QScrollArea;
    stackedWidget->addWidget(articlePageWidget10);

    //add favourites,settings, signin to pages
    favouritesPageWidget = new QScrollArea;
    stackedWidget->addWidget(favouritesPageWidget);
    settingsPageWidget = new QScrollArea;
    stackedWidget->addWidget(settingsPageWidget);
    signinPageWidget = new QScrollArea;
    stackedWidget->addWidget(signinPageWidget);
    searchPageWidget = new QScrollArea;
    stackedWidget->addWidget(searchPageWidget);

    //set page layout with scrollbar
    QWidget *widgetmain = new QWidget();
    widgetmain->setStyleSheet("QWidget {background-color: white;}");
    widgetmain->setLayout(vlayout);

    mainPageWidget->setWidgetResizable(true);
    mainPageWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mainPageWidget->setWidget(widgetmain);

    //set current page as the main page
    stackedWidget->setCurrentWidget(mainPageWidget);
    setCentralWidget(stackedWidget);

       connect(article1a, &QPushButton::clicked,
                 this, &Display::displayArticle1Handler);
        connect(article2a, &QPushButton::clicked,
                 this, &Display::displayArticle2Handler);
       connect(article3a, &QPushButton::clicked,
                 this, &Display::displayArticle3Handler);
       connect(article4a, &QPushButton::clicked,
                 this, &Display::displayArticle4Handler);
      connect(article5a, &QPushButton::clicked,
                 this, &Display::displayArticle5Handler);
       connect(article6a, &QPushButton::clicked,
                 this, &Display::displayArticle6Handler);
       connect(article7a, &QPushButton::clicked,
                 this, &Display::displayArticle7Handler);
      connect(article8a, &QPushButton::clicked,
                 this, &Display::displayArticle8Handler);

      connect(article1b, &QPushButton::clicked,
                this, &Display::displayArticle1Handler);
       connect(article2b, &QPushButton::clicked,
                this, &Display::displayArticle2Handler);
      connect(article3b, &QPushButton::clicked,
                this, &Display::displayArticle3Handler);
      connect(article4b, &QPushButton::clicked,
                this, &Display::displayArticle4Handler);
     connect(article5b, &QPushButton::clicked,
                this, &Display::displayArticle5Handler);
      connect(article6b, &QPushButton::clicked,
                this, &Display::displayArticle6Handler);
      connect(article7b, &QPushButton::clicked,
                this, &Display::displayArticle7Handler);
     connect(article8b, &QPushButton::clicked,
                this, &Display::displayArticle8Handler);

     connect(article1c, &QPushButton::clicked,
               this, &Display::displayArticle1Handler);
      connect(article2c, &QPushButton::clicked,
               this, &Display::displayArticle2Handler);
     connect(article3c, &QPushButton::clicked,
               this, &Display::displayArticle3Handler);
     connect(article4c, &QPushButton::clicked,
               this, &Display::displayArticle4Handler);
    connect(article5c, &QPushButton::clicked,
               this, &Display::displayArticle5Handler);
     connect(article6c, &QPushButton::clicked,
               this, &Display::displayArticle6Handler);
     connect(article7c, &QPushButton::clicked,
               this, &Display::displayArticle7Handler);
    connect(article8c, &QPushButton::clicked,
               this, &Display::displayArticle8Handler);

    connect(article1d, &QPushButton::clicked,
              this, &Display::displayArticle1Handler);
     connect(article2d, &QPushButton::clicked,
              this, &Display::displayArticle2Handler);
    connect(article3d, &QPushButton::clicked,
              this, &Display::displayArticle3Handler);
    connect(article4d, &QPushButton::clicked,
              this, &Display::displayArticle4Handler);
   connect(article5d, &QPushButton::clicked,
              this, &Display::displayArticle5Handler);
    connect(article6d, &QPushButton::clicked,
              this, &Display::displayArticle6Handler);
    connect(article7d, &QPushButton::clicked,
              this, &Display::displayArticle7Handler);
   connect(article8d, &QPushButton::clicked,
              this, &Display::displayArticle8Handler);


     connect(article5top, &QPushButton::clicked,
                        this, &Display::displayArticle5Handler);
       connect(article9, &QPushButton::clicked,
                 this, &Display::displayArticle9Handler);
       connect(article10, &QPushButton::clicked,
                 this, &Display::displayArticle10Handler);

       connect(rightArrow, &QPushButton::clicked,
                 this, &Display::topnextHandler);
       connect(leftArrow, &QPushButton::clicked,
                 this, &Display::topprevHandler);
       connect(rightArrow2, &QPushButton::clicked,
                 this, &Display::feednextHandler);
       connect(leftArrow2, &QPushButton::clicked,
                 this, &Display::feedprevHandler);
       connect(myFeed, &QAction::triggered, this, &Display::backpageHandler);

       //toolbar actions triggered
       connect(searchbar, &QLineEdit::returnPressed, this, &Display::searchHandler);
       connect(favourites, &QAction::triggered, this, &Display::favouritesHandler);
       connect(settings, &QAction::triggered, this, &Display::settingsHandler);
       connect(user, &QAction::triggered, this, &Display::userHandler);

       //sharing from main page
       connect(share1tha, &QPushButton::clicked, this, &Display::shareHandler1);
        connect(share1thb, &QPushButton::clicked, this, &Display::shareHandler1);
         connect(share1thc, &QPushButton::clicked, this, &Display::shareHandler1);
          connect(share1thd, &QPushButton::clicked, this, &Display::shareHandler1);
       connect(share2tha, &QPushButton::clicked, this, &Display::shareHandler2);
        connect(share2thb, &QPushButton::clicked, this, &Display::shareHandler2);
         connect(share2thc, &QPushButton::clicked, this, &Display::shareHandler2);
          connect(share2thd, &QPushButton::clicked, this, &Display::shareHandler2);
       connect(share3tha, &QPushButton::clicked, this, &Display::shareHandler3);
       connect(share3thb, &QPushButton::clicked, this, &Display::shareHandler3);
       connect(share3thc, &QPushButton::clicked, this, &Display::shareHandler3);
       connect(share3thd, &QPushButton::clicked, this, &Display::shareHandler3);
       connect(share4tha, &QPushButton::clicked, this, &Display::shareHandler4);
       connect(share4thb, &QPushButton::clicked, this, &Display::shareHandler4);
       connect(share4thc, &QPushButton::clicked, this, &Display::shareHandler4);
       connect(share4thd, &QPushButton::clicked, this, &Display::shareHandler4);
       connect(share5tha, &QPushButton::clicked, this, &Display::shareHandler5);
       connect(share5thb, &QPushButton::clicked, this, &Display::shareHandler5);
       connect(share5thc, &QPushButton::clicked, this, &Display::shareHandler5);
       connect(share5thd, &QPushButton::clicked, this, &Display::shareHandler5);
       connect(share6tha, &QPushButton::clicked, this, &Display::shareHandler6);
       connect(share6thb, &QPushButton::clicked, this, &Display::shareHandler6);
       connect(share6thc, &QPushButton::clicked, this, &Display::shareHandler6);
       connect(share6thd, &QPushButton::clicked, this, &Display::shareHandler6);
       connect(share7tha, &QPushButton::clicked, this, &Display::shareHandler7);
       connect(share7thb, &QPushButton::clicked, this, &Display::shareHandler7);
       connect(share7thc, &QPushButton::clicked, this, &Display::shareHandler7);
       connect(share7thd, &QPushButton::clicked, this, &Display::shareHandler7);
       connect(share8tha, &QPushButton::clicked, this, &Display::shareHandler8);
       connect(share8thb, &QPushButton::clicked, this, &Display::shareHandler8);
       connect(share8thc, &QPushButton::clicked, this, &Display::shareHandler8);
       connect(share8thd, &QPushButton::clicked, this, &Display::shareHandler8);

     //liking from main page
       connect(heart1a, &QPushButton::clicked, this, &Display::likedHandler1a);
       connect(heart1b, &QPushButton::clicked, this, &Display::likedHandler1b);
       connect(heart1c, &QPushButton::clicked, this, &Display::likedHandler1c);
       connect(heart1d, &QPushButton::clicked, this, &Display::likedHandler1d);
       connect(heart2a, &QPushButton::clicked, this, &Display::likedHandler2a);
       connect(heart2b, &QPushButton::clicked, this, &Display::likedHandler2b);
       connect(heart2c, &QPushButton::clicked, this, &Display::likedHandler2c);
       connect(heart2d, &QPushButton::clicked, this, &Display::likedHandler2d);
       connect(heart3a, &QPushButton::clicked, this, &Display::likedHandler3a);
       connect(heart3b, &QPushButton::clicked, this, &Display::likedHandler3b);
       connect(heart3c, &QPushButton::clicked, this, &Display::likedHandler3c);
       connect(heart3d, &QPushButton::clicked, this, &Display::likedHandler3d);
       connect(heart4a, &QPushButton::clicked, this, &Display::likedHandler4a);
       connect(heart4b, &QPushButton::clicked, this, &Display::likedHandler4b);
       connect(heart4c, &QPushButton::clicked, this, &Display::likedHandler4c);
       connect(heart4d, &QPushButton::clicked, this, &Display::likedHandler4d);
       connect(heart5a, &QPushButton::clicked, this, &Display::likedHandler5a);
       connect(heart5b, &QPushButton::clicked, this, &Display::likedHandler5b);
       connect(heart5c, &QPushButton::clicked, this, &Display::likedHandler5c);
       connect(heart5d, &QPushButton::clicked, this, &Display::likedHandler5d);
       connect(heart6a, &QPushButton::clicked, this, &Display::likedHandler6a);
       connect(heart6b, &QPushButton::clicked, this, &Display::likedHandler6b);
       connect(heart6c, &QPushButton::clicked, this, &Display::likedHandler6c);
       connect(heart6d, &QPushButton::clicked, this, &Display::likedHandler6d);
       connect(heart7a, &QPushButton::clicked, this, &Display::likedHandler7a);
       connect(heart7b, &QPushButton::clicked, this, &Display::likedHandler7b);
       connect(heart7c, &QPushButton::clicked, this, &Display::likedHandler7c);
       connect(heart7d, &QPushButton::clicked, this, &Display::likedHandler7d);
       connect(heart8a, &QPushButton::clicked, this, &Display::likedHandler8a);
       connect(heart8b, &QPushButton::clicked, this, &Display::likedHandler8b);
       connect(heart8c, &QPushButton::clicked, this, &Display::likedHandler8c);
       connect(heart8d, &QPushButton::clicked, this, &Display::likedHandler8d);

      //add to favourites from main page
      connect(plus1a, &QPushButton::clicked, this, &Display::addtoFavouritesHandler1);
       connect(plus1b, &QPushButton::clicked, this, &Display::addtoFavouritesHandler1);
        connect(plus1c, &QPushButton::clicked, this, &Display::addtoFavouritesHandler1);
         connect(plus1d, &QPushButton::clicked, this, &Display::addtoFavouritesHandler1);
        connect(plus2a, &QPushButton::clicked, this, &Display::addtoFavouritesHandler2);
        connect(plus2b, &QPushButton::clicked, this, &Display::addtoFavouritesHandler2);
        connect(plus2c, &QPushButton::clicked, this, &Display::addtoFavouritesHandler2);
        connect(plus2d, &QPushButton::clicked, this, &Display::addtoFavouritesHandler2);
        connect(plus3a, &QPushButton::clicked, this, &Display::addtoFavouritesHandler3);
        connect(plus3b, &QPushButton::clicked, this, &Display::addtoFavouritesHandler3);
        connect(plus3c, &QPushButton::clicked, this, &Display::addtoFavouritesHandler3);
        connect(plus3d, &QPushButton::clicked, this, &Display::addtoFavouritesHandler3);
        connect(plus4a, &QPushButton::clicked, this, &Display::addtoFavouritesHandler4);
        connect(plus4b, &QPushButton::clicked, this, &Display::addtoFavouritesHandler4);
        connect(plus4c, &QPushButton::clicked, this, &Display::addtoFavouritesHandler4);
        connect(plus4d, &QPushButton::clicked, this, &Display::addtoFavouritesHandler4);
        connect(plus5a, &QPushButton::clicked, this, &Display::addtoFavouritesHandler5);
        connect(plus5b, &QPushButton::clicked, this, &Display::addtoFavouritesHandler5);
        connect(plus5c, &QPushButton::clicked, this, &Display::addtoFavouritesHandler5);
        connect(plus5d, &QPushButton::clicked, this, &Display::addtoFavouritesHandler5);
        connect(plus6a, &QPushButton::clicked, this, &Display::addtoFavouritesHandler6);
        connect(plus6b, &QPushButton::clicked, this, &Display::addtoFavouritesHandler6);
        connect(plus6c, &QPushButton::clicked, this, &Display::addtoFavouritesHandler6);
        connect(plus6d, &QPushButton::clicked, this, &Display::addtoFavouritesHandler6);
        connect(plus7a, &QPushButton::clicked, this, &Display::addtoFavouritesHandler7);
        connect(plus7b, &QPushButton::clicked, this, &Display::addtoFavouritesHandler7);
        connect(plus7c, &QPushButton::clicked, this, &Display::addtoFavouritesHandler7);
        connect(plus7d, &QPushButton::clicked, this, &Display::addtoFavouritesHandler7);
        connect(plus8a, &QPushButton::clicked, this, &Display::addtoFavouritesHandler8);
        connect(plus8b, &QPushButton::clicked, this, &Display::addtoFavouritesHandler8);
        connect(plus8c, &QPushButton::clicked, this, &Display::addtoFavouritesHandler8);
        connect(plus8d, &QPushButton::clicked, this, &Display::addtoFavouritesHandler8);


}

void Display::displayArticle1Handler(){

    vlayout1 = new QVBoxLayout();
    //article image
     QPixmap articleImg1(":/1.jpg");
     img_label = new QLabel();
     title_label = new QLabel();
     text_label = new QLabel();
     text_label->setWordWrap(true);
     text_label->setContentsMargins(200,0,100,0);

     spacingRow = new QLabel();
     spacingRow2 = new QLabel();
     img_label->setPixmap(articleImg1);
     img_label->setAlignment(Qt::AlignCenter);
     title_label->setAlignment(Qt::AlignCenter);
     title_label->setStyleSheet("QLabel { font-weight: bold; font-size: 30px; text-align: center; }");
     title_label->setText(articles[0].m_title);
     text_label->setText(articles[0].m_text);
     vlayout1->addWidget(spacingRow2);
     vlayout1->addWidget(title_label);
     vlayout1->addWidget(spacingRow);
     vlayout1->addWidget(img_label);
     vlayout1->addWidget(text_label);

     //article buttons for user actions
     like = new QPushButton("LIKE");
     like->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
     share = new QPushButton("SHARE");
     share->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
     addToFavourites = new QPushButton("+SAVE");
     addToFavourites->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
     subscribe = new QPushButton("SUBSCRIBE");
     subscribe->setStyleSheet("QPushButton { background-color: red; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
     subscribe->setFixedWidth(100);
     addComment = new QLineEdit();
     addComment->setFixedWidth(300);
     addComment->setPlaceholderText("Add a public comment...");
     addComment->setAlignment(Qt::AlignCenter);
     loadComments = new QPushButton("Load Comments");
     loadComments->setStyleSheet("QPushButton { background-color:#b8b8b8; font-size: 15px; padding: .5em; border-radius: 7px;}");


          //layout for buttons
          QHBoxLayout *buttonslayout = new QHBoxLayout;
          buttonslayout->addWidget(like);
          buttonslayout->addWidget(share);
          buttonslayout->addWidget(addToFavourites);
          buttonslayout->addWidget(subscribe);
          buttonslayout->setAlignment(Qt::AlignCenter);
          vlayout1->addLayout(buttonslayout);
          QHBoxLayout *add = new QHBoxLayout();
          add->addWidget(addComment);
          add->setAlignment(Qt::AlignHCenter);
          vlayout1->addSpacing(50);
          vlayout1->addLayout(add);
          vlayout1->addSpacing(50);
          vlayout1->addWidget(loadComments);

          //set page layout with scrollbar
          QWidget *widget2 = new QWidget();
          widget2->setStyleSheet("QWidget {background-color: white;}");
          widget2->setLayout(vlayout1);

          //secondPageWidget = new QScrollArea();
          articlePageWidget1->setWidgetResizable(true);
          articlePageWidget1->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
          articlePageWidget1->setWidget(widget2);

        stackedWidget->setCurrentWidget(articlePageWidget1);
        setCentralWidget(stackedWidget);

         connect(share, &QPushButton::clicked, this, &Display::shareHandler1);
         connect(like, &QPushButton::clicked, this, &Display::likedHandler1);
         connect(addToFavourites, &QPushButton::clicked, this, &Display::addtoFavouritesHandler1);
         connect(subscribe, &QPushButton::clicked, this, &Display::subscribeHandler1);
         connect(loadComments, &QPushButton::clicked, this, &Display::loadCommentsHandler1);
         connect(addComment, &QLineEdit::returnPressed, this, &Display::addCommentHandler1);
}

void Display::likedHandler1(){
    like->setText("Liked!");
}

void Display::subscribeHandler1(){
    subscribe->setText("Subscribed!");
}

void Display::loadCommentsHandler1(){
    //article image and title
    QPixmap commentsImg(":/comment1.jpg");
    QLabel *commentlabel = new QLabel();
    commentlabel->setPixmap(commentsImg);
    vlayout1->addWidget(commentlabel);
    loadComments->setText("No more comments");
}

void Display::addCommentHandler1(){
    QString comment = "You: " + addComment->text();
    QLabel *addlabel = new QLabel(comment);
    addlabel->setContentsMargins(100,0,0,0);
    addlabel->setStyleSheet("QLabel {font-size: 20px }");
    vlayout1->addWidget(addlabel);
}

void Display::displayArticle2Handler(){

        vlayout2 = new QVBoxLayout();
        QPixmap articleImg2(":/2.jpg");
        img_label2 = new QLabel();
        title_label2 = new QLabel();
        text_label2 = new QLabel();
        text_label2->setWordWrap(true);
        text_label2->setContentsMargins(200,0,100,0);

         spacingRow3 = new QLabel();
         spacingRow4 = new QLabel();
         img_label2->setPixmap(articleImg2);
         img_label2->setAlignment(Qt::AlignCenter);
         title_label2->setAlignment(Qt::AlignCenter);
         title_label2->setStyleSheet("QLabel { font-weight: bold; font-size: 30px; text-align: center; }");
         title_label2->setText(articles[1].m_title);
         text_label2->setText(articles[1].m_text);
         vlayout2->addWidget(spacingRow3);
         vlayout2->addWidget(title_label2);
         vlayout2->addWidget(spacingRow4);
         vlayout2->addWidget(img_label2);
         vlayout2->addWidget(text_label2);

              //article buttons for user actions
              like2 = new QPushButton("LIKE");
              like2->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              share2 = new QPushButton("SHARE");
              share2->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              addToFavourites2 = new QPushButton("+SAVE");
              addToFavourites2->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe2 = new QPushButton("SUBSCRIBE");
              subscribe2->setStyleSheet("QPushButton { background-color: red; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe2->setFixedWidth(100);
              addComment2 = new QLineEdit();
              addComment2->setFixedWidth(300);
              addComment2->setPlaceholderText("Add a public comment...");
              addComment2->setAlignment(Qt::AlignCenter);
              loadComments2 = new QPushButton("Load Comments");
              loadComments2->setStyleSheet("QPushButton { background-color:#b8b8b8; font-size: 15px; padding: .5em; border-radius: 7px;}");

              //layout for buttons
              QHBoxLayout *buttonslayout2 = new QHBoxLayout;
              buttonslayout2->addWidget(like2);
              buttonslayout2->addWidget(share2);
              buttonslayout2->addWidget(addToFavourites2);
              buttonslayout2->addWidget(subscribe2);
              buttonslayout2->setAlignment(Qt::AlignCenter);
              vlayout2->addLayout(buttonslayout2);
              QHBoxLayout *add = new QHBoxLayout();
              add->addWidget(addComment2);
              add->setAlignment(Qt::AlignHCenter);
              vlayout2->addSpacing(50);
              vlayout2->addLayout(add);
              vlayout2->addSpacing(50);
              vlayout2->addWidget(loadComments2);

              //set page layout with scrollbar
              QWidget *widget3 = new QWidget();
              widget3->setStyleSheet("QWidget {background-color: white;}");
              widget3->setLayout(vlayout2);

              articlePageWidget2->setWidgetResizable(true);
              articlePageWidget2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
              articlePageWidget2->setWidget(widget3);

            stackedWidget->setCurrentWidget(articlePageWidget2);
            setCentralWidget(stackedWidget);

            connect(share2, &QPushButton::clicked, this, &Display::shareHandler2);
            connect(like2, &QPushButton::clicked, this, &Display::likedHandler2);
            connect(addToFavourites2, &QPushButton::clicked, this, &Display::addtoFavouritesHandler2);
            connect(subscribe2, &QPushButton::clicked, this, &Display::subscribeHandler2);
            connect(loadComments2, &QPushButton::clicked, this, &Display::loadCommentsHandler2);
            connect(addComment2, &QLineEdit::returnPressed, this, &Display::addCommentHandler2);

    }

void Display::likedHandler2(){
    like2->setText("Liked!");
}

void Display::subscribeHandler2(){
    subscribe2->setText("Subscribed!");
}

void Display::loadCommentsHandler2(){
    loadComments2->setText("No comments");
}
void Display::addCommentHandler2(){
    QString comment = "You: " + addComment2->text();
    QLabel *addlabel = new QLabel(comment);
    addlabel->setContentsMargins(100,0,0,0);
    addlabel->setStyleSheet("QLabel {font-size: 20px }");
    vlayout2->addWidget(addlabel);
}

    void Display::displayArticle3Handler(){
        vlayout3 = new QVBoxLayout();
        QPixmap articleImg3(":/3.jpeg");
        img_label3 = new QLabel();
        title_label3 = new QLabel();
        text_label3 = new QLabel();
        text_label3->setWordWrap(true);
         text_label3->setContentsMargins(200,0,100,0);

         spacingRow5 = new QLabel();
         spacingRow6 = new QLabel();
         img_label3->setPixmap(articleImg3);
         img_label3->setAlignment(Qt::AlignCenter);
         title_label3->setAlignment(Qt::AlignCenter);
         title_label3->setStyleSheet("QLabel { font-weight: bold; font-size: 30px; text-align: center; }");
         title_label3->setText(articles[2].m_title);
         text_label3->setText(articles[2].m_text);
         vlayout3->addWidget(spacingRow5);
         vlayout3->addWidget(title_label3);
         vlayout3->addWidget(spacingRow6);
         vlayout3->addWidget(img_label3);
         vlayout3->addWidget(text_label3);

              //article buttons for user actions
              like3 = new QPushButton("LIKE");
              like3->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              share3 = new QPushButton("SHARE");
              share3->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              addToFavourites3 = new QPushButton("+SAVE");
              addToFavourites3->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe3 = new QPushButton("SUBSCRIBE");
              subscribe3->setStyleSheet("QPushButton { background-color: red; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe3->setFixedWidth(100);
              addComment3 = new QLineEdit();
              addComment3->setFixedWidth(300);
              addComment3->setPlaceholderText("Add a public comment...");
              addComment3->setAlignment(Qt::AlignCenter);
              loadComments3 = new QPushButton("Load Comments");
              loadComments3->setStyleSheet("QPushButton { background-color:#b8b8b8; font-size: 15px; padding: .5em; border-radius: 7px;}");

              //layout for buttons
              QHBoxLayout *buttonslayout3 = new QHBoxLayout;
              buttonslayout3->addWidget(like3);
              buttonslayout3->addWidget(share3);
              buttonslayout3->addWidget(addToFavourites3);
              buttonslayout3->addWidget(subscribe3);
              buttonslayout3->setAlignment(Qt::AlignCenter);
              vlayout3->addLayout(buttonslayout3);
              QHBoxLayout *add = new QHBoxLayout();
              add->addWidget(addComment3);
              add->setAlignment(Qt::AlignHCenter);
              vlayout3->addSpacing(50);
              vlayout3->addLayout(add);
              vlayout3->addSpacing(50);
              vlayout3->addWidget(loadComments3);


              //set page layout with scrollbar
              QWidget *widget4 = new QWidget();
              widget4->setStyleSheet("QWidget {background-color: white;}");
              widget4->setLayout(vlayout3);

              articlePageWidget3->setWidgetResizable(true);
              articlePageWidget3->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
              articlePageWidget3->setWidget(widget4);

            stackedWidget->setCurrentWidget(articlePageWidget3);
            setCentralWidget(stackedWidget);

            connect(share3, &QPushButton::clicked, this, &Display::shareHandler3);
            connect(like3, &QPushButton::clicked, this, &Display::likedHandler3);
            connect(addToFavourites3, &QPushButton::clicked, this, &Display::addtoFavouritesHandler3);
            connect(subscribe3, &QPushButton::clicked, this, &Display::subscribeHandler3);
            connect(loadComments3, &QPushButton::clicked, this, &Display::loadCommentsHandler3);
            connect(addComment3, &QLineEdit::returnPressed, this, &Display::addCommentHandler3);

    }

    void Display::likedHandler3(){
        like3->setText("Liked!");
    }

    void Display::subscribeHandler3(){
        subscribe3->setText("Subscribed!");
    }

    void Display::loadCommentsHandler3(){
        loadComments3->setText("No Comments");
    }
    void Display::addCommentHandler3(){
        QString comment = "You: " + addComment3->text();
        QLabel *addlabel = new QLabel(comment);
        addlabel->setContentsMargins(100,0,0,0);
        addlabel->setStyleSheet("QLabel {font-size: 20px }");
        vlayout3->addWidget(addlabel);
    }

    void Display::displayArticle4Handler(){
        vlayout4 = new QVBoxLayout();
        QPixmap articleImg4(":/4.jpg");
        img_label4 = new QLabel();
        title_label4 = new QLabel();
        text_label4 = new QLabel();
        text_label4->setWordWrap(true);
         text_label4->setContentsMargins(200,0,100,0);

         spacingRow7 = new QLabel();
         spacingRow8 = new QLabel();
         img_label4->setPixmap(articleImg4);
         img_label4->setAlignment(Qt::AlignCenter);
         title_label4->setAlignment(Qt::AlignCenter);
         title_label4->setStyleSheet("QLabel { font-weight: bold; font-size: 30px; text-align: center; }");
         title_label4->setText(articles[3].m_title);
         text_label4->setText(articles[3].m_text);
         vlayout4->addWidget(spacingRow7);
         vlayout4->addWidget(title_label4);
         vlayout4->addWidget(spacingRow8);
         vlayout4->addWidget(img_label4);
         vlayout4->addWidget(text_label4);

              //article buttons for user actions
              like4 = new QPushButton("LIKE");
              like4->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              share4 = new QPushButton("SHARE");
              share4->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              addToFavourites4 = new QPushButton("+SAVE");
              addToFavourites4->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe4 = new QPushButton("SUBSCRIBE");
              subscribe4->setStyleSheet("QPushButton { background-color: red; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe4->setFixedWidth(100);
              addComment4 = new QLineEdit();
              addComment4->setFixedWidth(300);
              addComment4->setPlaceholderText("Add a public comment...");
              addComment4->setAlignment(Qt::AlignCenter);
              loadComments4 = new QPushButton("Load Comments");
              loadComments4->setStyleSheet("QPushButton { background-color:#b8b8b8; font-size: 15px; padding: .5em; border-radius: 7px;}");

              //layout for buttons
              QHBoxLayout *buttonslayout4 = new QHBoxLayout;
              buttonslayout4->addWidget(like4);
              buttonslayout4->addWidget(share4);
              buttonslayout4->addWidget(addToFavourites4);
              buttonslayout4->addWidget(subscribe4);
              buttonslayout4->setAlignment(Qt::AlignCenter);
              vlayout4->addLayout(buttonslayout4);
              QHBoxLayout *add = new QHBoxLayout();
              add->addWidget(addComment4);
              add->setAlignment(Qt::AlignHCenter);
              vlayout4->addSpacing(50);
              vlayout4->addLayout(add);
              vlayout4->addSpacing(50);
              vlayout4->addWidget(loadComments4);

              //set page layout with scrollbar
              QWidget *widget5 = new QWidget();
              widget5->setStyleSheet("QWidget {background-color: white;}");
              widget5->setLayout(vlayout4);

              articlePageWidget4->setWidgetResizable(true);
              articlePageWidget4->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
              articlePageWidget4->setWidget(widget5);

            stackedWidget->setCurrentWidget(articlePageWidget4);
            setCentralWidget(stackedWidget);

            connect(share4, &QPushButton::clicked, this, &Display::shareHandler4);
            connect(like4, &QPushButton::clicked, this, &Display::likedHandler4);
            connect(addToFavourites4, &QPushButton::clicked, this, &Display::addtoFavouritesHandler4);
            connect(subscribe4, &QPushButton::clicked, this, &Display::subscribeHandler4);
            connect(loadComments4, &QPushButton::clicked, this, &Display::loadCommentsHandler4);
            connect(addComment4, &QLineEdit::returnPressed, this, &Display::addCommentHandler4);

    }

    void Display::likedHandler4(){
        like4->setText("Liked!");
    }

    void Display::subscribeHandler4(){
        subscribe4->setText("Subscribed!");
    }

    void Display::loadCommentsHandler4(){
        loadComments4->setText("No Comments");
    }
    void Display::addCommentHandler4(){
        QString comment = "You: " + addComment4->text();
        QLabel *addlabel = new QLabel(comment);
        addlabel->setContentsMargins(100,0,0,0);
        addlabel->setStyleSheet("QLabel {font-size: 20px }");
        vlayout4->addWidget(addlabel);
    }

   void Display::displayArticle5Handler(){

        vlayout5 = new QVBoxLayout();
        QPixmap articleImg5(":/5.jpg");
        img_label5 = new QLabel();
        title_label5 = new QLabel();
        text_label5 = new QLabel();
        text_label5->setWordWrap(true);
         text_label5->setContentsMargins(200,0,100,0);

         spacingRow9 = new QLabel();
         spacingRow10 = new QLabel();
         img_label5->setPixmap(articleImg5);
         img_label5->setAlignment(Qt::AlignCenter);
         title_label5->setAlignment(Qt::AlignCenter);
         title_label5->setStyleSheet("QLabel { font-weight: bold; font-size: 30px; text-align: center; }");
         title_label5->setText(articles[4].m_title);
         text_label5->setText(articles[4].m_text);
         vlayout5->addWidget(spacingRow9);
         vlayout5->addWidget(title_label5);
         vlayout5->addWidget(spacingRow10);
         vlayout5->addWidget(img_label5);
         vlayout5->addWidget(text_label5);

              //article buttons for user actions
              like5 = new QPushButton("LIKE");
              like5->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              share5 = new QPushButton("SHARE");
              share5->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              addToFavourites5 = new QPushButton("+SAVE");
              addToFavourites5->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe5 = new QPushButton("SUBSCRIBE");
              subscribe5->setStyleSheet("QPushButton { background-color: red; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe5->setFixedWidth(100);
              addComment5 = new QLineEdit();
              addComment5->setFixedWidth(300);
              addComment5->setPlaceholderText("Add a public comment...");
              addComment5->setAlignment(Qt::AlignCenter);
              loadComments5 = new QPushButton("Load Comments");
              loadComments5->setStyleSheet("QPushButton { background-color:#b8b8b8; font-size: 15px; padding: .5em; border-radius: 7px;}");

              //layout for buttons
              QHBoxLayout *buttonslayout5 = new QHBoxLayout;
              buttonslayout5->addWidget(like5);
              buttonslayout5->addWidget(share5);
              buttonslayout5->addWidget(addToFavourites5);
              buttonslayout5->addWidget(subscribe5);
              buttonslayout5->setAlignment(Qt::AlignCenter);
              vlayout5->addLayout(buttonslayout5);
              QHBoxLayout *add = new QHBoxLayout();
              add->addWidget(addComment5);
              add->setAlignment(Qt::AlignHCenter);
              vlayout5->addSpacing(50);
              vlayout5->addLayout(add);
              vlayout5->addSpacing(50);
              vlayout5->addWidget(loadComments5);


              //set page layout with scrollbar
              QWidget *widget6 = new QWidget();
              widget6->setStyleSheet("QWidget {background-color: white;}");
              widget6->setLayout(vlayout5);

              articlePageWidget5->setWidgetResizable(true);
              articlePageWidget5->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
              articlePageWidget5->setWidget(widget6);

            stackedWidget->setCurrentWidget(articlePageWidget5);
            setCentralWidget(stackedWidget);

            connect(share5, &QPushButton::clicked, this, &Display::shareHandler5);
            connect(like5, &QPushButton::clicked, this, &Display::likedHandler5);
            connect(addToFavourites5, &QPushButton::clicked, this, &Display::addtoFavouritesHandler5);
            connect(subscribe5, &QPushButton::clicked, this, &Display::subscribeHandler5);
            connect(loadComments5, &QPushButton::clicked, this, &Display::loadCommentsHandler5);
            connect(addComment5, &QLineEdit::returnPressed, this, &Display::addCommentHandler5);
    }
   void Display::likedHandler5(){
       like5->setText("Liked!");
   }

   void Display::subscribeHandler5(){
       subscribe5->setText("Subscribed!");
   }

   void Display::loadCommentsHandler5(){
       loadComments5->setText("No Comments");
   }
   void Display::addCommentHandler5(){
       QString comment = "You: " + addComment5->text();
       QLabel *addlabel = new QLabel(comment);
       addlabel->setContentsMargins(100,0,0,0);
       addlabel->setStyleSheet("QLabel {font-size: 20px }");
       vlayout5->addWidget(addlabel);
   }

    void Display::displayArticle6Handler(){

        vlayout6 = new QVBoxLayout();
        QPixmap articleImg6(":/6.jpg");
        img_label6 = new QLabel();
        title_label6 = new QLabel();
        text_label6 = new QLabel();
        text_label6->setWordWrap(true);
         text_label6->setContentsMargins(200,0,100,0);

         spacingRow11 = new QLabel();
         spacingRow12 = new QLabel();
         img_label6->setPixmap(articleImg6);
         img_label6->setAlignment(Qt::AlignCenter);
         title_label6->setAlignment(Qt::AlignCenter);
         title_label6->setStyleSheet("QLabel { font-weight: bold; font-size: 30px; text-align: center; }");
         title_label6->setText(articles[5].m_title);
         text_label6->setText(articles[5].m_text);
         vlayout6->addWidget(spacingRow11);
         vlayout6->addWidget(title_label6);
         vlayout6->addWidget(spacingRow12);
         vlayout6->addWidget(img_label6);
         vlayout6->addWidget(text_label6);

              //article buttons for user actions
              like6 = new QPushButton("LIKE");
              like6->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              share6 = new QPushButton("SHARE");
              share6->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              addToFavourites6 = new QPushButton("+SAVE");
              addToFavourites6->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe6 = new QPushButton("SUBSCRIBE");
              subscribe6->setStyleSheet("QPushButton { background-color: red; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe6->setFixedWidth(100);
              addComment6 = new QLineEdit();
              addComment6->setFixedWidth(300);
              addComment6->setPlaceholderText("Add a public comment...");
              addComment6->setAlignment(Qt::AlignCenter);
              loadComments6 = new QPushButton("Load Comments");
              loadComments6->setStyleSheet("QPushButton { background-color:#b8b8b8; font-size: 15px; padding: .5em; border-radius: 7px;}");

              //layout for buttons
              QHBoxLayout *buttonslayout6 = new QHBoxLayout;
              buttonslayout6->addWidget(like6);
              buttonslayout6->addWidget(share6);
              buttonslayout6->addWidget(addToFavourites6);
              buttonslayout6->addWidget(subscribe6);
              buttonslayout6->setAlignment(Qt::AlignCenter);
              vlayout6->addLayout(buttonslayout6);
              QHBoxLayout *add = new QHBoxLayout();
              add->addWidget(addComment6);
              add->setAlignment(Qt::AlignHCenter);
              vlayout6->addSpacing(50);
              vlayout6->addLayout(add);
              vlayout6->addSpacing(50);
              vlayout6->addWidget(loadComments6);

              //set page layout with scrollbar
              QWidget *widget7 = new QWidget();
              widget7->setStyleSheet("QWidget {background-color: white;}");
              widget7->setLayout(vlayout6);

              articlePageWidget6->setWidgetResizable(true);
              articlePageWidget6->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
              articlePageWidget6->setWidget(widget7);

            stackedWidget->setCurrentWidget(articlePageWidget6);
            setCentralWidget(stackedWidget);

            connect(share6, &QPushButton::clicked, this, &Display::shareHandler6);
            connect(like6, &QPushButton::clicked, this, &Display::likedHandler6);
            connect(addToFavourites6, &QPushButton::clicked, this, &Display::addtoFavouritesHandler6);
            connect(subscribe6, &QPushButton::clicked, this, &Display::subscribeHandler6);
            connect(loadComments6, &QPushButton::clicked, this, &Display::loadCommentsHandler6);
            connect(addComment6, &QLineEdit::returnPressed, this, &Display::addCommentHandler6);
    }

    void Display::likedHandler6(){
        like6->setText("Liked!");
    }

    void Display::subscribeHandler6(){
        subscribe6->setText("Subscribed!");
    }

    void Display::loadCommentsHandler6(){
        loadComments6->setText("No Comments");
    }
    void Display::addCommentHandler6(){
        QString comment = "You: " + addComment6->text();
        QLabel *addlabel = new QLabel(comment);
        addlabel->setContentsMargins(100,0,0,0);
        addlabel->setStyleSheet("QLabel {font-size: 20px }");
        vlayout6->addWidget(addlabel);
    }

   void Display::displayArticle7Handler(){

        vlayout7 = new QVBoxLayout();
        QPixmap articleImg7(":/7.jpg");
        img_label7 = new QLabel();
        title_label7 = new QLabel();
        text_label7 = new QLabel();
        text_label7->setWordWrap(true);
         text_label7->setContentsMargins(200,0,100,0);

         spacingRow13 = new QLabel();
         spacingRow14 = new QLabel();
         img_label7->setPixmap(articleImg7);
         img_label7->setAlignment(Qt::AlignCenter);
         title_label7->setAlignment(Qt::AlignCenter);
         title_label7->setStyleSheet("QLabel { font-weight: bold; font-size: 30px; text-align: center; }");
         title_label7->setText(articles[6].m_title);
         text_label7->setText(articles[6].m_text);
         vlayout7->addWidget(spacingRow13);
         vlayout7->addWidget(title_label7);
         vlayout7->addWidget(spacingRow14);
         vlayout7->addWidget(img_label7);
         vlayout7->addWidget(text_label7);

              //article buttons for user actions
              like7 = new QPushButton("LIKE");
              like7->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              share7 = new QPushButton("SHARE");
              share7->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              addToFavourites7 = new QPushButton("+SAVE");
              addToFavourites7->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe7 = new QPushButton("SUBSCRIBE");
              subscribe7->setStyleSheet("QPushButton { background-color: red; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe7->setFixedWidth(100);
              addComment7 = new QLineEdit();
              addComment7->setFixedWidth(300);
              addComment7->setPlaceholderText("Add a public comment...");
              addComment7->setAlignment(Qt::AlignCenter);
              loadComments7 = new QPushButton("Load Comments");
              loadComments7->setStyleSheet("QPushButton { background-color:#b8b8b8; font-size: 15px; padding: .5em; border-radius: 7px;}");

              //layout for buttons
              QHBoxLayout *buttonslayout7 = new QHBoxLayout;
              buttonslayout7->addWidget(like7);
              buttonslayout7->addWidget(share7);
              buttonslayout7->addWidget(addToFavourites7);
              buttonslayout7->addWidget(subscribe7);
              buttonslayout7->setAlignment(Qt::AlignCenter);
              vlayout7->addLayout(buttonslayout7);
              QHBoxLayout *add = new QHBoxLayout();
              add->addWidget(addComment7);
              add->setAlignment(Qt::AlignHCenter);
              vlayout7->addSpacing(50);
              vlayout7->addLayout(add);
              vlayout7->addSpacing(50);
              vlayout7->addWidget(loadComments7);



              //set page layout with scrollbar
              QWidget *widget8 = new QWidget();
              widget8->setStyleSheet("QWidget {background-color: white;}");
              widget8->setLayout(vlayout7);

              articlePageWidget7->setWidgetResizable(true);
              articlePageWidget7->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
              articlePageWidget7->setWidget(widget8);

            stackedWidget->setCurrentWidget(articlePageWidget7);
            setCentralWidget(stackedWidget);

            connect(share7, &QPushButton::clicked, this, &Display::shareHandler7);
            connect(like7, &QPushButton::clicked, this, &Display::likedHandler7);
            connect(addToFavourites7, &QPushButton::clicked, this, &Display::addtoFavouritesHandler7);
            connect(subscribe7, &QPushButton::clicked, this, &Display::subscribeHandler7);
            connect(loadComments7, &QPushButton::clicked, this, &Display::loadCommentsHandler7);
            connect(addComment7, &QLineEdit::returnPressed, this, &Display::addCommentHandler7);
    }

   void Display::likedHandler7(){
       like7->setText("Liked!");
   }

   void Display::subscribeHandler7(){
       subscribe7->setText("Subscribed!");
   }

   void Display::loadCommentsHandler7(){
       loadComments7->setText("No Comments");
   }
   void Display::addCommentHandler7(){
       QString comment = "You: " + addComment7->text();
       QLabel *addlabel = new QLabel(comment);
       addlabel->setContentsMargins(100,0,0,0);
       addlabel->setStyleSheet("QLabel {font-size: 20px }");
       vlayout7->addWidget(addlabel);
   }

    void Display::displayArticle8Handler(){

        vlayout8 = new QVBoxLayout();
        QPixmap articleImg8(":/8.jpg");
        img_label8 = new QLabel();
        title_label8 = new QLabel();
        text_label8 = new QLabel();
        text_label8->setWordWrap(true);
         text_label8->setContentsMargins(200,0,100,0);

         spacingRow15 = new QLabel();
         spacingRow16 = new QLabel();
         img_label8->setPixmap(articleImg8);
         img_label8->setAlignment(Qt::AlignCenter);
         title_label8->setAlignment(Qt::AlignCenter);
         title_label8->setStyleSheet("QLabel { font-weight: bold; font-size: 30px; text-align: center; }");
         title_label8->setText(articles[7].m_title);
         text_label8->setText(articles[7].m_text);
         vlayout8->addWidget(spacingRow15);
         vlayout8->addWidget(title_label8);
         vlayout8->addWidget(spacingRow16);
         vlayout8->addWidget(img_label8);
         vlayout8->addWidget(text_label8);

              //article buttons for user actions
              like8 = new QPushButton("LIKE");
              like8->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              share8 = new QPushButton("SHARE");
              share8->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              addToFavourites8 = new QPushButton("+SAVE");
              addToFavourites8->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe8 = new QPushButton("SUBSCRIBE");
              subscribe8->setStyleSheet("QPushButton { background-color: red; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe8->setFixedWidth(100);
              addComment8 = new QLineEdit();
              addComment8->setFixedWidth(300);
              addComment8->setPlaceholderText("Add a public comment...");
              addComment8->setAlignment(Qt::AlignCenter);
              loadComments8 = new QPushButton("Load Comments");
              loadComments8->setStyleSheet("QPushButton { background-color:#b8b8b8; font-size: 15px; padding: .5em; border-radius: 7px;}");

              //layout for buttons
              QHBoxLayout *buttonslayout8 = new QHBoxLayout;
              buttonslayout8->addWidget(like8);
              buttonslayout8->addWidget(share8);
              buttonslayout8->addWidget(addToFavourites8);
              buttonslayout8->addWidget(subscribe8);
              buttonslayout8->setAlignment(Qt::AlignCenter);
              vlayout8->addLayout(buttonslayout8);
              QHBoxLayout *add = new QHBoxLayout();
              add->addWidget(addComment8);
              add->setAlignment(Qt::AlignHCenter);
              vlayout8->addSpacing(50);
              vlayout8->addLayout(add);
              vlayout8->addSpacing(50);
              vlayout8->addWidget(loadComments8);

              //set page layout with scrollbar
              QWidget *widget9 = new QWidget();
              widget9->setStyleSheet("QWidget {background-color: white;}");
              widget9->setLayout(vlayout8);

              articlePageWidget8->setWidgetResizable(true);
              articlePageWidget8->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
              articlePageWidget8->setWidget(widget9);

            stackedWidget->setCurrentWidget(articlePageWidget8);
            setCentralWidget(stackedWidget);

            connect(share8, &QPushButton::clicked, this, &Display::shareHandler8);
            connect(like8, &QPushButton::clicked, this, &Display::likedHandler8);
            connect(addToFavourites8, &QPushButton::clicked, this, &Display::addtoFavouritesHandler8);
            connect(subscribe8, &QPushButton::clicked, this, &Display::subscribeHandler8);
            connect(loadComments8, &QPushButton::clicked, this, &Display::loadCommentsHandler8);
            connect(addComment8, &QLineEdit::returnPressed, this, &Display::addCommentHandler8);
    }

    void Display::likedHandler8(){
        like8->setText("Liked!");
    }

    void Display::subscribeHandler8(){
        subscribe8->setText("Subscribed!");
    }

    void Display::loadCommentsHandler8(){
        loadComments8->setText("No Comments");
    }
    void Display::addCommentHandler8(){
        QString comment = "You: " + addComment8->text();
        QLabel *addlabel = new QLabel(comment);
        addlabel->setContentsMargins(100,0,0,0);
        addlabel->setStyleSheet("QLabel {font-size: 20px }");
        vlayout8->addWidget(addlabel);
    }


    void Display::displayArticle9Handler(){

        vlayout9 = new QVBoxLayout();
        QPixmap articleImg9(":/9.jpg");
        img_label9 = new QLabel();
        title_label9 = new QLabel();
        text_label9 = new QLabel();
        text_label9->setWordWrap(true);
         text_label9->setContentsMargins(200,0,100,0);

         spacingRow17= new QLabel();
         spacingRow18 = new QLabel();
         img_label9->setPixmap(articleImg9);
         img_label9->setAlignment(Qt::AlignCenter);
         title_label9->setAlignment(Qt::AlignCenter);
         title_label9->setStyleSheet("QLabel { font-weight: bold; font-size: 30px; text-align: center; }");
         title_label9->setText(articles[8].m_title);
         text_label9->setText(articles[8].m_text);
         vlayout9->addWidget(spacingRow17);
         vlayout9->addWidget(title_label9);
         vlayout9->addWidget(spacingRow18);
         vlayout9->addWidget(img_label9);
         vlayout9->addWidget(text_label9);

              //article buttons for user actions
              like9 = new QPushButton("LIKE");
              like9->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              share9 = new QPushButton("SHARE");
              share9->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              addToFavourites9 = new QPushButton("+SAVE");
              addToFavourites9->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe9 = new QPushButton("SUBSCRIBE");
              subscribe9->setStyleSheet("QPushButton { background-color: red; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe9->setFixedWidth(100);
              addComment9 = new QLineEdit();
              addComment9->setFixedWidth(300);
              addComment9->setPlaceholderText("Add a public comment...");
              addComment9->setAlignment(Qt::AlignCenter);
              loadComments9 = new QPushButton("Load Comments");
              loadComments9->setStyleSheet("QPushButton { background-color:#b8b8b8; font-size: 15px; padding: .5em; border-radius: 7px;}");

              //layout for buttons
              QHBoxLayout *buttonslayout9 = new QHBoxLayout;
              buttonslayout9->addWidget(like9);
              buttonslayout9->addWidget(share9);
              buttonslayout9->addWidget(addToFavourites9);
              buttonslayout9->addWidget(subscribe9);
              buttonslayout9->setAlignment(Qt::AlignCenter);
              vlayout9->addLayout(buttonslayout9);
              QHBoxLayout *add = new QHBoxLayout();
              add->addWidget(addComment9);
              add->setAlignment(Qt::AlignHCenter);
              vlayout9->addSpacing(50);
              vlayout9->addLayout(add);
              vlayout9->addSpacing(50);
              vlayout9->addWidget(loadComments9);

              //set page layout with scrollbar
              QWidget *widget10 = new QWidget();
              widget10->setStyleSheet("QWidget {background-color: white;}");
              widget10->setLayout(vlayout9);

              articlePageWidget9->setWidgetResizable(true);
              articlePageWidget9->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
              articlePageWidget9->setWidget(widget10);

            stackedWidget->setCurrentWidget(articlePageWidget9);
            setCentralWidget(stackedWidget);

            connect(share9, &QPushButton::clicked, this, &Display::shareHandler9);
            connect(like9, &QPushButton::clicked, this, &Display::likedHandler9);
            connect(addToFavourites9, &QPushButton::clicked, this, &Display::addtoFavouritesHandler9);
            connect(subscribe9, &QPushButton::clicked, this, &Display::subscribeHandler9);
            connect(loadComments9, &QPushButton::clicked, this, &Display::loadCommentsHandler9);
            connect(addComment9, &QLineEdit::returnPressed, this, &Display::addCommentHandler9);
    }

    void Display::likedHandler9(){
        like9->setText("Liked!");
    }

    void Display::subscribeHandler9(){
        subscribe9->setText("Subscribed!");
    }

    void Display::loadCommentsHandler9(){
        loadComments9->setText("No Comments");
    }
    void Display::addCommentHandler9(){
        QString comment = "You: " + addComment9->text();
        QLabel *addlabel = new QLabel(comment);
        addlabel->setContentsMargins(100,0,0,0);
        addlabel->setStyleSheet("QLabel {font-size: 20px }");
        vlayout9->addWidget(addlabel);
    }

    void Display::displayArticle10Handler(){

        vlayout10 = new QVBoxLayout();
        QPixmap articleImg10(":/10.jpg");
        img_label10 = new QLabel();
        title_label10 = new QLabel();
        text_label10 = new QLabel();
        text_label10->setWordWrap(true);
         text_label10->setContentsMargins(200,0,100,0);

         spacingRow19= new QLabel();
         spacingRow20 = new QLabel();
         img_label10->setPixmap(articleImg10);
         img_label10->setAlignment(Qt::AlignCenter);
         title_label10->setAlignment(Qt::AlignCenter);
         title_label10->setStyleSheet("QLabel { font-weight: bold; font-size: 30px; text-align: center; }");
         title_label10->setText(articles[9].m_title);
         text_label10->setText(articles[9].m_text);
         vlayout10->addWidget(spacingRow19);
         vlayout10->addWidget(title_label10);
         vlayout10->addWidget(spacingRow20);
         vlayout10->addWidget(img_label10);
         vlayout10->addWidget(text_label10);

              //article buttons for user actions
              like10 = new QPushButton("LIKE");
              like10->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              share10 = new QPushButton("SHARE");
              share10->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              addToFavourites10 = new QPushButton("+SAVE");
              addToFavourites10->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe10 = new QPushButton("SUBSCRIBE");
              subscribe10->setStyleSheet("QPushButton { background-color: red; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
              subscribe10->setFixedWidth(100);
              addComment10 = new QLineEdit();
              addComment10->setFixedWidth(300);
              addComment10->setPlaceholderText("Add a public comment...");
              addComment10->setAlignment(Qt::AlignCenter);
              loadComments10 = new QPushButton("Load Comments");
              loadComments10->setStyleSheet("QPushButton { background-color:#b8b8b8; font-size: 15px; padding: .5em; border-radius: 7px;}");

              //layout for buttons
              QHBoxLayout *buttonslayout10 = new QHBoxLayout;
              buttonslayout10->addWidget(like10);
              buttonslayout10->addWidget(share10);
              buttonslayout10->addWidget(addToFavourites10);
              buttonslayout10->addWidget(subscribe10);
              buttonslayout10->setAlignment(Qt::AlignCenter);
              vlayout10->addLayout(buttonslayout10);
              QHBoxLayout *add = new QHBoxLayout();
              add->addWidget(addComment10);
              add->setAlignment(Qt::AlignHCenter);
              vlayout10->addSpacing(50);
              vlayout10->addLayout(add);
              vlayout10->addSpacing(50);
              vlayout10->addWidget(loadComments10);


              //set page layout with scrollbar
              QWidget *widget11 = new QWidget();
              widget11->setStyleSheet("QWidget {background-color: white;}");
              widget11->setLayout(vlayout10);

              articlePageWidget10->setWidgetResizable(true);
              articlePageWidget10->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
              articlePageWidget10->setWidget(widget11);

            stackedWidget->setCurrentWidget(articlePageWidget10);
            setCentralWidget(stackedWidget);

            connect(share10, &QPushButton::clicked, this, &Display::shareHandler10);
            connect(like10, &QPushButton::clicked, this, &Display::likedHandler10);
            connect(addToFavourites10, &QPushButton::clicked, this, &Display::addtoFavouritesHandler10);
            connect(subscribe10, &QPushButton::clicked, this, &Display::subscribeHandler10);
            connect(loadComments10, &QPushButton::clicked, this, &Display::loadCommentsHandler10);
            connect(addComment10, &QLineEdit::returnPressed, this, &Display::addCommentHandler10);
    }

    void Display::likedHandler10(){
        like10->setText("Liked!");
    }

    void Display::subscribeHandler10(){
        subscribe10->setText("Subscribed!");
    }

    void Display::loadCommentsHandler10(){
        loadComments10->setText("No Comments");
    }
    void Display::addCommentHandler10(){
        QString comment = "You: " + addComment10->text();
        QLabel *addlabel = new QLabel(comment);
        addlabel->setContentsMargins(100,0,0,0);
        addlabel->setStyleSheet("QLabel {font-size: 20px }");
        vlayout10->addWidget(addlabel);
    }

  /* void Display::displayArticle5topHandler(){


    }*/

void Display::topnextHandler(){

    //go to next index on stacked widget

    int index = stackedTopnews->currentIndex();
    if(index != 2){
    index++;
    }
    else if(index ==2){
        index = 0;
    }
    stackedTopnews->setCurrentIndex(index);
}

void Display::topprevHandler(){

    //go to prev index on stacked widget

    int index = stackedTopnews->currentIndex();
    if(index != 0){
    index--;
    }
    else if(index == 0){
        index = 2;
    }
    stackedTopnews->setCurrentIndex(index);

}

void Display::feednextHandler(){

    //go to next index on stacked widget feed
    int index1 = stackedFeed1->currentIndex();
    if(index1 != 7){
    index1++;
    }
    else if(index1 == 7){
        index1 = 0;
    }
    stackedFeed1->setCurrentIndex(index1);

    //go to next index on stacked widget feed
    int index2 = stackedFeed2->currentIndex();
    if(index2 != 7){
    index2++;
    }
    else if(index2 == 7){
        index2 = 0;
    }
    stackedFeed2->setCurrentIndex(index2);

    //go to next index on stacked widget feed
    int index3 = stackedFeed3->currentIndex();
    if(index3 != 7){
    index3++;
    }
    else if(index3 == 7){
        index3 = 0;
    }

    stackedFeed3->setCurrentIndex(index3);

    //go to next index on stacked widget feed
    int index4 = stackedFeed4->currentIndex();
    if(index4 != 7){
    index4++;
    }
    else if(index4 == 7){
        index4 = 0;
    }
    stackedFeed4->setCurrentIndex(index4);
}

void Display::feedprevHandler(){

    //go to next index on stacked widget feed
    int index1 = stackedFeed1->currentIndex();
    if(index1 != 0){
    index1--;
    }
    else if(index1 == 0){
        index1 = 7;
    }
    stackedFeed1->setCurrentIndex(index1);

    //go to next index on stacked widget feed
    int index2 = stackedFeed2->currentIndex();
    if(index2 != 0){
    index2--;
    }
    else if(index2 == 0){
        index2 = 7;
    }
    stackedFeed2->setCurrentIndex(index2);

    //go to next index on stacked widget feed
    int index3 = stackedFeed3->currentIndex();
    if(index3 != 0){
    index3--;
    }
    else if(index3 == 0){
        index3 = 7;
    }

    stackedFeed3->setCurrentIndex(index3);

    //go to next index on stacked widget feed
    int index4 = stackedFeed4->currentIndex();
    if(index4 != 0){
    index4--;
    }
    else if(index4 == 0){
        index4 = 7;
    }
    stackedFeed4->setCurrentIndex(index4);
}

void Display::backpageHandler(){

    //setting main view
     stackedWidget->setCurrentWidget(mainPageWidget);
     setCentralWidget(stackedWidget);
}

void Display::favouritesHandler(){

    //display favourites lists with corresponding saved articles
    QVBoxLayout *savedlist = new QVBoxLayout();
    QVBoxLayout *folderlist = new QVBoxLayout();

    //make folder icons
    QPixmap folder(":/favlist.jpg");
    QPixmap folders[20];
    folders[0] = folder;
    folders[1] = folder;
    folders[2] = folder;
    folders[3] = folder;
    folders[4] = folder;
    folders[5] = folder;
    folders[6] = folder;
    folders[7] = folder;
    folders[8] = folder;
    folders[9] = folder;
    folders[10] = folder;
    folders[11] = folder;
    folders[12] = folder;
    folders[13] = folder;
    folders[14] = folder;
    folders[15] = folder;
    folders[16] = folder;
    folders[17] = folder;
    folders[18] = folder;
    folders[19] = folder;

    for(int i = 0; i < favlists[i]->count() && favlists[0][i] != ""; ++i)
    {
        if(favlists[0][i] != ""){
           favlisticons[i] = new QLabel();
           favlisticons[i]->setPixmap(folders[i]);
           folderlist->addWidget(favlisticons[i]);
           favlisted[i] = new QLabel(favlists[0][i]);
           savedlist->addWidget(favlisted[i]);

               //iterate through row to check for next available spot to store article title in list
               for(int j = 1;j < favlists[j]->count() && favlists[j][i] != ""; ++j)
               {
                   if(favlists[j][i] != ""){
                   favtitles[j] = new QPushButton("-" + favlists[j][i]);
                   favtitles[j]->setStyleSheet("QPushButton{border: none;}");
                   savedlist->addWidget(favtitles[j]);
               }
             }
           }
        }

    folderlist->setMargin(0);
    folderlist->setSpacing(0);
    savedlist->setMargin(0);
    savedlist->setSpacing(0);
    QHBoxLayout *favouriteslisted = new QHBoxLayout();
    favouriteslisted->addLayout(folderlist, Qt::AlignLeft);
    favouriteslisted->addLayout(savedlist, Qt::AlignRight);


    QLabel *favouriteslabel = new QLabel("Favourites");
    favouriteslabel->setStyleSheet("QLabel{font-size: 30px; font-weight: bold;}");
    favouriteslabel->setContentsMargins(450,30,30,30);

    QPushButton *newlist= new QPushButton("+ Create New List");
    newlist->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addWidget(newlist);


    favlayout = new QVBoxLayout();
    favlayout->addWidget(favouriteslabel);
    favlayout->addLayout(favouriteslisted);
    favlayout->addLayout(buttons);
    favlayout->setContentsMargins(50,50,50,50);

    //set page layout with scrollbar
    QWidget *favwidget = new QWidget();
    favwidget->setStyleSheet("QWidget {background-color: white;}");
    favwidget->setLayout(favlayout);

    favouritesPageWidget->setWidgetResizable(true);
    favouritesPageWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    favouritesPageWidget->setWidget(favwidget);

  stackedWidget->setCurrentWidget(favouritesPageWidget);
  setCentralWidget(stackedWidget);

  connect(newlist, &QPushButton::clicked, this, &Display::newwwHandler);
}

void Display::newwwHandler(){

        listnameFieldc = new QLineEdit();
        QFormLayout *flayoutlistname = new QFormLayout();
        flayoutlistname->addRow("New Favourites List Name:", listnameFieldc);
        QPushButton *create = new QPushButton("Create List");
        create->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");

        QVBoxLayout *newlist = new QVBoxLayout();
        newlist->addLayout(flayoutlistname);
        newlist->addWidget(create);

        newlistWidget = new QWidget();
        newlistWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
        newlistWidget->setLayout(newlist);
        newlistWidget->setWindowTitle("Create New Favourites List");
        newlistWidget->resize(200, 100);
        newlistWidget->show();

        connect(create, &QPushButton::clicked, this, &Display::createlistHandler);
    }

void Display::createlistHandler(){

    for(int i = 0;i < favlists[0]->count(); ++i)
    {
        if(favlists[0][i] == ""){
           favlists[0][i] = listnameFieldc->text();
           break;
        }
    }
    newlistWidget->hide();
    favouritesHandler();
}

void Display::settingsHandler() {

    //display favourites lists with corresponding saved articles
    QHBoxLayout *settings = new QHBoxLayout();

    //make folder icons
   QPixmap img(":/profile.jpg");
    QLabel *img2 = new QLabel();
    img2->setPixmap(img);

     firstnameField = new QLineEdit();
     firstnameField->setText(actor.m_firstName);
     firstnameField->setContentsMargins(0,80,50,0);
     lastnameField = new QLineEdit();
     lastnameField->setText(actor.m_lastName);
     lastnameField->setContentsMargins(0,0,50,0);
     unField = new QLineEdit();
     unField->setText(actor.m_username);
     unField->setContentsMargins(0,0,50,0);
     passField = new QLineEdit();
     passField->setText(actor.m_password);
     passField->setContentsMargins(0,0,50,0);
     emailField = new QLineEdit();
     emailField->setText(actor.m_email);
     emailField->setContentsMargins(0,0,50,0);
     ccField = new QLineEdit();
     ccField->setText(actor.m_creditCard);
     ccField->setContentsMargins(0,0,50,0);
     QLabel *space = new QLabel();
     QLabel *space2 = new QLabel();
     QLabel *space3 = new QLabel();
     QLabel *space4 = new QLabel();
     QLabel *space5 = new QLabel();

     QFormLayout *flayoutSettings = new QFormLayout();
     QLabel *firstNamelabel = new QLabel("First Name:");
     firstNamelabel->setContentsMargins(0,80,50,0);
     firstNamelabel->setStyleSheet("QLabel{font-weight: bold; font-size:20px;}");
     flayoutSettings->addRow(firstNamelabel, firstnameField);
     flayoutSettings->addRow(space);
     QLabel *lastNamelabel = new QLabel("Last Name:");
     lastNamelabel->setStyleSheet("QLabel{font-weight: bold; font-size:20px;}");
     flayoutSettings->addRow(lastNamelabel, lastnameField);
     flayoutSettings->addRow(space2);
     QLabel *unlabel = new QLabel("User Name:");
     unlabel->setStyleSheet("QLabel{font-weight: bold; font-size:20px;}");
     flayoutSettings->addRow(unlabel, unField);
     flayoutSettings->addRow(space3);
     QLabel *passlabel = new QLabel("Password:");
     passlabel->setStyleSheet("QLabel{font-weight: bold; font-size:20px;}");
     flayoutSettings->addRow(passlabel, passField);
     flayoutSettings->addRow(space4);
     QLabel *emaillabel = new QLabel("Email:");
     emaillabel->setStyleSheet("QLabel{font-weight: bold; font-size:20px;}");
     flayoutSettings->addRow(emaillabel, emailField);
     flayoutSettings->addRow(space5);
     QLabel *cclabel = new QLabel("Credit Card:");
     cclabel->setStyleSheet("QLabel{font-weight: bold; font-size:20px;}");
     flayoutSettings->addRow(cclabel, ccField);

     img2->setContentsMargins(50,0,50,250);
     settings->addWidget(img2);
     settings->addLayout(flayoutSettings);

    savesettings= new QPushButton("Save Settings");
    savesettings->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
    QPushButton *signout= new QPushButton("Sign Out");
    signout->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
    QPushButton *deleteAccount= new QPushButton("Delete Account");
    deleteAccount->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
    QHBoxLayout *buttons = new QHBoxLayout();
    savesettings->setContentsMargins(50,0,50,50);
    buttons->addWidget(savesettings);
    signout->setContentsMargins(50,0,50,50);
    buttons->addWidget(signout);
    deleteAccount->setContentsMargins(50,0,50,50);
    buttons->addWidget(deleteAccount);

    QVBoxLayout *anotherlayout = new QVBoxLayout();
    anotherlayout->addLayout(settings);
    anotherlayout->addLayout(buttons);

    QFrame *favframe = new QFrame();
    favframe->setMaximumWidth(1000);
    favframe->setMinimumHeight(600);
    favframe->setLayout(anotherlayout);
    favframe->setFrameStyle(QFrame::Box | QFrame::Plain);
    favframe->setLineWidth(1);

    QHBoxLayout *framelayout = new QHBoxLayout();
    framelayout->addWidget(favframe, Qt::AlignCenter);
    framelayout->setContentsMargins(50, -10, 0, 100);

    QLabel *settingslabel= new QLabel("Settings");
    settingslabel->setContentsMargins(450,0,0,0);
    settingslabel->setStyleSheet("QLabel {font-size: 30px; font-weight: bold;}");
    QVBoxLayout *entirepage = new QVBoxLayout();
    entirepage->addWidget(settingslabel);
    entirepage->addLayout(framelayout);

    //set page layout with scrollbar
    QWidget *setwidget = new QWidget();
    setwidget->setStyleSheet("QWidget {background-color: white;}");
    setwidget->setLayout(entirepage);

    settingsPageWidget->setWidgetResizable(true);
    settingsPageWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    settingsPageWidget->setWidget(setwidget);

  stackedWidget->setCurrentWidget(settingsPageWidget);
  setCentralWidget(stackedWidget);

  connect(savesettings, &QPushButton::clicked, this, &Display::savesettingsHandler);
  connect(signout, &QPushButton::clicked, this, &Display::userHandler);
  connect(deleteAccount, &QPushButton::clicked, this, &Display::deleteHandler);

}

void Display::savesettingsHandler(){
  actor.m_firstName = firstnameField->text();
  actor.m_lastName = lastnameField->text();
  actor.m_username = unField->text();
  actor.m_password = passField->text();
  actor.m_email = emailField->text();
  actor.m_creditCard = ccField->text();
  savesettings->setText("Saved!");
}

void Display::deleteHandler(){

    QLabel *Quserlabel = new QLabel("Are you sure you would like to delete your account?");
    Quserlabel->setStyleSheet("QLabel{font-size: 20px; font-weight: bold;}");
    QLabel *space2 = new QLabel();
    QPushButton *yes = new QPushButton("Yes");
    QPushButton *no = new QPushButton("No");
    QHBoxLayout *buttonlayout = new QHBoxLayout;
    buttonlayout->addWidget(yes);
    buttonlayout->addWidget(no);

    userlayout = new QVBoxLayout();
    userlayout->addWidget(Quserlabel);
    userlayout->addWidget(space2);
    userlayout->addLayout(buttonlayout);

    user = new QWidget();
    user->setLayout(userlayout);
    user->setWindowTitle("Delete Account?");
    user->resize(300, 150);
    user->show();

    connect(yes, &QPushButton::clicked, this, &Display::endHandler);
    connect(no, &QPushButton::clicked, this, &Display::quitHandler);

}

void Display::endHandler(){
    actor.m_username = "";
    actor.m_password = "";

    user->hide();
    this->hide();
    QLabel *space = new QLabel();
    //QLabel *username = new QLabel("please enter your username:");
    QPixmap logoImg(":/logo.jpg");
    QLabel *logo = new QLabel();
    logo->setPixmap(logoImg);
    logo->setContentsMargins(100,0,0,0);
    usernameField = new QLineEdit();
    passwordField = new QLineEdit();
    QPushButton *signin = new QPushButton("Sign In");
    signin->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");

     QFormLayout *flayoutSignin = new QFormLayout();
     flayoutSignin->addRow("please enter your username:", usernameField);
     flayoutSignin->addRow(space);
     flayoutSignin->addRow("please enter your password:", passwordField);

    signinlayout = new QVBoxLayout;
    signinlayout->addWidget(logo);
    signinlayout->addLayout(flayoutSignin);
    signinlayout->addWidget(signin);
    message = new QLabel();
    signinlayout->addWidget(message);

    signinWidget = new QWidget();
    signinWidget->setLayout(signinlayout);
    signinWidget->setWindowTitle("Sign In");
    signinWidget->resize(500,500);
    signinWidget->show();

   connect(signin, &QPushButton::clicked, this, &Display::signinHandler);

}

void Display::userHandler(){

    QLabel *userlabel = new QLabel("Signed In");
    userlabel->setStyleSheet("QLabel{font-size: 20px;  font-style: italic;}");
    userlabel->setAlignment(Qt::AlignHCenter);
    QLabel *space = new QLabel();
   // favouriteslabel->setContentsMargins(550,30,30,30);
    QLabel *Quserlabel = new QLabel("Would you like to sign out of your account?");
    Quserlabel->setStyleSheet("QLabel{font-size: 20px; font-weight: bold;}");
    QLabel *space2 = new QLabel();
    QPushButton *yes = new QPushButton("Yes");
    QPushButton *no = new QPushButton("No");
    QHBoxLayout *buttonlayout = new QHBoxLayout;
    buttonlayout->addWidget(yes);
    buttonlayout->addWidget(no);

    userlayout = new QVBoxLayout();
    userlayout->addWidget(userlabel);
    userlayout->addWidget(space);
    userlayout->addWidget(Quserlabel);
    userlayout->addWidget(space2);
    userlayout->addLayout(buttonlayout);

    user = new QWidget();
    user->setLayout(userlayout);
    user->setWindowTitle("Sign out?");
    user->resize(300, 150);
    user->show();

    connect(yes, &QPushButton::clicked, this, &Display::signoutHandler);
    connect(no, &QPushButton::clicked, this, &Display::quitHandler);
}

void Display::quitHandler(){
    user->hide();
}

void Display::signoutHandler(){

    user->hide();
    this->hide();
    QLabel *space = new QLabel();
    //QLabel *username = new QLabel("please enter your username:");
    QPixmap logoImg(":/logo.jpg");
    QLabel *logo = new QLabel();
    logo->setPixmap(logoImg);
    logo->setContentsMargins(100,0,0,0);
    usernameField = new QLineEdit();
    passwordField = new QLineEdit();
    QPushButton *signin = new QPushButton("Sign In");
    signin->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");

     QFormLayout *flayoutSignin = new QFormLayout();
     flayoutSignin->addRow("please enter your username:", usernameField);
     flayoutSignin->addRow(space);
     flayoutSignin->addRow("please enter your password:", passwordField);

    signinlayout = new QVBoxLayout;
    signinlayout->addWidget(logo);
    signinlayout->addLayout(flayoutSignin);
    signinlayout->addWidget(signin);
    message = new QLabel();
    signinlayout->addWidget(message);

    signinWidget = new QWidget();
    signinWidget->setLayout(signinlayout);
    signinWidget->setWindowTitle("Sign In");
    signinWidget->resize(500,500);
    signinWidget->show();

   connect(signin, &QPushButton::clicked, this, &Display::signinHandler);

}

void Display::signinHandler(){

    //setting main view
    if(usernameField->text() == actor.m_username && passwordField->text() == actor.m_password){
    this->show();
    signinWidget->hide();
     stackedWidget->setCurrentWidget(mainPageWidget);
     setCentralWidget(stackedWidget);
    }
    else{
        usernameField->setText("");
    passwordField->setText("");
   message->setText("Please try again, we were not able to authenticate that username and password");
    }
}

void Display::likedHandler1a(){
     heart1a->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart1a->setMaximumWidth(15);
}
void Display::likedHandler2a(){
     heart2a->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart2a->setMaximumWidth(15);
}
void Display::likedHandler3a(){
     heart3a->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart3a->setMaximumWidth(15);
}
void Display::likedHandler4a(){
     heart4a->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart4a->setMaximumWidth(15);

}
void Display::likedHandler5a(){
     heart5a->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart5a->setMaximumWidth(15);
}
void Display::likedHandler6a(){
     heart6a->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart6a->setMaximumWidth(15);
}
void Display::likedHandler7a(){
     heart7a->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart7a->setMaximumWidth(15);
}
void Display::likedHandler8a(){
     heart8a->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart8a->setMaximumWidth(15);
}

void Display::likedHandler1b(){
     heart1b->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart1b->setMaximumWidth(15);
}
void Display::likedHandler2b(){
     heart2b->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart2b->setMaximumWidth(15);
}
void Display::likedHandler3b(){
     heart3b->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart3b->setMaximumWidth(15);
}
void Display::likedHandler4b(){
     heart4b->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart4b->setMaximumWidth(15);
}
void Display::likedHandler5b(){
     heart5b->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart5b->setMaximumWidth(15);
}
void Display::likedHandler6b(){
     heart6b->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart6b->setMaximumWidth(15);
}
void Display::likedHandler7b(){
     heart7b->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart7b->setMaximumWidth(15);
}
void Display::likedHandler8b(){
     heart8b->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart8b->setMaximumWidth(15);}

void Display::likedHandler1c(){
     heart1c->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart1c->setMaximumWidth(15);
}
void Display::likedHandler2c(){
     heart2c->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart2c->setMaximumWidth(15);
}
void Display::likedHandler3c(){
     heart3c->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart3c->setMaximumWidth(15);
}
void Display::likedHandler4c(){
     heart4c->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart4c->setMaximumWidth(15);
}
void Display::likedHandler5c(){
     heart5c->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart5c->setMaximumWidth(15);}
void Display::likedHandler6c(){
     heart6c->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart6c->setMaximumWidth(15);
}
void Display::likedHandler7c(){
     heart7c->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart7c->setMaximumWidth(15);
}
void Display::likedHandler8c(){
     heart8c->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart8c->setMaximumWidth(15);
}

void Display::likedHandler1d(){
     heart1d->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart1d->setMaximumWidth(15);
}
void Display::likedHandler2d(){
     heart2d->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart2d->setMaximumWidth(15);
}
void Display::likedHandler3d(){
     heart3d->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart3d->setMaximumWidth(15);
}
void Display::likedHandler4d(){
     heart4d->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart4d->setMaximumWidth(15);
}
void Display::likedHandler5d(){
     heart5d->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart5d->setMaximumWidth(15);
}
void Display::likedHandler6d(){
     heart6d->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart6d->setMaximumWidth(15);
}
void Display::likedHandler7d(){
     heart7d->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart7d->setMaximumWidth(15);
}
void Display::likedHandler8d(){
     heart8d->setStyleSheet("QPushButton {border-image:url(:/liked.jpg);}");
     heart8d->setMaximumWidth(15);
}


void Display::shareHandler1(){

    QPushButton *facebook = new QPushButton();
    facebook->setCursor(Qt::PointingHandCursor);
    facebook->setStyleSheet("QPushButton {border-image:url(:/facebook.jpg);}");
    facebook->setMaximumWidth(99);
    facebook->setMinimumHeight(130);
    QPushButton *twitter = new QPushButton();
    twitter->setCursor(Qt::PointingHandCursor);
    twitter->setStyleSheet("QPushButton {border-image:url(:/twitter.jpg);}");
    twitter->setMaximumWidth(99);
    twitter->setMinimumHeight(130);
    QPushButton *email = new QPushButton();
    email->setCursor(Qt::PointingHandCursor);
    email->setStyleSheet("QPushButton {border-image:url(:/email.jpg);}");
    email->setMaximumWidth(99);
    email->setMinimumHeight(130);
    QPushButton *linkedin = new QPushButton();
    linkedin->setCursor(Qt::PointingHandCursor);
    linkedin->setStyleSheet("QPushButton {border-image:url(:/linkedin.jpg);}");
    linkedin->setMaximumWidth(99);
    linkedin->setMinimumHeight(130);
    QPushButton *tumblr = new QPushButton();
    tumblr->setCursor(Qt::PointingHandCursor);
    tumblr->setStyleSheet("QPushButton {border-image:url(:/tumblr.jpg);}");
    tumblr->setMaximumWidth(99);
    tumblr->setMinimumHeight(130);
    QHBoxLayout *shareiconlayout = new QHBoxLayout;
    shareiconlayout->addWidget(facebook);
    shareiconlayout->addWidget(twitter);
    shareiconlayout->addWidget(email);
    shareiconlayout->addWidget(linkedin);
    shareiconlayout->addWidget(tumblr);

    link = new QLineEdit;
    link->setText(links[0]);
    QPushButton *copy = new QPushButton("Copy");
    copy->setCursor(Qt::PointingHandCursor);
    copy->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
    link->setContentsMargins(20,20,20,20);

    sharelayout = new QVBoxLayout();
    sharelayout->addLayout(shareiconlayout);

    QHBoxLayout *copylink= new QHBoxLayout;
    copylink->addWidget(link);
    copylink->addWidget(copy);
    sharelayout->addLayout(copylink);
    sharelayout->setContentsMargins(70,30,70,50);

    shareWidget = new QWidget();
    shareWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    shareWidget->setLayout(sharelayout);
    shareWidget->setWindowTitle("Share");
    shareWidget->resize(600, 300);
    shareWidget->show();

    connect(facebook, &QPushButton::clicked, this, &Display::facebookHandler);
    connect(twitter, &QPushButton::clicked, this, &Display::twitterHandler);
    connect(email, &QPushButton::clicked, this, &Display::emailHandler);
    connect(linkedin, &QPushButton::clicked, this, &Display::linkedinHandler);
    connect(tumblr, &QPushButton::clicked, this, &Display::tumblrHandler);
    connect(copy, &QPushButton::clicked, this, &Display::copyHandler);
};

void Display::shareHandler2(){

    QPushButton *facebook = new QPushButton();
    facebook->setCursor(Qt::PointingHandCursor);
    facebook->setStyleSheet("QPushButton {border-image:url(:/facebook.jpg);}");
    facebook->setMaximumWidth(99);
    facebook->setMinimumHeight(130);
    QPushButton *twitter = new QPushButton();
    twitter->setCursor(Qt::PointingHandCursor);
    twitter->setStyleSheet("QPushButton {border-image:url(:/twitter.jpg);}");
    twitter->setMaximumWidth(99);
    twitter->setMinimumHeight(130);
    QPushButton *email = new QPushButton();
    email->setCursor(Qt::PointingHandCursor);
    email->setStyleSheet("QPushButton {border-image:url(:/email.jpg);}");
    email->setMaximumWidth(99);
    email->setMinimumHeight(130);
    QPushButton *linkedin = new QPushButton();
    linkedin->setCursor(Qt::PointingHandCursor);
    linkedin->setStyleSheet("QPushButton {border-image:url(:/linkedin.jpg);}");
    linkedin->setMaximumWidth(99);
    linkedin->setMinimumHeight(130);
    QPushButton *tumblr = new QPushButton();
    tumblr->setCursor(Qt::PointingHandCursor);
    tumblr->setStyleSheet("QPushButton {border-image:url(:/tumblr.jpg);}");
    tumblr->setMaximumWidth(99);
    tumblr->setMinimumHeight(130);
    QHBoxLayout *shareiconlayout = new QHBoxLayout;
    shareiconlayout->addWidget(facebook);
    shareiconlayout->addWidget(twitter);
    shareiconlayout->addWidget(email);
    shareiconlayout->addWidget(linkedin);
    shareiconlayout->addWidget(tumblr);

    link = new QLineEdit;
    link->setText(links[1]);
    QPushButton *copy = new QPushButton("Copy");
    copy->setCursor(Qt::PointingHandCursor);
    copy->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
    link->setContentsMargins(20,20,20,20);

    sharelayout = new QVBoxLayout();
    sharelayout->addLayout(shareiconlayout);

    QHBoxLayout *copylink= new QHBoxLayout;
    copylink->addWidget(link);
    copylink->addWidget(copy);
    sharelayout->addLayout(copylink);
    sharelayout->setContentsMargins(70,30,70,50);

    shareWidget = new QWidget();
    shareWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    shareWidget->setLayout(sharelayout);
    shareWidget->setWindowTitle("Share");
    shareWidget->resize(600, 300);
    shareWidget->show();

    connect(facebook, &QPushButton::clicked, this, &Display::facebookHandler);
    connect(twitter, &QPushButton::clicked, this, &Display::twitterHandler);
    connect(email, &QPushButton::clicked, this, &Display::emailHandler);
    connect(linkedin, &QPushButton::clicked, this, &Display::linkedinHandler);
    connect(tumblr, &QPushButton::clicked, this, &Display::tumblrHandler);
    connect(copy, &QPushButton::clicked, this, &Display::copyHandler);
};

void Display::shareHandler3(){

    QPushButton *facebook = new QPushButton();
    facebook->setCursor(Qt::PointingHandCursor);
    facebook->setStyleSheet("QPushButton {border-image:url(:/facebook.jpg);}");
    facebook->setMaximumWidth(99);
    facebook->setMinimumHeight(130);
    QPushButton *twitter = new QPushButton();
    twitter->setCursor(Qt::PointingHandCursor);
    twitter->setStyleSheet("QPushButton {border-image:url(:/twitter.jpg);}");
    twitter->setMaximumWidth(99);
    twitter->setMinimumHeight(130);
    QPushButton *email = new QPushButton();
    email->setCursor(Qt::PointingHandCursor);
    email->setStyleSheet("QPushButton {border-image:url(:/email.jpg);}");
    email->setMaximumWidth(99);
    email->setMinimumHeight(130);
    QPushButton *linkedin = new QPushButton();
    linkedin->setCursor(Qt::PointingHandCursor);
    linkedin->setStyleSheet("QPushButton {border-image:url(:/linkedin.jpg);}");
    linkedin->setMaximumWidth(99);
    linkedin->setMinimumHeight(130);
    QPushButton *tumblr = new QPushButton();
    tumblr->setCursor(Qt::PointingHandCursor);
    tumblr->setStyleSheet("QPushButton {border-image:url(:/tumblr.jpg);}");
    tumblr->setMaximumWidth(99);
    tumblr->setMinimumHeight(130);
    QHBoxLayout *shareiconlayout = new QHBoxLayout;
    shareiconlayout->addWidget(facebook);
    shareiconlayout->addWidget(twitter);
    shareiconlayout->addWidget(email);
    shareiconlayout->addWidget(linkedin);
    shareiconlayout->addWidget(tumblr);

    link = new QLineEdit;
    link->setText(links[2]);
    QPushButton *copy = new QPushButton("Copy");
    copy->setCursor(Qt::PointingHandCursor);
    copy->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
    link->setContentsMargins(20,20,20,20);

    sharelayout = new QVBoxLayout();
    sharelayout->addLayout(shareiconlayout);

    QHBoxLayout *copylink= new QHBoxLayout;
    copylink->addWidget(link);
    copylink->addWidget(copy);
    sharelayout->addLayout(copylink);
    sharelayout->setContentsMargins(70,30,70,50);

    shareWidget = new QWidget();
    shareWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    shareWidget->setLayout(sharelayout);
    shareWidget->setWindowTitle("Share");
    shareWidget->resize(600, 300);
    shareWidget->show();

    connect(facebook, &QPushButton::clicked, this, &Display::facebookHandler);
    connect(twitter, &QPushButton::clicked, this, &Display::twitterHandler);
    connect(email, &QPushButton::clicked, this, &Display::emailHandler);
    connect(linkedin, &QPushButton::clicked, this, &Display::linkedinHandler);
    connect(tumblr, &QPushButton::clicked, this, &Display::tumblrHandler);
    connect(copy, &QPushButton::clicked, this, &Display::copyHandler);
};

void Display::shareHandler4(){

    QPushButton *facebook = new QPushButton();
    facebook->setCursor(Qt::PointingHandCursor);
    facebook->setStyleSheet("QPushButton {border-image:url(:/facebook.jpg);}");
    facebook->setMaximumWidth(99);
    facebook->setMinimumHeight(130);
    QPushButton *twitter = new QPushButton();
    twitter->setCursor(Qt::PointingHandCursor);
    twitter->setStyleSheet("QPushButton {border-image:url(:/twitter.jpg);}");
    twitter->setMaximumWidth(99);
    twitter->setMinimumHeight(130);
    QPushButton *email = new QPushButton();
    email->setCursor(Qt::PointingHandCursor);
    email->setStyleSheet("QPushButton {border-image:url(:/email.jpg);}");
    email->setMaximumWidth(99);
    email->setMinimumHeight(130);
    QPushButton *linkedin = new QPushButton();
    linkedin->setCursor(Qt::PointingHandCursor);
    linkedin->setStyleSheet("QPushButton {border-image:url(:/linkedin.jpg);}");
    linkedin->setMaximumWidth(99);
    linkedin->setMinimumHeight(130);
    QPushButton *tumblr = new QPushButton();
    tumblr->setCursor(Qt::PointingHandCursor);
    tumblr->setStyleSheet("QPushButton {border-image:url(:/tumblr.jpg);}");
    tumblr->setMaximumWidth(99);
    tumblr->setMinimumHeight(130);
    QHBoxLayout *shareiconlayout = new QHBoxLayout;
    shareiconlayout->addWidget(facebook);
    shareiconlayout->addWidget(twitter);
    shareiconlayout->addWidget(email);
    shareiconlayout->addWidget(linkedin);
    shareiconlayout->addWidget(tumblr);

    link = new QLineEdit;
    link->setText(links[3]);
    QPushButton *copy = new QPushButton("Copy");
    copy->setCursor(Qt::PointingHandCursor);
    copy->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
    link->setContentsMargins(20,20,20,20);

    sharelayout = new QVBoxLayout();
    sharelayout->addLayout(shareiconlayout);

    QHBoxLayout *copylink= new QHBoxLayout;
    copylink->addWidget(link);
    copylink->addWidget(copy);
    sharelayout->addLayout(copylink);
    sharelayout->setContentsMargins(70,30,70,50);

    shareWidget = new QWidget();
    shareWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    shareWidget->setLayout(sharelayout);
    shareWidget->setWindowTitle("Share");
    shareWidget->resize(600, 300);
    shareWidget->show();

    connect(facebook, &QPushButton::clicked, this, &Display::facebookHandler);
    connect(twitter, &QPushButton::clicked, this, &Display::twitterHandler);
    connect(email, &QPushButton::clicked, this, &Display::emailHandler);
    connect(linkedin, &QPushButton::clicked, this, &Display::linkedinHandler);
    connect(tumblr, &QPushButton::clicked, this, &Display::tumblrHandler);
    connect(copy, &QPushButton::clicked, this, &Display::copyHandler);
};

void Display::shareHandler5(){

    QPushButton *facebook = new QPushButton();
    facebook->setCursor(Qt::PointingHandCursor);
    facebook->setStyleSheet("QPushButton {border-image:url(:/facebook.jpg);}");
    facebook->setMaximumWidth(99);
    facebook->setMinimumHeight(130);
    QPushButton *twitter = new QPushButton();
    twitter->setCursor(Qt::PointingHandCursor);
    twitter->setStyleSheet("QPushButton {border-image:url(:/twitter.jpg);}");
    twitter->setMaximumWidth(99);
    twitter->setMinimumHeight(130);
    QPushButton *email = new QPushButton();
    email->setCursor(Qt::PointingHandCursor);
    email->setStyleSheet("QPushButton {border-image:url(:/email.jpg);}");
    email->setMaximumWidth(99);
    email->setMinimumHeight(130);
    QPushButton *linkedin = new QPushButton();
    linkedin->setCursor(Qt::PointingHandCursor);
    linkedin->setStyleSheet("QPushButton {border-image:url(:/linkedin.jpg);}");
    linkedin->setMaximumWidth(99);
    linkedin->setMinimumHeight(130);
    QPushButton *tumblr = new QPushButton();
    tumblr->setCursor(Qt::PointingHandCursor);
    tumblr->setStyleSheet("QPushButton {border-image:url(:/tumblr.jpg);}");
    tumblr->setMaximumWidth(99);
    tumblr->setMinimumHeight(130);
    QHBoxLayout *shareiconlayout = new QHBoxLayout;
    shareiconlayout->addWidget(facebook);
    shareiconlayout->addWidget(twitter);
    shareiconlayout->addWidget(email);
    shareiconlayout->addWidget(linkedin);
    shareiconlayout->addWidget(tumblr);

    link = new QLineEdit;
    link->setText(links[4]);
    QPushButton *copy = new QPushButton("Copy");
    copy->setCursor(Qt::PointingHandCursor);
    copy->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
    link->setContentsMargins(20,20,20,20);

    sharelayout = new QVBoxLayout();
    sharelayout->addLayout(shareiconlayout);

    QHBoxLayout *copylink= new QHBoxLayout;
    copylink->addWidget(link);
    copylink->addWidget(copy);
    sharelayout->addLayout(copylink);
    sharelayout->setContentsMargins(70,30,70,50);

    shareWidget = new QWidget();
    shareWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    shareWidget->setLayout(sharelayout);
    shareWidget->setWindowTitle("Share");
    shareWidget->resize(600, 300);
    shareWidget->show();

    connect(facebook, &QPushButton::clicked, this, &Display::facebookHandler);
    connect(twitter, &QPushButton::clicked, this, &Display::twitterHandler);
    connect(email, &QPushButton::clicked, this, &Display::emailHandler);
    connect(linkedin, &QPushButton::clicked, this, &Display::linkedinHandler);
    connect(tumblr, &QPushButton::clicked, this, &Display::tumblrHandler);
    connect(copy, &QPushButton::clicked, this, &Display::copyHandler);
};

void Display::shareHandler6(){

    QPushButton *facebook = new QPushButton();
    facebook->setCursor(Qt::PointingHandCursor);
    facebook->setStyleSheet("QPushButton {border-image:url(:/facebook.jpg);}");
    facebook->setMaximumWidth(99);
    facebook->setMinimumHeight(130);
    QPushButton *twitter = new QPushButton();
    twitter->setCursor(Qt::PointingHandCursor);
    twitter->setStyleSheet("QPushButton {border-image:url(:/twitter.jpg);}");
    twitter->setMaximumWidth(99);
    twitter->setMinimumHeight(130);
    QPushButton *email = new QPushButton();
    email->setCursor(Qt::PointingHandCursor);
    email->setStyleSheet("QPushButton {border-image:url(:/email.jpg);}");
    email->setMaximumWidth(99);
    email->setMinimumHeight(130);
    QPushButton *linkedin = new QPushButton();
    linkedin->setCursor(Qt::PointingHandCursor);
    linkedin->setStyleSheet("QPushButton {border-image:url(:/linkedin.jpg);}");
    linkedin->setMaximumWidth(99);
    linkedin->setMinimumHeight(130);
    QPushButton *tumblr = new QPushButton();
    tumblr->setCursor(Qt::PointingHandCursor);
    tumblr->setStyleSheet("QPushButton {border-image:url(:/tumblr.jpg);}");
    tumblr->setMaximumWidth(99);
    tumblr->setMinimumHeight(130);
    QHBoxLayout *shareiconlayout = new QHBoxLayout;
    shareiconlayout->addWidget(facebook);
    shareiconlayout->addWidget(twitter);
    shareiconlayout->addWidget(email);
    shareiconlayout->addWidget(linkedin);
    shareiconlayout->addWidget(tumblr);

    link = new QLineEdit;
    link->setText(links[5]);
    QPushButton *copy = new QPushButton("Copy");
    copy->setCursor(Qt::PointingHandCursor);
    copy->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
    link->setContentsMargins(20,20,20,20);

    sharelayout = new QVBoxLayout();
    sharelayout->addLayout(shareiconlayout);

    QHBoxLayout *copylink= new QHBoxLayout;
    copylink->addWidget(link);
    copylink->addWidget(copy);
    sharelayout->addLayout(copylink);
    sharelayout->setContentsMargins(70,30,70,50);

    shareWidget = new QWidget();
    shareWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    shareWidget->setLayout(sharelayout);
    shareWidget->setWindowTitle("Share");
    shareWidget->resize(600, 300);
    shareWidget->show();

    connect(facebook, &QPushButton::clicked, this, &Display::facebookHandler);
    connect(twitter, &QPushButton::clicked, this, &Display::twitterHandler);
    connect(email, &QPushButton::clicked, this, &Display::emailHandler);
    connect(linkedin, &QPushButton::clicked, this, &Display::linkedinHandler);
    connect(tumblr, &QPushButton::clicked, this, &Display::tumblrHandler);
    connect(copy, &QPushButton::clicked, this, &Display::copyHandler);
};

void Display::shareHandler7(){

    QPushButton *facebook = new QPushButton();
    facebook->setCursor(Qt::PointingHandCursor);
    facebook->setStyleSheet("QPushButton {border-image:url(:/facebook.jpg);}");
    facebook->setMaximumWidth(99);
    facebook->setMinimumHeight(130);
    QPushButton *twitter = new QPushButton();
    twitter->setCursor(Qt::PointingHandCursor);
    twitter->setStyleSheet("QPushButton {border-image:url(:/twitter.jpg);}");
    twitter->setMaximumWidth(99);
    twitter->setMinimumHeight(130);
    QPushButton *email = new QPushButton();
    email->setCursor(Qt::PointingHandCursor);
    email->setStyleSheet("QPushButton {border-image:url(:/email.jpg);}");
    email->setMaximumWidth(99);
    email->setMinimumHeight(130);
    QPushButton *linkedin = new QPushButton();
    linkedin->setCursor(Qt::PointingHandCursor);
    linkedin->setStyleSheet("QPushButton {border-image:url(:/linkedin.jpg);}");
    linkedin->setMaximumWidth(99);
    linkedin->setMinimumHeight(130);
    QPushButton *tumblr = new QPushButton();
    tumblr->setCursor(Qt::PointingHandCursor);
    tumblr->setStyleSheet("QPushButton {border-image:url(:/tumblr.jpg);}");
    tumblr->setMaximumWidth(99);
    tumblr->setMinimumHeight(130);
    QHBoxLayout *shareiconlayout = new QHBoxLayout;
    shareiconlayout->addWidget(facebook);
    shareiconlayout->addWidget(twitter);
    shareiconlayout->addWidget(email);
    shareiconlayout->addWidget(linkedin);
    shareiconlayout->addWidget(tumblr);

    link = new QLineEdit;
    link->setText(links[6]);
    QPushButton *copy = new QPushButton("Copy");
    copy->setCursor(Qt::PointingHandCursor);
    copy->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
    link->setContentsMargins(20,20,20,20);

    sharelayout = new QVBoxLayout();
    sharelayout->addLayout(shareiconlayout);

    QHBoxLayout *copylink= new QHBoxLayout;
    copylink->addWidget(link);
    copylink->addWidget(copy);
    sharelayout->addLayout(copylink);
    sharelayout->setContentsMargins(70,30,70,50);

    shareWidget = new QWidget();
    shareWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    shareWidget->setLayout(sharelayout);
    shareWidget->setWindowTitle("Share");
    shareWidget->resize(600, 300);
    shareWidget->show();

    connect(facebook, &QPushButton::clicked, this, &Display::facebookHandler);
    connect(twitter, &QPushButton::clicked, this, &Display::twitterHandler);
    connect(email, &QPushButton::clicked, this, &Display::emailHandler);
    connect(linkedin, &QPushButton::clicked, this, &Display::linkedinHandler);
    connect(tumblr, &QPushButton::clicked, this, &Display::tumblrHandler);
    connect(copy, &QPushButton::clicked, this, &Display::copyHandler);
};

void Display::shareHandler8(){

    QPushButton *facebook = new QPushButton();
    facebook->setCursor(Qt::PointingHandCursor);
    facebook->setStyleSheet("QPushButton {border-image:url(:/facebook.jpg);}");
    facebook->setMaximumWidth(99);
    facebook->setMinimumHeight(130);
    QPushButton *twitter = new QPushButton();
    twitter->setCursor(Qt::PointingHandCursor);
    twitter->setStyleSheet("QPushButton {border-image:url(:/twitter.jpg);}");
    twitter->setMaximumWidth(99);
    twitter->setMinimumHeight(130);
    QPushButton *email = new QPushButton();
    email->setCursor(Qt::PointingHandCursor);
    email->setStyleSheet("QPushButton {border-image:url(:/email.jpg);}");
    email->setMaximumWidth(99);
    email->setMinimumHeight(130);
    QPushButton *linkedin = new QPushButton();
    linkedin->setCursor(Qt::PointingHandCursor);
    linkedin->setStyleSheet("QPushButton {border-image:url(:/linkedin.jpg);}");
    linkedin->setMaximumWidth(99);
    linkedin->setMinimumHeight(130);
    QPushButton *tumblr = new QPushButton();
    tumblr->setCursor(Qt::PointingHandCursor);
    tumblr->setStyleSheet("QPushButton {border-image:url(:/tumblr.jpg);}");
    tumblr->setMaximumWidth(99);
    tumblr->setMinimumHeight(130);
    QHBoxLayout *shareiconlayout = new QHBoxLayout;
    shareiconlayout->addWidget(facebook);
    shareiconlayout->addWidget(twitter);
    shareiconlayout->addWidget(email);
    shareiconlayout->addWidget(linkedin);
    shareiconlayout->addWidget(tumblr);

    link = new QLineEdit;
    link->setText(links[7]);
    QPushButton *copy = new QPushButton("Copy");
    copy->setCursor(Qt::PointingHandCursor);
    copy->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
    link->setContentsMargins(20,20,20,20);

    sharelayout = new QVBoxLayout();
    sharelayout->addLayout(shareiconlayout);

    QHBoxLayout *copylink= new QHBoxLayout;
    copylink->addWidget(link);
    copylink->addWidget(copy);
    sharelayout->addLayout(copylink);
    sharelayout->setContentsMargins(70,30,70,50);

    shareWidget = new QWidget();
    shareWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    shareWidget->setLayout(sharelayout);
    shareWidget->setWindowTitle("Share");
    shareWidget->resize(600, 300);
    shareWidget->show();

    connect(facebook, &QPushButton::clicked, this, &Display::facebookHandler);
    connect(twitter, &QPushButton::clicked, this, &Display::twitterHandler);
    connect(email, &QPushButton::clicked, this, &Display::emailHandler);
    connect(linkedin, &QPushButton::clicked, this, &Display::linkedinHandler);
    connect(tumblr, &QPushButton::clicked, this, &Display::tumblrHandler);
    connect(copy, &QPushButton::clicked, this, &Display::copyHandler);
};

void Display::shareHandler9(){

    QPushButton *facebook = new QPushButton();
    facebook->setCursor(Qt::PointingHandCursor);
    facebook->setStyleSheet("QPushButton {border-image:url(:/facebook.jpg);}");
    facebook->setMaximumWidth(99);
    facebook->setMinimumHeight(130);
    QPushButton *twitter = new QPushButton();
    twitter->setCursor(Qt::PointingHandCursor);
    twitter->setStyleSheet("QPushButton {border-image:url(:/twitter.jpg);}");
    twitter->setMaximumWidth(99);
    twitter->setMinimumHeight(130);
    QPushButton *email = new QPushButton();
    email->setCursor(Qt::PointingHandCursor);
    email->setStyleSheet("QPushButton {border-image:url(:/email.jpg);}");
    email->setMaximumWidth(99);
    email->setMinimumHeight(130);
    QPushButton *linkedin = new QPushButton();
    linkedin->setCursor(Qt::PointingHandCursor);
    linkedin->setStyleSheet("QPushButton {border-image:url(:/linkedin.jpg);}");
    linkedin->setMaximumWidth(99);
    linkedin->setMinimumHeight(130);
    QPushButton *tumblr = new QPushButton();
    tumblr->setCursor(Qt::PointingHandCursor);
    tumblr->setStyleSheet("QPushButton {border-image:url(:/tumblr.jpg);}");
    tumblr->setMaximumWidth(99);
    tumblr->setMinimumHeight(130);
    QHBoxLayout *shareiconlayout = new QHBoxLayout;
    shareiconlayout->addWidget(facebook);
    shareiconlayout->addWidget(twitter);
    shareiconlayout->addWidget(email);
    shareiconlayout->addWidget(linkedin);
    shareiconlayout->addWidget(tumblr);

    link = new QLineEdit;
    link->setText(links[8]);
    QPushButton *copy = new QPushButton("Copy");
    copy->setCursor(Qt::PointingHandCursor);
    copy->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
    link->setContentsMargins(20,20,20,20);

    sharelayout = new QVBoxLayout();
    sharelayout->addLayout(shareiconlayout);

    QHBoxLayout *copylink= new QHBoxLayout;
    copylink->addWidget(link);
    copylink->addWidget(copy);
    sharelayout->addLayout(copylink);
    sharelayout->setContentsMargins(70,30,70,50);

    shareWidget = new QWidget();
    shareWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    shareWidget->setLayout(sharelayout);
    shareWidget->setWindowTitle("Share");
    shareWidget->resize(600, 300);
    shareWidget->show();

    connect(facebook, &QPushButton::clicked, this, &Display::facebookHandler);
    connect(twitter, &QPushButton::clicked, this, &Display::twitterHandler);
    connect(email, &QPushButton::clicked, this, &Display::emailHandler);
    connect(linkedin, &QPushButton::clicked, this, &Display::linkedinHandler);
    connect(tumblr, &QPushButton::clicked, this, &Display::tumblrHandler);
    connect(copy, &QPushButton::clicked, this, &Display::copyHandler);
};

void Display::shareHandler10(){

    QPushButton *facebook = new QPushButton();
    facebook->setCursor(Qt::PointingHandCursor);
    facebook->setStyleSheet("QPushButton {border-image:url(:/facebook.jpg);}");
    facebook->setMaximumWidth(99);
    facebook->setMinimumHeight(130);
    QPushButton *twitter = new QPushButton();
    twitter->setCursor(Qt::PointingHandCursor);
    twitter->setStyleSheet("QPushButton {border-image:url(:/twitter.jpg);}");
    twitter->setMaximumWidth(99);
    twitter->setMinimumHeight(130);
    QPushButton *email = new QPushButton();
    email->setCursor(Qt::PointingHandCursor);
    email->setStyleSheet("QPushButton {border-image:url(:/email.jpg);}");
    email->setMaximumWidth(99);
    email->setMinimumHeight(130);
    QPushButton *linkedin = new QPushButton();
    linkedin->setCursor(Qt::PointingHandCursor);
    linkedin->setStyleSheet("QPushButton {border-image:url(:/linkedin.jpg);}");
    linkedin->setMaximumWidth(99);
    linkedin->setMinimumHeight(130);
    QPushButton *tumblr = new QPushButton();
    tumblr->setCursor(Qt::PointingHandCursor);
    tumblr->setStyleSheet("QPushButton {border-image:url(:/tumblr.jpg);}");
    tumblr->setMaximumWidth(99);
    tumblr->setMinimumHeight(130);
    QHBoxLayout *shareiconlayout = new QHBoxLayout;
    shareiconlayout->addWidget(facebook);
    shareiconlayout->addWidget(twitter);
    shareiconlayout->addWidget(email);
    shareiconlayout->addWidget(linkedin);
    shareiconlayout->addWidget(tumblr);

    link = new QLineEdit;
    link->setText(links[9]);
    QPushButton *copy = new QPushButton("Copy");
    copy->setCursor(Qt::PointingHandCursor);
    copy->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
    link->setContentsMargins(20,20,20,20);

    sharelayout = new QVBoxLayout();
    sharelayout->addLayout(shareiconlayout);

    QHBoxLayout *copylink= new QHBoxLayout;
    copylink->addWidget(link);
    copylink->addWidget(copy);
    sharelayout->addLayout(copylink);
    sharelayout->setContentsMargins(70,30,70,50);

    shareWidget = new QWidget();
    shareWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    shareWidget->setLayout(sharelayout);
    shareWidget->setWindowTitle("Share");
    shareWidget->resize(600, 300);
    shareWidget->show();

    connect(facebook, &QPushButton::clicked, this, &Display::facebookHandler);
    connect(twitter, &QPushButton::clicked, this, &Display::twitterHandler);
    connect(email, &QPushButton::clicked, this, &Display::emailHandler);
    connect(linkedin, &QPushButton::clicked, this, &Display::linkedinHandler);
    connect(tumblr, &QPushButton::clicked, this, &Display::tumblrHandler);
    connect(copy, &QPushButton::clicked, this, &Display::copyHandler);
};


void Display::facebookHandler(){
    QString link = "https://www.facebook.com/";
    QDesktopServices::openUrl(QUrl(link));
}

void Display::twitterHandler(){
    QString link = "https://twitter.com/login?lang=en";
    QDesktopServices::openUrl(QUrl(link));
}

void Display::emailHandler(){
    QString link = "https://accounts.google.com/";
    QDesktopServices::openUrl(QUrl(link));
}

void Display::linkedinHandler(){
    QString link = "https://www.linkedin.com/login";
    QDesktopServices::openUrl(QUrl(link));
}

void Display::tumblrHandler(){
    QString link = "https://www.tumblr.com/";
    QDesktopServices::openUrl(QUrl(link));
}

void Display::copyHandler(){
    link->selectAll();
    link->copy();
}

void Display::addtoFavouritesHandler1(){

     //article image and title
     QPixmap articleImg1(":/save1.jpg");
     QLabel *fav_imglabel = new QLabel();
     QLabel *fav_title = new QLabel();
     fav_title->setWordWrap(true);

     fav_imglabel->setPixmap(articleImg1);
     fav_imglabel->setMaximumWidth(210);
     fav_imglabel->setMinimumHeight(115);
     fav_title->setStyleSheet("QLabel { font-size: 20px; }");
     fav_title->setText(articles[0].m_title);
     fav_title->setMaximumWidth(300);
     fav_title->setMinimumHeight(115);
     QHBoxLayout *articletosave = new QHBoxLayout();
     articletosave->addWidget(fav_imglabel);
     articletosave->addWidget(fav_title);

     QFrame *topborder = new QFrame();
     topborder->setFrameShape(QFrame::HLine);
     topborder->setFrameShadow(QFrame::Sunken);
     topborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");
     QFrame *bottomborder = new QFrame();
     bottomborder->setFrameShape(QFrame::HLine);
     bottomborder->setFrameShadow(QFrame::Sunken);
     bottomborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");

    QLabel *spacingRow = new QLabel();
     saveasField = new QLineEdit();
     saveasField->setText(articles[0].m_title);
     QPushButton *save= new QPushButton("SAVE");
     save->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
     QPushButton *newlist= new QPushButton("+ Create New List");
     newlist->setStyleSheet("QPushButton { color: ##f0f0f0; background-color: #FFFFFF; font-size: 15px; }");

     QFormLayout *flayoutSaveas = new QFormLayout();
     QLabel *saveas = new QLabel("Save As:");
     saveas->setStyleSheet("QLabel {font-weight: bold;}");
     flayoutSaveas->addRow(saveas, saveasField);
     QLabel *savetolist = new QLabel("Save To List:");
     savetolist->setStyleSheet("QLabel {font-weight: bold;}");

     //checkboxes for lists
     lists = new QVBoxLayout();
     for(int i = 0;i < favlists[0]->count() && favlists[0][i] != ""; ++i)
     {
         if(favlists[0][i] != ""){
            dynamic[i] = new QCheckBox(favlists[0][i]);
            lists->addWidget(dynamic[i]);
         }
     }
     flayoutSaveas->addRow(spacingRow);
     flayoutSaveas->addRow(savetolist, lists);
     flayoutSaveas->setContentsMargins(0,50,0,50);

     saveaslayout = new QVBoxLayout;
     saveaslayout->addWidget(topborder);
     saveaslayout->addLayout(articletosave);
     saveaslayout->addWidget(bottomborder);
     //saveaslayout->addWidget(spacingRow);
     saveaslayout->addLayout(flayoutSaveas);
     //saveaslayout->addLayout(lists);
     saveaslayout->addWidget(newlist);
     saveaslayout->addWidget(save);
     saveaslayout->setContentsMargins(20,20,20,20);

    addtoWidget = new QWidget();
    addtoWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    addtoWidget->setLayout(saveaslayout);
    addtoWidget->setWindowTitle("Save to Favourites");
    addtoWidget->resize(510, 300);
    addtoWidget->show();

   connect(save, &QPushButton::clicked, this, &Display::saveHandler);
   connect(newlist, &QPushButton::clicked, this, &Display::newlistHandler1);

}

void Display::addtoFavouritesHandler2(){

     //article image and title
     QPixmap articleImg2(":/save2.jpg");
     QLabel *fav_imglabel = new QLabel();
     QLabel *fav_title = new QLabel();
     fav_title->setWordWrap(true);

     fav_imglabel->setPixmap(articleImg2);
     fav_imglabel->setMaximumWidth(210);
     fav_imglabel->setMinimumHeight(115);
     fav_title->setStyleSheet("QLabel { font-size: 20px; }");
     fav_title->setText(articles[1].m_title);
     fav_title->setMaximumWidth(300);
     fav_title->setMinimumHeight(115);
     QHBoxLayout *articletosave = new QHBoxLayout();
     articletosave->addWidget(fav_imglabel);
     articletosave->addWidget(fav_title);

     QFrame *topborder = new QFrame();
     topborder->setFrameShape(QFrame::HLine);
     topborder->setFrameShadow(QFrame::Sunken);
     topborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");
     QFrame *bottomborder = new QFrame();
     bottomborder->setFrameShape(QFrame::HLine);
     bottomborder->setFrameShadow(QFrame::Sunken);
     bottomborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");

    QLabel *spacingRow = new QLabel();
     saveasField = new QLineEdit();
     saveasField->setText(articles[1].m_title);
     QPushButton *save= new QPushButton("SAVE");
     save->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
     QPushButton *newlist= new QPushButton("+ Create New List");
     newlist->setStyleSheet("QPushButton { color: ##f0f0f0; background-color: #FFFFFF; font-size: 15px; }");

     QFormLayout *flayoutSaveas = new QFormLayout();
     QLabel *saveas = new QLabel("Save As:");
     saveas->setStyleSheet("QLabel {font-weight: bold;}");
     flayoutSaveas->addRow(saveas, saveasField);
     QLabel *savetolist = new QLabel("Save To List:");
     savetolist->setStyleSheet("QLabel {font-weight: bold;}");

     //checkboxes for lists
     lists = new QVBoxLayout();
     for(int i = 0;i < favlists[0]->count() && favlists[0][i] != ""; ++i)
     {
         if(favlists[0][i] != ""){
            dynamic[i] = new QCheckBox(favlists[0][i]);
            lists->addWidget(dynamic[i]);
         }
     }
     flayoutSaveas->addRow(spacingRow);
     flayoutSaveas->addRow(savetolist, lists);
     flayoutSaveas->setContentsMargins(0,50,0,50);

     saveaslayout = new QVBoxLayout;
     saveaslayout->addWidget(topborder);
     saveaslayout->addLayout(articletosave);
     saveaslayout->addWidget(bottomborder);
     //saveaslayout->addWidget(spacingRow);
     saveaslayout->addLayout(flayoutSaveas);
     //saveaslayout->addLayout(lists);
     saveaslayout->addWidget(newlist);
     saveaslayout->addWidget(save);
     saveaslayout->setContentsMargins(20,20,20,20);

    addtoWidget = new QWidget();
    addtoWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    addtoWidget->setLayout(saveaslayout);
    addtoWidget->setWindowTitle("Save to Favourites");
    addtoWidget->resize(510, 300);
    addtoWidget->show();

   connect(save, &QPushButton::clicked, this, &Display::saveHandler);
   connect(newlist, &QPushButton::clicked, this, &Display::newlistHandler2);

}

void Display::addtoFavouritesHandler3(){

     //article image and title
     QPixmap articleImg3(":/save3.jpg");
     QLabel *fav_imglabel = new QLabel();
     QLabel *fav_title = new QLabel();
     fav_title->setWordWrap(true);

     fav_imglabel->setPixmap(articleImg3);
     fav_imglabel->setMaximumWidth(210);
     fav_imglabel->setMinimumHeight(115);
     fav_title->setStyleSheet("QLabel { font-size: 20px; }");
     fav_title->setText(articles[2].m_title);
     fav_title->setMaximumWidth(300);
     fav_title->setMinimumHeight(115);
     QHBoxLayout *articletosave = new QHBoxLayout();
     articletosave->addWidget(fav_imglabel);
     articletosave->addWidget(fav_title);

     QFrame *topborder = new QFrame();
     topborder->setFrameShape(QFrame::HLine);
     topborder->setFrameShadow(QFrame::Sunken);
     topborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");
     QFrame *bottomborder = new QFrame();
     bottomborder->setFrameShape(QFrame::HLine);
     bottomborder->setFrameShadow(QFrame::Sunken);
     bottomborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");

    QLabel *spacingRow = new QLabel();
     saveasField = new QLineEdit();
     saveasField->setText(articles[2].m_title);
     QPushButton *save= new QPushButton("SAVE");
     save->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
     QPushButton *newlist= new QPushButton("+ Create New List");
     newlist->setStyleSheet("QPushButton { color: ##f0f0f0; background-color: #FFFFFF; font-size: 15px; }");

     QFormLayout *flayoutSaveas = new QFormLayout();
     QLabel *saveas = new QLabel("Save As:");
     saveas->setStyleSheet("QLabel {font-weight: bold;}");
     flayoutSaveas->addRow(saveas, saveasField);
     QLabel *savetolist = new QLabel("Save To List:");
     savetolist->setStyleSheet("QLabel {font-weight: bold;}");

     //checkboxes for lists
     lists = new QVBoxLayout();
     for(int i = 0;i < favlists[0]->count() && favlists[0][i] != ""; ++i)
     {
         if(favlists[0][i] != ""){
            dynamic[i] = new QCheckBox(favlists[0][i]);
            lists->addWidget(dynamic[i]);
         }
     }
     flayoutSaveas->addRow(spacingRow);
     flayoutSaveas->addRow(savetolist, lists);
     flayoutSaveas->setContentsMargins(0,50,0,50);

     saveaslayout = new QVBoxLayout;
     saveaslayout->addWidget(topborder);
     saveaslayout->addLayout(articletosave);
     saveaslayout->addWidget(bottomborder);
     //saveaslayout->addWidget(spacingRow);
     saveaslayout->addLayout(flayoutSaveas);
     //saveaslayout->addLayout(lists);
     saveaslayout->addWidget(newlist);
     saveaslayout->addWidget(save);
     saveaslayout->setContentsMargins(20,20,20,20);

    addtoWidget = new QWidget();
    addtoWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    addtoWidget->setLayout(saveaslayout);
    addtoWidget->setWindowTitle("Save to Favourites");
    addtoWidget->resize(510, 300);
    addtoWidget->show();

   connect(save, &QPushButton::clicked, this, &Display::saveHandler);
   connect(newlist, &QPushButton::clicked, this, &Display::newlistHandler3);

}

void Display::addtoFavouritesHandler4(){

     //article image and title
     QPixmap articleImg4(":/save4.jpg");
     QLabel *fav_imglabel = new QLabel();
     QLabel *fav_title = new QLabel();
     fav_title->setWordWrap(true);

     fav_imglabel->setPixmap(articleImg4);
     fav_imglabel->setMaximumWidth(210);
     fav_imglabel->setMinimumHeight(115);
     fav_title->setStyleSheet("QLabel { font-size: 20px; }");
     fav_title->setText(articles[3].m_title);
     fav_title->setMaximumWidth(300);
     fav_title->setMinimumHeight(115);
     QHBoxLayout *articletosave = new QHBoxLayout();
     articletosave->addWidget(fav_imglabel);
     articletosave->addWidget(fav_title);

     QFrame *topborder = new QFrame();
     topborder->setFrameShape(QFrame::HLine);
     topborder->setFrameShadow(QFrame::Sunken);
     topborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");
     QFrame *bottomborder = new QFrame();
     bottomborder->setFrameShape(QFrame::HLine);
     bottomborder->setFrameShadow(QFrame::Sunken);
     bottomborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");

    QLabel *spacingRow = new QLabel();
     saveasField = new QLineEdit();
     saveasField->setText(articles[3].m_title);
     QPushButton *save= new QPushButton("SAVE");
     save->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
     QPushButton *newlist= new QPushButton("+ Create New List");
     newlist->setStyleSheet("QPushButton { color: ##f0f0f0; background-color: #FFFFFF; font-size: 15px; }");

     QFormLayout *flayoutSaveas = new QFormLayout();
     QLabel *saveas = new QLabel("Save As:");
     saveas->setStyleSheet("QLabel {font-weight: bold;}");
     flayoutSaveas->addRow(saveas, saveasField);
     QLabel *savetolist = new QLabel("Save To List:");
     savetolist->setStyleSheet("QLabel {font-weight: bold;}");

     //checkboxes for lists
     lists = new QVBoxLayout();
     for(int i = 0;i < favlists[0]->count() && favlists[0][i] != ""; ++i)
     {
         if(favlists[0][i] != ""){
            dynamic[i] = new QCheckBox(favlists[0][i]);
            lists->addWidget(dynamic[i]);
         }
     }
     flayoutSaveas->addRow(spacingRow);
     flayoutSaveas->addRow(savetolist, lists);
     flayoutSaveas->setContentsMargins(0,50,0,50);

     saveaslayout = new QVBoxLayout;
     saveaslayout->addWidget(topborder);
     saveaslayout->addLayout(articletosave);
     saveaslayout->addWidget(bottomborder);
     //saveaslayout->addWidget(spacingRow);
     saveaslayout->addLayout(flayoutSaveas);
     //saveaslayout->addLayout(lists);
     saveaslayout->addWidget(newlist);
     saveaslayout->addWidget(save);
     saveaslayout->setContentsMargins(20,20,20,20);

    addtoWidget = new QWidget();
    addtoWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    addtoWidget->setLayout(saveaslayout);
    addtoWidget->setWindowTitle("Save to Favourites");
    addtoWidget->resize(510, 300);
    addtoWidget->show();

   connect(save, &QPushButton::clicked, this, &Display::saveHandler);
   connect(newlist, &QPushButton::clicked, this, &Display::newlistHandler4);

}

void Display::addtoFavouritesHandler5(){

     //article image and title
     QPixmap articleImg5(":/save5.jpg");
     QLabel *fav_imglabel = new QLabel();
     QLabel *fav_title = new QLabel();
     fav_title->setWordWrap(true);

     fav_imglabel->setPixmap(articleImg5);
     fav_imglabel->setMaximumWidth(210);
     fav_imglabel->setMinimumHeight(115);
     fav_title->setStyleSheet("QLabel { font-size: 20px; }");
     fav_title->setText(articles[4].m_title);
     fav_title->setMaximumWidth(300);
     fav_title->setMinimumHeight(115);
     QHBoxLayout *articletosave = new QHBoxLayout();
     articletosave->addWidget(fav_imglabel);
     articletosave->addWidget(fav_title);

     QFrame *topborder = new QFrame();
     topborder->setFrameShape(QFrame::HLine);
     topborder->setFrameShadow(QFrame::Sunken);
     topborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");
     QFrame *bottomborder = new QFrame();
     bottomborder->setFrameShape(QFrame::HLine);
     bottomborder->setFrameShadow(QFrame::Sunken);
     bottomborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");

    QLabel *spacingRow = new QLabel();
     saveasField = new QLineEdit();
     saveasField->setText(articles[4].m_title);
     QPushButton *save= new QPushButton("SAVE");
     save->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
     QPushButton *newlist= new QPushButton("+ Create New List");
     newlist->setStyleSheet("QPushButton { color: ##f0f0f0; background-color: #FFFFFF; font-size: 15px; }");

     QFormLayout *flayoutSaveas = new QFormLayout();
     QLabel *saveas = new QLabel("Save As:");
     saveas->setStyleSheet("QLabel {font-weight: bold;}");
     flayoutSaveas->addRow(saveas, saveasField);
     QLabel *savetolist = new QLabel("Save To List:");
     savetolist->setStyleSheet("QLabel {font-weight: bold;}");

     //checkboxes for lists
     lists = new QVBoxLayout();
     for(int i = 0;i < favlists[0]->count() && favlists[0][i] != ""; ++i)
     {
         if(favlists[0][i] != ""){
            dynamic[i] = new QCheckBox(favlists[0][i]);
            lists->addWidget(dynamic[i]);
         }
     }
     flayoutSaveas->addRow(spacingRow);
     flayoutSaveas->addRow(savetolist, lists);
     flayoutSaveas->setContentsMargins(0,50,0,50);

     saveaslayout = new QVBoxLayout;
     saveaslayout->addWidget(topborder);
     saveaslayout->addLayout(articletosave);
     saveaslayout->addWidget(bottomborder);
     //saveaslayout->addWidget(spacingRow);
     saveaslayout->addLayout(flayoutSaveas);
     //saveaslayout->addLayout(lists);
     saveaslayout->addWidget(newlist);
     saveaslayout->addWidget(save);
     saveaslayout->setContentsMargins(20,20,20,20);

    addtoWidget = new QWidget();
    addtoWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    addtoWidget->setLayout(saveaslayout);
    addtoWidget->setWindowTitle("Save to Favourites");
    addtoWidget->resize(510, 300);
    addtoWidget->show();

   connect(save, &QPushButton::clicked, this, &Display::saveHandler);
   connect(newlist, &QPushButton::clicked, this, &Display::newlistHandler5);

}

void Display::addtoFavouritesHandler6(){

     //article image and title
     QPixmap articleImg6(":/save6.jpg");
     QLabel *fav_imglabel = new QLabel();
     QLabel *fav_title = new QLabel();
     fav_title->setWordWrap(true);

     fav_imglabel->setPixmap(articleImg6);
     fav_imglabel->setMaximumWidth(210);
     fav_imglabel->setMinimumHeight(115);
     fav_title->setStyleSheet("QLabel { font-size: 20px; }");
     fav_title->setText(articles[5].m_title);
     fav_title->setMaximumWidth(300);
     fav_title->setMinimumHeight(115);
     QHBoxLayout *articletosave = new QHBoxLayout();
     articletosave->addWidget(fav_imglabel);
     articletosave->addWidget(fav_title);

     QFrame *topborder = new QFrame();
     topborder->setFrameShape(QFrame::HLine);
     topborder->setFrameShadow(QFrame::Sunken);
     topborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");
     QFrame *bottomborder = new QFrame();
     bottomborder->setFrameShape(QFrame::HLine);
     bottomborder->setFrameShadow(QFrame::Sunken);
     bottomborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");

    QLabel *spacingRow = new QLabel();
     saveasField = new QLineEdit();
     saveasField->setText(articles[5].m_title);
     QPushButton *save= new QPushButton("SAVE");
     save->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
     QPushButton *newlist= new QPushButton("+ Create New List");
     newlist->setStyleSheet("QPushButton { color: ##f0f0f0; background-color: #FFFFFF; font-size: 15px; }");

     QFormLayout *flayoutSaveas = new QFormLayout();
     QLabel *saveas = new QLabel("Save As:");
     saveas->setStyleSheet("QLabel {font-weight: bold;}");
     flayoutSaveas->addRow(saveas, saveasField);
     QLabel *savetolist = new QLabel("Save To List:");
     savetolist->setStyleSheet("QLabel {font-weight: bold;}");

     //checkboxes for lists
     lists = new QVBoxLayout();
     for(int i = 0;i < favlists[0]->count() && favlists[0][i] != ""; ++i)
     {
         if(favlists[0][i] != ""){
            dynamic[i] = new QCheckBox(favlists[0][i]);
            lists->addWidget(dynamic[i]);
         }
     }
     flayoutSaveas->addRow(spacingRow);
     flayoutSaveas->addRow(savetolist, lists);
     flayoutSaveas->setContentsMargins(0,50,0,50);

     saveaslayout = new QVBoxLayout;
     saveaslayout->addWidget(topborder);
     saveaslayout->addLayout(articletosave);
     saveaslayout->addWidget(bottomborder);
     //saveaslayout->addWidget(spacingRow);
     saveaslayout->addLayout(flayoutSaveas);
     //saveaslayout->addLayout(lists);
     saveaslayout->addWidget(newlist);
     saveaslayout->addWidget(save);
     saveaslayout->setContentsMargins(20,20,20,20);

    addtoWidget = new QWidget();
    addtoWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    addtoWidget->setLayout(saveaslayout);
    addtoWidget->setWindowTitle("Save to Favourites");
    addtoWidget->resize(510, 300);
    addtoWidget->show();

   connect(save, &QPushButton::clicked, this, &Display::saveHandler);
   connect(newlist, &QPushButton::clicked, this, &Display::newlistHandler6);

}

void Display::addtoFavouritesHandler7(){

     //article image and title
     QPixmap articleImg7(":/save7.jpg");
     QLabel *fav_imglabel = new QLabel();
     QLabel *fav_title = new QLabel();
     fav_title->setWordWrap(true);

     fav_imglabel->setPixmap(articleImg7);
     fav_imglabel->setMaximumWidth(210);
     fav_imglabel->setMinimumHeight(115);
     fav_title->setStyleSheet("QLabel { font-size: 20px; }");
     fav_title->setText(articles[6].m_title);
     fav_title->setMaximumWidth(300);
     fav_title->setMinimumHeight(115);
     QHBoxLayout *articletosave = new QHBoxLayout();
     articletosave->addWidget(fav_imglabel);
     articletosave->addWidget(fav_title);

     QFrame *topborder = new QFrame();
     topborder->setFrameShape(QFrame::HLine);
     topborder->setFrameShadow(QFrame::Sunken);
     topborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");
     QFrame *bottomborder = new QFrame();
     bottomborder->setFrameShape(QFrame::HLine);
     bottomborder->setFrameShadow(QFrame::Sunken);
     bottomborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");

    QLabel *spacingRow = new QLabel();
     saveasField = new QLineEdit();
     saveasField->setText(articles[6].m_title);
     QPushButton *save= new QPushButton("SAVE");
     save->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
     QPushButton *newlist= new QPushButton("+ Create New List");
     newlist->setStyleSheet("QPushButton { color: ##f0f0f0; background-color: #FFFFFF; font-size: 15px; }");

     QFormLayout *flayoutSaveas = new QFormLayout();
     QLabel *saveas = new QLabel("Save As:");
     saveas->setStyleSheet("QLabel {font-weight: bold;}");
     flayoutSaveas->addRow(saveas, saveasField);
     QLabel *savetolist = new QLabel("Save To List:");
     savetolist->setStyleSheet("QLabel {font-weight: bold;}");

     //checkboxes for lists
     lists = new QVBoxLayout();
     for(int i = 0;i < favlists[0]->count() && favlists[0][i] != ""; ++i)
     {
         if(favlists[0][i] != ""){
            dynamic[i] = new QCheckBox(favlists[0][i]);
            lists->addWidget(dynamic[i]);
         }
     }
     flayoutSaveas->addRow(spacingRow);
     flayoutSaveas->addRow(savetolist, lists);
     flayoutSaveas->setContentsMargins(0,50,0,50);

     saveaslayout = new QVBoxLayout;
     saveaslayout->addWidget(topborder);
     saveaslayout->addLayout(articletosave);
     saveaslayout->addWidget(bottomborder);
     //saveaslayout->addWidget(spacingRow);
     saveaslayout->addLayout(flayoutSaveas);
     //saveaslayout->addLayout(lists);
     saveaslayout->addWidget(newlist);
     saveaslayout->addWidget(save);
     saveaslayout->setContentsMargins(20,20,20,20);

    addtoWidget = new QWidget();
    addtoWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    addtoWidget->setLayout(saveaslayout);
    addtoWidget->setWindowTitle("Save to Favourites");
    addtoWidget->resize(510, 300);
    addtoWidget->show();

   connect(save, &QPushButton::clicked, this, &Display::saveHandler);
   connect(newlist, &QPushButton::clicked, this, &Display::newlistHandler7);

}

void Display::addtoFavouritesHandler8(){

     //article image and title
     QPixmap articleImg8(":/save8.jpg");
     QLabel *fav_imglabel = new QLabel();
     QLabel *fav_title = new QLabel();
     fav_title->setWordWrap(true);

     fav_imglabel->setPixmap(articleImg8);
     fav_imglabel->setMaximumWidth(210);
     fav_imglabel->setMinimumHeight(115);
     fav_title->setStyleSheet("QLabel { font-size: 20px; }");
     fav_title->setText(articles[7].m_title);
     fav_title->setMaximumWidth(300);
     fav_title->setMinimumHeight(115);
     QHBoxLayout *articletosave = new QHBoxLayout();
     articletosave->addWidget(fav_imglabel);
     articletosave->addWidget(fav_title);

     QFrame *topborder = new QFrame();
     topborder->setFrameShape(QFrame::HLine);
     topborder->setFrameShadow(QFrame::Sunken);
     topborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");
     QFrame *bottomborder = new QFrame();
     bottomborder->setFrameShape(QFrame::HLine);
     bottomborder->setFrameShadow(QFrame::Sunken);
     bottomborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");

    QLabel *spacingRow = new QLabel();
     saveasField = new QLineEdit();
     saveasField->setText(articles[7].m_title);
     QPushButton *save= new QPushButton("SAVE");
     save->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
     QPushButton *newlist= new QPushButton("+ Create New List");
     newlist->setStyleSheet("QPushButton { color: ##f0f0f0; background-color: #FFFFFF; font-size: 15px; }");

     QFormLayout *flayoutSaveas = new QFormLayout();
     QLabel *saveas = new QLabel("Save As:");
     saveas->setStyleSheet("QLabel {font-weight: bold;}");
     flayoutSaveas->addRow(saveas, saveasField);
     QLabel *savetolist = new QLabel("Save To List:");
     savetolist->setStyleSheet("QLabel {font-weight: bold;}");

     //checkboxes for lists
     lists = new QVBoxLayout();
     for(int i = 0;i < favlists[0]->count() && favlists[0][i] != ""; ++i)
     {
         if(favlists[0][i] != ""){
            dynamic[i] = new QCheckBox(favlists[0][i]);
            lists->addWidget(dynamic[i]);
         }
     }
     flayoutSaveas->addRow(spacingRow);
     flayoutSaveas->addRow(savetolist, lists);
     flayoutSaveas->setContentsMargins(0,50,0,50);

     saveaslayout = new QVBoxLayout;
     saveaslayout->addWidget(topborder);
     saveaslayout->addLayout(articletosave);
     saveaslayout->addWidget(bottomborder);
     //saveaslayout->addWidget(spacingRow);
     saveaslayout->addLayout(flayoutSaveas);
     //saveaslayout->addLayout(lists);
     saveaslayout->addWidget(newlist);
     saveaslayout->addWidget(save);
     saveaslayout->setContentsMargins(20,20,20,20);

    addtoWidget = new QWidget();
    addtoWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    addtoWidget->setLayout(saveaslayout);
    addtoWidget->setWindowTitle("Save to Favourites");
    addtoWidget->resize(510, 300);
    addtoWidget->show();

   connect(save, &QPushButton::clicked, this, &Display::saveHandler);
   connect(newlist, &QPushButton::clicked, this, &Display::newlistHandler8);

}

void Display::addtoFavouritesHandler9(){

     //article image and title
     QPixmap articleImg9(":/save9.jpg");
     QLabel *fav_imglabel = new QLabel();
     QLabel *fav_title = new QLabel();
     fav_title->setWordWrap(true);

     fav_imglabel->setPixmap(articleImg9);
     fav_imglabel->setMaximumWidth(210);
     fav_imglabel->setMinimumHeight(115);
     fav_title->setStyleSheet("QLabel { font-size: 20px; }");
     fav_title->setText(articles[8].m_title);
     fav_title->setMaximumWidth(300);
     fav_title->setMinimumHeight(115);
     QHBoxLayout *articletosave = new QHBoxLayout();
     articletosave->addWidget(fav_imglabel);
     articletosave->addWidget(fav_title);

     QFrame *topborder = new QFrame();
     topborder->setFrameShape(QFrame::HLine);
     topborder->setFrameShadow(QFrame::Sunken);
     topborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");
     QFrame *bottomborder = new QFrame();
     bottomborder->setFrameShape(QFrame::HLine);
     bottomborder->setFrameShadow(QFrame::Sunken);
     bottomborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");

    QLabel *spacingRow = new QLabel();
     saveasField = new QLineEdit();
     saveasField->setText(articles[8].m_title);
     QPushButton *save= new QPushButton("SAVE");
     save->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
     QPushButton *newlist= new QPushButton("+ Create New List");
     newlist->setStyleSheet("QPushButton { color: ##f0f0f0; background-color: #FFFFFF; font-size: 15px; }");

     QFormLayout *flayoutSaveas = new QFormLayout();
     QLabel *saveas = new QLabel("Save As:");
     saveas->setStyleSheet("QLabel {font-weight: bold;}");
     flayoutSaveas->addRow(saveas, saveasField);
     QLabel *savetolist = new QLabel("Save To List:");
     savetolist->setStyleSheet("QLabel {font-weight: bold;}");

     //checkboxes for lists
     lists = new QVBoxLayout();
     for(int i = 0;i < favlists[0]->count() && favlists[0][i] != ""; ++i)
     {
         if(favlists[0][i] != ""){
            dynamic[i] = new QCheckBox(favlists[0][i]);
            lists->addWidget(dynamic[i]);
         }
     }
     flayoutSaveas->addRow(spacingRow);
     flayoutSaveas->addRow(savetolist, lists);
     flayoutSaveas->setContentsMargins(0,50,0,50);

     saveaslayout = new QVBoxLayout;
     saveaslayout->addWidget(topborder);
     saveaslayout->addLayout(articletosave);
     saveaslayout->addWidget(bottomborder);
     //saveaslayout->addWidget(spacingRow);
     saveaslayout->addLayout(flayoutSaveas);
     //saveaslayout->addLayout(lists);
     saveaslayout->addWidget(newlist);
     saveaslayout->addWidget(save);
     saveaslayout->setContentsMargins(20,20,20,20);

    addtoWidget = new QWidget();
    addtoWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    addtoWidget->setLayout(saveaslayout);
    addtoWidget->setWindowTitle("Save to Favourites");
    addtoWidget->resize(510, 300);
    addtoWidget->show();

   connect(save, &QPushButton::clicked, this, &Display::saveHandler);
   connect(newlist, &QPushButton::clicked, this, &Display::newlistHandler9);
}


void Display::addtoFavouritesHandler10(){

     //article image and title
     QPixmap articleImg10(":/save10.jpg");
     QLabel *fav_imglabel = new QLabel();
     QLabel *fav_title = new QLabel();
     fav_title->setWordWrap(true);

     fav_imglabel->setPixmap(articleImg10);
     fav_imglabel->setMaximumWidth(210);
     fav_imglabel->setMinimumHeight(115);
     fav_title->setStyleSheet("QLabel { font-size: 20px; }");
     fav_title->setText(articles[9].m_title);
     fav_title->setMaximumWidth(300);
     fav_title->setMinimumHeight(115);
     QHBoxLayout *articletosave = new QHBoxLayout();
     articletosave->addWidget(fav_imglabel);
     articletosave->addWidget(fav_title);

     QFrame *topborder = new QFrame();
     topborder->setFrameShape(QFrame::HLine);
     topborder->setFrameShadow(QFrame::Sunken);
     topborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");
     QFrame *bottomborder = new QFrame();
     bottomborder->setFrameShape(QFrame::HLine);
     bottomborder->setFrameShadow(QFrame::Sunken);
     bottomborder->setStyleSheet("QFrame { border-top: 1px solid; color: black;}");

    QLabel *spacingRow = new QLabel();
     saveasField = new QLineEdit();
     saveasField->setText(articles[9].m_title);
     QPushButton *save= new QPushButton("SAVE");
     save->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");
     QPushButton *newlist= new QPushButton("+ Create New List");
     newlist->setStyleSheet("QPushButton { color: ##f0f0f0; background-color: #FFFFFF; font-size: 15px; }");

     QFormLayout *flayoutSaveas = new QFormLayout();
     QLabel *saveas = new QLabel("Save As:");
     saveas->setStyleSheet("QLabel {font-weight: bold;}");
     flayoutSaveas->addRow(saveas, saveasField);
     QLabel *savetolist = new QLabel("Save To List:");
     savetolist->setStyleSheet("QLabel {font-weight: bold;}");

     //checkboxes for lists
     lists = new QVBoxLayout();
     for(int i = 0;i < favlists[0]->count() && favlists[0][i] != ""; ++i)
     {
         if(favlists[0][i] != ""){
            dynamic[i] = new QCheckBox(favlists[0][i]);
            lists->addWidget(dynamic[i]);
         }
     }
     flayoutSaveas->addRow(spacingRow);
     flayoutSaveas->addRow(savetolist, lists);
     flayoutSaveas->setContentsMargins(0,50,0,50);

     saveaslayout = new QVBoxLayout;
     saveaslayout->addWidget(topborder);
     saveaslayout->addLayout(articletosave);
     saveaslayout->addWidget(bottomborder);
     //saveaslayout->addWidget(spacingRow);
     saveaslayout->addLayout(flayoutSaveas);
     //saveaslayout->addLayout(lists);
     saveaslayout->addWidget(newlist);
     saveaslayout->addWidget(save);
     saveaslayout->setContentsMargins(20,20,20,20);

    addtoWidget = new QWidget();
    addtoWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    addtoWidget->setLayout(saveaslayout);
    addtoWidget->setWindowTitle("Save to Favourites");
    addtoWidget->resize(510, 300);
    addtoWidget->show();

   connect(save, &QPushButton::clicked, this, &Display::saveHandler);
   connect(newlist, &QPushButton::clicked, this, &Display::newlistHandler10);

}

void Display::saveHandler(){

    //check which list was checked by user
             for(int i = 0;i < favlists[0]->count() && favlists[0][i] != ""; ++i)
             {
                 if(favlists[0][i] != ""){
                    if(dynamic[i]->isChecked()){
                        //iterate through row to check for next available spot to store article title in list
                        for(int j = 1;j < favlists[0]->count(); ++j)
                        {
                            if(favlists[j][i] == ""){
                            favlists[j][i] = saveasField->text();
                            break;
                        }
                      }
                    }
                 }
             }
       addtoWidget->hide();
}

void Display::newlistHandler1(){

    addtoWidget->hide();
    listnameField = new QLineEdit();
    QFormLayout *flayoutlistname = new QFormLayout();
    flayoutlistname->addRow("New Favourites List Name:", listnameField);
    QPushButton *create = new QPushButton("Create List");
    create->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");

    QVBoxLayout *newlist = new QVBoxLayout();
    newlist->addLayout(flayoutlistname);
    newlist->addWidget(create);

    newlistWidget = new QWidget();
    newlistWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    newlistWidget->setLayout(newlist);
    newlistWidget->setWindowTitle("Create New Favourites List");
    newlistWidget->resize(200, 100);
    newlistWidget->show();

    connect(create, &QPushButton::clicked, this, &Display::createlistHandler1);
}

void Display::newlistHandler2(){

    addtoWidget->hide();
    listnameField = new QLineEdit();
    QFormLayout *flayoutlistname = new QFormLayout();
    flayoutlistname->addRow("New Favourites List Name:", listnameField);
    QPushButton *create = new QPushButton("Create List");
    create->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");

    QVBoxLayout *newlist = new QVBoxLayout();
    newlist->addLayout(flayoutlistname);
    newlist->addWidget(create);

    newlistWidget = new QWidget();
    newlistWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    newlistWidget->setLayout(newlist);
    newlistWidget->setWindowTitle("Create New Favourites List");
    newlistWidget->resize(200, 100);
    newlistWidget->show();

    connect(create, &QPushButton::clicked, this, &Display::createlistHandler2);
}

void Display::newlistHandler3(){

    addtoWidget->hide();
    listnameField = new QLineEdit();
    QFormLayout *flayoutlistname = new QFormLayout();
    flayoutlistname->addRow("New Favourites List Name:", listnameField);
    QPushButton *create = new QPushButton("Create List");
    create->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");

    QVBoxLayout *newlist = new QVBoxLayout();
    newlist->addLayout(flayoutlistname);
    newlist->addWidget(create);

    newlistWidget = new QWidget();
    newlistWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    newlistWidget->setLayout(newlist);
    newlistWidget->setWindowTitle("Create New Favourites List");
    newlistWidget->resize(200, 100);
    newlistWidget->show();

    connect(create, &QPushButton::clicked, this, &Display::createlistHandler3);
}

void Display::newlistHandler4(){

    addtoWidget->hide();
    listnameField = new QLineEdit();
    QFormLayout *flayoutlistname = new QFormLayout();
    flayoutlistname->addRow("New Favourites List Name:", listnameField);
    QPushButton *create = new QPushButton("Create List");
    create->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");

    QVBoxLayout *newlist = new QVBoxLayout();
    newlist->addLayout(flayoutlistname);
    newlist->addWidget(create);

    newlistWidget = new QWidget();
    newlistWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    newlistWidget->setLayout(newlist);
    newlistWidget->setWindowTitle("Create New Favourites List");
    newlistWidget->resize(200, 100);
    newlistWidget->show();

    connect(create, &QPushButton::clicked, this, &Display::createlistHandler4);
}

void Display::newlistHandler5(){

    addtoWidget->hide();
    listnameField = new QLineEdit();
    QFormLayout *flayoutlistname = new QFormLayout();
    flayoutlistname->addRow("New Favourites List Name:", listnameField);
    QPushButton *create = new QPushButton("Create List");
    create->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");

    QVBoxLayout *newlist = new QVBoxLayout();
    newlist->addLayout(flayoutlistname);
    newlist->addWidget(create);

    newlistWidget = new QWidget();
    newlistWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    newlistWidget->setLayout(newlist);
    newlistWidget->setWindowTitle("Create New Favourites List");
    newlistWidget->resize(200, 100);
    newlistWidget->show();

    connect(create, &QPushButton::clicked, this, &Display::createlistHandler5);
}

void Display::newlistHandler6(){

    addtoWidget->hide();
    listnameField = new QLineEdit();
    QFormLayout *flayoutlistname = new QFormLayout();
    flayoutlistname->addRow("New Favourites List Name:", listnameField);
    QPushButton *create = new QPushButton("Create List");
    create->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");

    QVBoxLayout *newlist = new QVBoxLayout();
    newlist->addLayout(flayoutlistname);
    newlist->addWidget(create);

    newlistWidget = new QWidget();
    newlistWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    newlistWidget->setLayout(newlist);
    newlistWidget->setWindowTitle("Create New Favourites List");
    newlistWidget->resize(200, 100);
    newlistWidget->show();

    connect(create, &QPushButton::clicked, this, &Display::createlistHandler6);
}

void Display::newlistHandler7(){

    addtoWidget->hide();
    listnameField = new QLineEdit();
    QFormLayout *flayoutlistname = new QFormLayout();
    flayoutlistname->addRow("New Favourites List Name:", listnameField);
    QPushButton *create = new QPushButton("Create List");
    create->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");

    QVBoxLayout *newlist = new QVBoxLayout();
    newlist->addLayout(flayoutlistname);
    newlist->addWidget(create);

    newlistWidget = new QWidget();
    newlistWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    newlistWidget->setLayout(newlist);
    newlistWidget->setWindowTitle("Create New Favourites List");
    newlistWidget->resize(200, 100);
    newlistWidget->show();

    connect(create, &QPushButton::clicked, this, &Display::createlistHandler7);
}

void Display::newlistHandler8(){

    addtoWidget->hide();
    listnameField = new QLineEdit();
    QFormLayout *flayoutlistname = new QFormLayout();
    flayoutlistname->addRow("New Favourites List Name:", listnameField);
    QPushButton *create = new QPushButton("Create List");
    create->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");

    QVBoxLayout *newlist = new QVBoxLayout();
    newlist->addLayout(flayoutlistname);
    newlist->addWidget(create);

    newlistWidget = new QWidget();
    newlistWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    newlistWidget->setLayout(newlist);
    newlistWidget->setWindowTitle("Create New Favourites List");
    newlistWidget->resize(200, 100);
    newlistWidget->show();

    connect(create, &QPushButton::clicked, this, &Display::createlistHandler8);
}

void Display::newlistHandler9(){

    addtoWidget->hide();
    listnameField = new QLineEdit();
    QFormLayout *flayoutlistname = new QFormLayout();
    flayoutlistname->addRow("New Favourites List Name:", listnameField);
    QPushButton *create = new QPushButton("Create List");
    create->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");

    QVBoxLayout *newlist = new QVBoxLayout();
    newlist->addLayout(flayoutlistname);
    newlist->addWidget(create);

    newlistWidget = new QWidget();
    newlistWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    newlistWidget->setLayout(newlist);
    newlistWidget->setWindowTitle("Create New Favourites List");
    newlistWidget->resize(200, 100);
    newlistWidget->show();

    connect(create, &QPushButton::clicked, this, &Display::createlistHandler9);
}

void Display::newlistHandler10(){

    addtoWidget->hide();
    listnameField = new QLineEdit();
    QFormLayout *flayoutlistname = new QFormLayout();
    flayoutlistname->addRow("New Favourites List Name:", listnameField);
    QPushButton *create = new QPushButton("Create List");
    create->setStyleSheet("QPushButton { background-color: #1F4A8A; color: #FFFFFF; font-size: 15px; padding: .5em; border-radius: 7px;}");

    QVBoxLayout *newlist = new QVBoxLayout();
    newlist->addLayout(flayoutlistname);
    newlist->addWidget(create);

    newlistWidget = new QWidget();
    newlistWidget->setStyleSheet("QWidget{background-color: #FFFFFF; }");
    newlistWidget->setLayout(newlist);
    newlistWidget->setWindowTitle("Create New Favourites List");
    newlistWidget->resize(200, 100);
    newlistWidget->show();

    connect(create, &QPushButton::clicked, this, &Display::createlistHandler10);
}

void Display::createlistHandler1(){

    for(int i = 0;i < favlists[0]->count(); ++i)
    {
        if(favlists[0][i] == ""){
           favlists[0][i] = listnameField->text();
           break;
        }
    }
    newlistWidget->hide();
    addtoFavouritesHandler1();
}

void Display::createlistHandler2(){

    for(int i = 0;i < favlists[0]->count(); ++i)
    {
        if(favlists[0][i] == ""){
           favlists[0][i] = listnameField->text();
           break;
        }
    }
    newlistWidget->hide();
    addtoFavouritesHandler2();
}

void Display::createlistHandler3(){

    for(int i = 0;i < favlists[0]->count(); ++i)
    {
        if(favlists[0][i] == ""){
           favlists[0][i] = listnameField->text();
           break;
        }
    }
    newlistWidget->hide();
    addtoFavouritesHandler3();
}

void Display::createlistHandler4(){

    for(int i = 0;i < favlists[0]->count(); ++i)
    {
        if(favlists[0][i] == ""){
           favlists[0][i] = listnameField->text();
           break;
        }
    }
    newlistWidget->hide();
    addtoFavouritesHandler4();
}

void Display::createlistHandler5(){

    for(int i = 0;i < favlists[0]->count(); ++i)
    {
        if(favlists[0][i] == ""){
           favlists[0][i] = listnameField->text();
           break;
        }
    }
    newlistWidget->hide();
    addtoFavouritesHandler5();
}

void Display::createlistHandler6(){

    for(int i = 0;i < favlists[0]->count(); ++i)
    {
        if(favlists[0][i] == ""){
           favlists[0][i] = listnameField->text();
           break;
        }
    }
    newlistWidget->hide();
    addtoFavouritesHandler6();
}

void Display::createlistHandler7(){

    for(int i = 0;i < favlists[0]->count(); ++i)
    {
        if(favlists[0][i] == ""){
           favlists[0][i] = listnameField->text();
           break;
        }
    }
    newlistWidget->hide();
    addtoFavouritesHandler7();
}

void Display::createlistHandler8(){

    for(int i = 0;i < favlists[0]->count(); ++i)
    {
        if(favlists[0][i] == ""){
           favlists[0][i] = listnameField->text();
           break;
        }
    }
    newlistWidget->hide();
    addtoFavouritesHandler8();
}

void Display::createlistHandler9(){

    for(int i = 0;i < favlists[0]->count(); ++i)
    {
        if(favlists[0][i] == ""){
           favlists[0][i] = listnameField->text();
           break;
        }
    }
    newlistWidget->hide();
    addtoFavouritesHandler9();
}

void Display::createlistHandler10(){

    for(int i = 0;i < favlists[0]->count(); ++i)
    {
        if(favlists[0][i] == ""){
           favlists[0][i] = listnameField->text();
           break;
        }
    }
    newlistWidget->hide();
    addtoFavouritesHandler10();
}

void Display::searchHandler(){

    //layout
    QVBoxLayout *searchlayout = new QVBoxLayout();
    searchlayout->setSpacing(0);
    searchlayout->setMargin(0);
    QLabel *results = new QLabel("Results:");
    results->setStyleSheet("QLabel{font-size: 20px; font-weight: bold;}");
    searchlayout->addWidget(results, 0, Qt::AlignTop);
    //searchlayout->addWidget(results);
   // searchlayout->setAlignment(Qt::AlignCenter);
    QPushButton *title0 = new QPushButton();
    title0->setStyleSheet("QPushButton{border: none;}");
    title0->setCursor(Qt::PointingHandCursor);
    QPushButton *title1 = new QPushButton();
    title1->setStyleSheet("QPushButton{border: none;}");
    title1->setCursor(Qt::PointingHandCursor);
    QPushButton *title2 = new QPushButton();
    title2->setStyleSheet("QPushButton{border: none;}");
    title2->setCursor(Qt::PointingHandCursor);
    QPushButton *title3 = new QPushButton();
    title3->setStyleSheet("QPushButton{border: none;}");
    title3->setCursor(Qt::PointingHandCursor);
    QPushButton *title4 = new QPushButton();
    title4->setStyleSheet("QPushButton{border: none;}");
    title4->setCursor(Qt::PointingHandCursor);
    QPushButton *title5 = new QPushButton();
    title5->setStyleSheet("QPushButton{border: none;}");
    title5->setCursor(Qt::PointingHandCursor);
    QPushButton *title6 = new QPushButton();
    title6->setStyleSheet("QPushButton{border: none;}");
    title6->setCursor(Qt::PointingHandCursor);
    QPushButton *title7 = new QPushButton();
    title7->setStyleSheet("QPushButton{border: none;}");
    title7->setCursor(Qt::PointingHandCursor);
    QPushButton *title8 = new QPushButton();
    title8->setStyleSheet("QPushButton{border: none;}");
    title8->setCursor(Qt::PointingHandCursor);
    QPushButton *title9 = new QPushButton();
    title9->setStyleSheet("QPushButton{border: none;}");
    title9->setCursor(Qt::PointingHandCursor);

    if(searchbar->text() == "sports"){
        title1->setStyleSheet("QPushButton {border-image:url(:/results2.jpg);}");
        title1->setMaximumWidth(550);
        title1->setMinimumHeight(140);
        searchlayout->addWidget(title1, 0, Qt::AlignTop);
        searchlayout->setContentsMargins(700,100,0,100);
    }
    if(searchbar->text() == "covid-19"){
        title2->setStyleSheet("QPushButton {border-image:url(:/results3.jpg);}");
        title2->setMaximumWidth(550);
        title2->setMinimumHeight(140);
        searchlayout->addWidget(title2);

        title4->setStyleSheet("QPushButton {border-image:url(:/results5.jpg);}");
        title4->setMaximumWidth(550);
        title4->setMinimumHeight(140);
        searchlayout->addWidget(title4);

        title5->setStyleSheet("QPushButton {border-image:url(:/results6.jpg);}");
        title5->setMaximumWidth(550);
        title5->setMinimumHeight(140);
        searchlayout->addWidget(title5);

        title8->setStyleSheet("QPushButton {border-image:url(:/results9.jpg);}");
        title8->setMaximumWidth(550);
        title8->setMinimumHeight(140);
        searchlayout->addWidget(title8);
        searchlayout->setContentsMargins(700,100,0,100);
    }
    if(searchbar->text() == "politics" || searchbar->text() == "trudeau"){
        title0->setStyleSheet("QPushButton {border-image:url(:/results1.jpg);}");
        title0->setMaximumWidth(550);
        title0->setMinimumHeight(140);
        searchlayout->addWidget(title0);

        title2->setStyleSheet("QPushButton {border-image:url(:/results3.jpg);}");
        title2->setMaximumWidth(550);
        title2->setMinimumHeight(140);
        searchlayout->addWidget(title2);

        searchlayout->setContentsMargins(700,100,0,100);

    }
    if(searchbar->text() == "military"){
        title9->setStyleSheet("QPushButton {border-image:url(:/results10.jpg);}");
        title9->setMaximumWidth(550);
        title9->setMinimumHeight(140);
        searchlayout->addWidget(title9);
        searchlayout->setContentsMargins(700,100,0,100);
    }
    if(searchbar->text() == "canada" || searchbar->text() == "local" || searchbar->text() == "current"){
        title0->setStyleSheet("QPushButton {border-image:url(:/results1.jpg);}");
        title0->setMaximumWidth(550);
        title0->setMinimumHeight(140);
        searchlayout->addWidget(title0);

        title1->setStyleSheet("QPushButton {border-image:url(:/results2.jpg);}");
        title1->setMaximumWidth(550);
        title1->setMinimumHeight(140);
        searchlayout->addWidget(title1);

        title2->setStyleSheet("QPushButton {border-image:url(:/results3.jpg);}");
        title2->setMaximumWidth(550);
        title2->setMinimumHeight(140);
        searchlayout->addWidget(title2);

        title3->setStyleSheet("QPushButton {border-image:url(:/results4.jpg);}");
        title3->setMaximumWidth(550);
        title3->setMinimumHeight(140);
        searchlayout->addWidget(title3);

        title4->setStyleSheet("QPushButton {border-image:url(:/results5.jpg);}");
        title4->setMaximumWidth(550);
        title4->setMinimumHeight(140);
        searchlayout->addWidget(title4);

        title5->setStyleSheet("QPushButton {border-image:url(:/results6.jpg);}");
        title5->setMaximumWidth(550);
        title5->setMinimumHeight(140);
        searchlayout->addWidget(title5);

        title6->setStyleSheet("QPushButton {border-image:url(:/results7.jpg);}");
        title6->setMaximumWidth(550);
        title6->setMinimumHeight(140);
        searchlayout->addWidget(title6);

        title7->setStyleSheet("QPushButton {border-image:url(:/results8.jpg);}");
        title7->setMaximumWidth(550);
        title7->setMinimumHeight(140);
        searchlayout->addWidget(title7);

        title8->setStyleSheet("QPushButton {border-image:url(:/results9.jpg);}");
        title8->setMaximumWidth(550);
        title8->setMinimumHeight(140);
        searchlayout->addWidget(title8);

        title9->setStyleSheet("QPushButton {border-image:url(:/results10.jpg);}");
        title9->setMaximumWidth(550);
        title9->setMinimumHeight(140);
        searchlayout->addWidget(title9);
        searchlayout->setContentsMargins(700,100,0,100);
    }
    if(searchbar->text() != "sports" && searchbar->text() != "covid-19" && searchbar->text() != "politics" && searchbar->text() != "trudeau" &&
            searchbar->text() != "military" && searchbar->text() != "canada" && searchbar->text() != "local" && searchbar->text() != "current"){
        QString message = "Sorry, Your search '" + searchbar->text() + "' did not match any articles.";
        title0->setText(message);
         title0->setStyleSheet("QPushButton{border: none; font-size: 18px;}");
        searchlayout->addWidget(title0);
        results->setContentsMargins(0,0,0,50);
        searchlayout->setAlignment(Qt::AlignCenter);
    }


    //set page layout with scrollbar
    QWidget *searchwidget = new QWidget();
    searchwidget->setStyleSheet("QWidget {background-color: white;}");
    searchwidget->setLayout(searchlayout);

    searchPageWidget->setWidgetResizable(true);
    searchPageWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    searchPageWidget->setWidget(searchwidget);

  stackedWidget->setCurrentWidget(searchPageWidget);
  setCentralWidget(stackedWidget);

  //to display articles
  connect(title0, &QPushButton::clicked,
            this, &Display::displayArticle1Handler);
   connect(title1, &QPushButton::clicked,
            this, &Display::displayArticle2Handler);
  connect(title2, &QPushButton::clicked,
            this, &Display::displayArticle3Handler);
  connect(title3, &QPushButton::clicked,
            this, &Display::displayArticle4Handler);
 connect(title4, &QPushButton::clicked,
            this, &Display::displayArticle5Handler);
  connect(title5, &QPushButton::clicked,
            this, &Display::displayArticle6Handler);
  connect(title6, &QPushButton::clicked,
            this, &Display::displayArticle7Handler);
 connect(title7, &QPushButton::clicked,
            this, &Display::displayArticle8Handler);
  connect(title8, &QPushButton::clicked,
            this, &Display::displayArticle9Handler);
  connect(title9, &QPushButton::clicked,
            this, &Display::displayArticle10Handler);

}

Display::~Display(){} //destructor

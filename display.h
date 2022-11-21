#ifndef DISPLAY_H
#define DISPLAY_H


#include <QMainWindow>
#include <QApplication>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QTextBrowser>
#include <QString>
#include <QScrollArea>
#include <QFrame>
#include <QToolBar>
#include <QStackedWidget>
#include <QCheckBox>

class Display : public QMainWindow {


  Q_OBJECT


    struct Article {

           QString m_title;
           QString m_text;
           QPixmap *img;

       };
    struct User{
        QString m_username;
        QString m_password;
        QString m_firstName;
        QString m_lastName;
        QString m_email;
        QString m_creditCard;
        QPixmap *m_profileImg;
    };


  public:

    Display(QWidget *parent = nullptr);
    ~Display();

private slots:
    void topnextHandler();
    void topprevHandler();
    void feednextHandler();
    void feedprevHandler();
    void backpageHandler();
    void displayArticle1Handler();
    void displayArticle2Handler();
    void displayArticle3Handler();
    void displayArticle4Handler();
    void displayArticle5Handler();
    //void displayArticle5topHandler();
    void displayArticle6Handler();
    void displayArticle7Handler();
    void displayArticle8Handler();
    void displayArticle9Handler();
    void displayArticle10Handler();

    void favouritesHandler();
    void settingsHandler();
    void userHandler();
    //void likeHandler();
    //void shareHandler();
    void addtoFavouritesHandler1();
    void addtoFavouritesHandler2();
    void addtoFavouritesHandler3();
    void addtoFavouritesHandler4();
    void addtoFavouritesHandler5();
    void addtoFavouritesHandler6();
    void addtoFavouritesHandler7();
    void addtoFavouritesHandler8();
    void addtoFavouritesHandler9();
    void addtoFavouritesHandler10();
    void createlistHandler();

    void newwwHandler();


    void signoutHandler();
    void quitHandler();
    void signinHandler();
    void endHandler();

    void likedHandler1a();
    void likedHandler2a();
    void likedHandler3a();
    void likedHandler4a();
    void likedHandler5a();
    void likedHandler6a();
    void likedHandler7a();
    void likedHandler8a();
    void likedHandler1b();
    void likedHandler2b();
    void likedHandler3b();
    void likedHandler4b();
    void likedHandler5b();
    void likedHandler6b();
    void likedHandler7b();
    void likedHandler8b();
    void likedHandler1c();
    void likedHandler2c();
    void likedHandler3c();
    void likedHandler4c();
    void likedHandler5c();
    void likedHandler6c();
    void likedHandler7c();
    void likedHandler8c();
    void likedHandler1d();
    void likedHandler2d();
    void likedHandler3d();
    void likedHandler4d();
    void likedHandler5d();
    void likedHandler6d();
    void likedHandler7d();
    void likedHandler8d();

    //share articles
    void shareHandler1();
    void shareHandler2();
    void shareHandler3();
    void shareHandler4();
    void shareHandler5();
    void shareHandler6();
    void shareHandler7();
    void shareHandler8();
    void shareHandler9();
    void shareHandler10();

    void facebookHandler();
    void twitterHandler();
    void emailHandler();
    void linkedinHandler();
    void tumblrHandler();
    void copyHandler();
   // void plusHandler();
    void saveHandler();
    void newlistHandler1();
    void newlistHandler2();
    void newlistHandler3();
    void newlistHandler4();
    void newlistHandler5();
    void newlistHandler6();
    void newlistHandler7();
    void newlistHandler8();
    void newlistHandler9();
    void newlistHandler10();

    void createlistHandler1();
    void createlistHandler2();
    void createlistHandler3();
    void createlistHandler4();
    void createlistHandler5();
    void createlistHandler6();
    void createlistHandler7();
    void createlistHandler8();
    void createlistHandler9();
    void createlistHandler10();

    void searchHandler();

    void likedHandler1();
    void likedHandler2();
    void likedHandler3();
    void likedHandler4();
    void likedHandler5();
    void likedHandler6();
    void likedHandler7();
    void likedHandler8();
    void likedHandler9();
    void likedHandler10();

    void subscribeHandler1();
    void subscribeHandler2();
    void subscribeHandler3();
    void subscribeHandler4();
    void subscribeHandler5();
    void subscribeHandler6();
    void subscribeHandler7();
    void subscribeHandler8();
    void subscribeHandler9();
    void subscribeHandler10();

    void loadCommentsHandler1();
    void loadCommentsHandler2();
    void loadCommentsHandler3();
    void loadCommentsHandler4();
    void loadCommentsHandler5();
    void loadCommentsHandler6();
    void loadCommentsHandler7();
    void loadCommentsHandler8();
    void loadCommentsHandler9();
    void loadCommentsHandler10();

    void addCommentHandler1();
    void addCommentHandler2();
    void addCommentHandler3();
    void addCommentHandler4();
    void addCommentHandler5();
    void addCommentHandler6();
    void addCommentHandler7();
    void addCommentHandler8();
    void addCommentHandler9();
    void addCommentHandler10();

    void savesettingsHandler();
    void deleteHandler();

private:
     int *status = 0;
    //set main page article thumbnails layouts
    QVBoxLayout *articlelayout1a;
    QVBoxLayout *articlelayout1b;
    QVBoxLayout *articlelayout1c;
    QVBoxLayout *articlelayout1d;
    QVBoxLayout *articlelayout2a;
    QVBoxLayout *articlelayout2b;
    QVBoxLayout *articlelayout2c;
    QVBoxLayout *articlelayout2d;
    QVBoxLayout *articlelayout3a;
    QVBoxLayout *articlelayout3b;
    QVBoxLayout *articlelayout3c;
    QVBoxLayout *articlelayout3d;
    QVBoxLayout *articlelayout4a;
    QVBoxLayout *articlelayout4b;
    QVBoxLayout *articlelayout4c;
    QVBoxLayout *articlelayout4d;
    QVBoxLayout *articlelayout5a;
    QVBoxLayout *articlelayout5b;
    QVBoxLayout *articlelayout5c;
    QVBoxLayout *articlelayout5d;
    QVBoxLayout *articlelayout6a;
    QVBoxLayout *articlelayout6b;
    QVBoxLayout *articlelayout6c;
    QVBoxLayout *articlelayout6d;
    QVBoxLayout *articlelayout7a;
    QVBoxLayout *articlelayout7b;
    QVBoxLayout *articlelayout7c;
    QVBoxLayout *articlelayout7d;
    QVBoxLayout *articlelayout8a;
    QVBoxLayout *articlelayout8b;
    QVBoxLayout *articlelayout8c;
    QVBoxLayout *articlelayout8d;

    //set main page horizontal article icon layouts
    QHBoxLayout *iconlayout1a;
    QHBoxLayout *iconlayout1b;
    QHBoxLayout *iconlayout1c;
    QHBoxLayout *iconlayout1d;
    QHBoxLayout *iconlayout2a;
    QHBoxLayout *iconlayout2b;
    QHBoxLayout *iconlayout2c;
    QHBoxLayout *iconlayout2d;
    QHBoxLayout *iconlayout3a;
    QHBoxLayout *iconlayout3b;
    QHBoxLayout *iconlayout3c;
    QHBoxLayout *iconlayout3d;
    QHBoxLayout *iconlayout4a;
    QHBoxLayout *iconlayout4b;
    QHBoxLayout *iconlayout4c;
    QHBoxLayout *iconlayout4d;
    QHBoxLayout *iconlayout5a;
    QHBoxLayout *iconlayout5b;
    QHBoxLayout *iconlayout5c;
    QHBoxLayout *iconlayout5d;
    QHBoxLayout *iconlayout6a;
    QHBoxLayout *iconlayout6b;
    QHBoxLayout *iconlayout6c;
    QHBoxLayout *iconlayout6d;
    QHBoxLayout *iconlayout7a;
    QHBoxLayout *iconlayout7b;
    QHBoxLayout *iconlayout7c;
    QHBoxLayout *iconlayout7d;
    QHBoxLayout *iconlayout8a;
    QHBoxLayout *iconlayout8b;
    QHBoxLayout *iconlayout8c;
    QHBoxLayout *iconlayout8d;

    //heart buttons - on article thumbnails
    QPushButton *heart1a;
    QPushButton *heart1b;
    QPushButton *heart1c;
    QPushButton *heart1d;
    QPushButton *heart2a;
    QPushButton *heart2b;
    QPushButton *heart2c;
    QPushButton *heart2d;
    QPushButton *heart3a;
    QPushButton *heart3b;
    QPushButton *heart3c;
    QPushButton *heart3d;
    QPushButton *heart4a;
    QPushButton *heart4b;
    QPushButton *heart4c;
    QPushButton *heart4d;
    QPushButton *heart5a;
    QPushButton *heart5b;
    QPushButton *heart5c;
    QPushButton *heart5d;
    QPushButton *heart6a;
    QPushButton *heart6b;
    QPushButton *heart6c;
    QPushButton *heart6d;
    QPushButton *heart7a;
    QPushButton *heart7b;
    QPushButton *heart7c;
    QPushButton *heart7d;
    QPushButton *heart8a;
    QPushButton *heart8b;
    QPushButton *heart8c;
    QPushButton *heart8d;

    //add buttons - on article thumbnails
    QPushButton *plus1a;
    QPushButton *plus1b;
    QPushButton *plus1c;
    QPushButton *plus1d;
    QPushButton *plus2a;
    QPushButton *plus2b;
    QPushButton *plus2c;
    QPushButton *plus2d;
    QPushButton *plus3a;
    QPushButton *plus3b;
    QPushButton *plus3c;
    QPushButton *plus3d;
    QPushButton *plus4a;
    QPushButton *plus4b;
    QPushButton *plus4c;
    QPushButton *plus4d;
    QPushButton *plus5a;
    QPushButton *plus5b;
    QPushButton *plus5c;
    QPushButton *plus5d;
    QPushButton *plus6a;
    QPushButton *plus6b;
    QPushButton *plus6c;
    QPushButton *plus6d;
    QPushButton *plus7a;
    QPushButton *plus7b;
    QPushButton *plus7c;
    QPushButton *plus7d;
    QPushButton *plus8a;
    QPushButton *plus8b;
    QPushButton *plus8c;
    QPushButton *plus8d;

    //share buttons - on article thumbnails
    QPushButton *share1tha;
    QPushButton *share1thb;
    QPushButton *share1thc;
    QPushButton *share1thd;
    QPushButton *share2tha;
    QPushButton *share2thb;
    QPushButton *share2thc;
    QPushButton *share2thd;
    QPushButton *share3tha;
    QPushButton *share3thb;
    QPushButton *share3thc;
    QPushButton *share3thd;
    QPushButton *share4tha;
    QPushButton *share4thb;
    QPushButton *share4thc;
    QPushButton *share4thd;
    QPushButton *share5tha;
    QPushButton *share5thb;
    QPushButton *share5thc;
    QPushButton *share5thd;
    QPushButton *share6tha;
    QPushButton *share6thb;
    QPushButton *share6thc;
    QPushButton *share6thd;
    QPushButton *share7tha;
    QPushButton *share7thb;
    QPushButton *share7thc;
    QPushButton *share7thd;
    QPushButton *share8tha;
    QPushButton *share8thb;
    QPushButton *share8thc;
    QPushButton *share8thd;

    //spaces
    QLabel *spacinga;
    QLabel *spacingb;
    QLabel *spacingc;
    QLabel *spacingd;
    QLabel *spacing2a;
    QLabel *spacing2b;
    QLabel *spacing2c;
    QLabel *spacing2d;
    QLabel *spacing3a;
    QLabel *spacing3b;
    QLabel *spacing3c;
    QLabel *spacing3d;
    QLabel *spacing4a;
    QLabel *spacing4b;
    QLabel *spacing4c;
    QLabel *spacing4d;
    QLabel *spacing5a;
    QLabel *spacing5b;
    QLabel *spacing5c;
    QLabel *spacing5d;
    QLabel *spacing6a;
    QLabel *spacing6b;
    QLabel *spacing6c;
    QLabel *spacing6d;
    QLabel *spacing7a;
    QLabel *spacing7b;
    QLabel *spacing7c;
    QLabel *spacing7d;
    QLabel *spacing8a;
    QLabel *spacing8b;
    QLabel *spacing8c;
    QLabel *spacing8d;
    QLabel *spacingFeeds;
    QLabel *spacingFeeds2;
    QLabel *spacingFeeds3;

    //set pages
    QScrollArea *mainPageWidget;
    QScrollArea *articlePageWidget1;
    QScrollArea *articlePageWidget2;
    QScrollArea *articlePageWidget3;
    QScrollArea *articlePageWidget4;
    QScrollArea *articlePageWidget5;
    QScrollArea *articlePageWidget6;
    QScrollArea *articlePageWidget7;
    QScrollArea *articlePageWidget8;
    QScrollArea *articlePageWidget9;
    QScrollArea *articlePageWidget10;
    QScrollArea *favouritesPageWidget;
    QScrollArea *settingsPageWidget;
    QScrollArea *signinPageWidget;
    QScrollArea *searchPageWidget;
    QStackedWidget *stackedWidget;
    QStackedWidget *stackedTopnews;
    QStackedWidget *stackedFeed1;
    QStackedWidget *stackedFeed2;
    QStackedWidget *stackedFeed3;
    QStackedWidget *stackedFeed4;

    //set page layouts
    QVBoxLayout *vlayout;
    QVBoxLayout *vlayout1;
    QVBoxLayout *vlayout2;
    QVBoxLayout *vlayout3;
    QVBoxLayout *vlayout4;
    QVBoxLayout *vlayout5;
    QVBoxLayout *vlayout6;
    QVBoxLayout *vlayout7;
    QVBoxLayout *vlayout8;
    QVBoxLayout *vlayout9;
    QVBoxLayout *vlayout10;

    QLabel *topnewslabel;
    QLabel *myfeedlabel;
    QVBoxLayout *mainlayout;
    QVBoxLayout *favlayout;
    QWidget *mainwidget;
    QAction *myFeed;
    QLineEdit *searchbar;
    QHBoxLayout *feedlayout;
    QHBoxLayout *topNewslayout;
    QVBoxLayout *signinlayout;
    QVBoxLayout *userlayout;
    QVBoxLayout *settingslayout;
    QVBoxLayout *sharelayout;
    QVBoxLayout *saveaslayout;

    //thumbnail buttons on main screen view
    QPushButton *article1a;
    QPushButton *article1b;
    QPushButton *article1c;
    QPushButton *article1d;
    QPushButton *article2a;
    QPushButton *article2b;
    QPushButton *article2c;
    QPushButton *article2d;
    QPushButton *article3a;
    QPushButton *article3b;
    QPushButton *article3c;
    QPushButton *article3d;
    QPushButton *article4a;
    QPushButton *article4b;
    QPushButton *article4c;
    QPushButton *article4d;
    QPushButton *article5a;
    QPushButton *article5b;
    QPushButton *article5c;
    QPushButton *article5d;
    QPushButton *article6a;
    QPushButton *article6b;
    QPushButton *article6c;
    QPushButton *article6d;
    QPushButton *article7a;
    QPushButton *article7b;
    QPushButton *article7c;
    QPushButton *article7d;
    QPushButton *article8a;
    QPushButton *article8b;
    QPushButton *article8c;
    QPushButton *article8d;
    QPushButton *article9;
    QPushButton *article10;
    QPushButton *article5top;

    QPushButton *rightArrow;
    QPushButton *leftArrow;
    QPushButton *rightArrow2;
    QPushButton *leftArrow2;

    QToolBar *toolbar;
    QToolBar *toolbar2;


    //from in lab
      QWidget *central;
      QLabel *labelArticleRange;
      QPushButton *submitBut;
      QScrollArea *scroller;

      QPixmap *img[10];
      Article articles[10];
      QString links[10];
      QString favlists[20][20];
      QCheckBox *dynamic[20];
      QLabel *favlisticons[20];
      QLabel *favlisted[20];
      QPushButton *favtitles[20];
      int topStories[3];
      QLabel *thumbnail_label;

      QLabel *title_label;
      QLabel *title_label2;
      QLabel *title_label3;
      QLabel *title_label4;
      QLabel *title_label5;
      QLabel *title_label6;
      QLabel *title_label7;
      QLabel *title_label8;
      QLabel *title_label9;
      QLabel *title_label10;


      QLabel *img_label;
      QLabel *img_label2;
      QLabel *img_label3;
      QLabel *img_label4;
      QLabel *img_label5;
      QLabel *img_label6;
      QLabel *img_label7;
      QLabel *img_label8;
      QLabel *img_label9;
      QLabel *img_label10;

      QLabel *text_label;
      QLabel *text_label2;
      QLabel *text_label3;
      QLabel *text_label4;
      QLabel *text_label5;
      QLabel *text_label6;
      QLabel *text_label7;
      QLabel *text_label8;
      QLabel *text_label9;
      QLabel *text_label10;

      QFrame *line;
      QFrame *line2;
      QFrame *line3;
      QFrame *line4;
      QFrame *line5;
      QFrame *line6;
      QFrame *line7;
      QFrame *line8;
      QFrame *line9;
      QFrame *line10;


      QLabel *spacingRow;
      QLabel *spacingRow2;
      QLabel *spacingRow3;
      QLabel *spacingRow4;
      QLabel *spacingRow5;
      QLabel *spacingRow6;
      QLabel *spacingRow7;
      QLabel *spacingRow8;
      QLabel *spacingRow9;
      QLabel *spacingRow10;
      QLabel *spacingRow11;
      QLabel *spacingRow12;
      QLabel *spacingRow13;
      QLabel *spacingRow14;
      QLabel *spacingRow15;
      QLabel *spacingRow16;
      QLabel *spacingRow17;
      QLabel *spacingRow18;
      QLabel *spacingRow19;
      QLabel *spacingRow20;

      QPushButton *like;
      QPushButton *like2;
      QPushButton *like3;
      QPushButton *like4;
      QPushButton *like5;
      QPushButton *like6;
      QPushButton *like7;
      QPushButton *like8;
      QPushButton *like9;
      QPushButton *like10;

      QPushButton *share;
      QPushButton *share2;
      QPushButton *share3;
      QPushButton *share4;
      QPushButton *share5;
      QPushButton *share6;
      QPushButton *share7;
      QPushButton *share8;
      QPushButton *share9;
      QPushButton *share10;

      QPushButton *addToFavourites;
      QPushButton *addToFavourites2;
      QPushButton *addToFavourites3;
      QPushButton *addToFavourites4;
      QPushButton *addToFavourites5;
      QPushButton *addToFavourites6;
      QPushButton *addToFavourites7;
      QPushButton *addToFavourites8;
      QPushButton *addToFavourites9;
      QPushButton *addToFavourites10;

      QPushButton *subscribe;
      QPushButton *subscribe2;
      QPushButton *subscribe3;
      QPushButton *subscribe4;
      QPushButton *subscribe5;
      QPushButton *subscribe6;
      QPushButton *subscribe7;
      QPushButton *subscribe8;
      QPushButton *subscribe9;
      QPushButton *subscribe10;

      QLineEdit *addComment;
      QLineEdit *addComment2;
      QLineEdit *addComment3;
      QLineEdit *addComment4;
      QLineEdit *addComment5;
      QLineEdit *addComment6;
      QLineEdit *addComment7;
      QLineEdit *addComment8;
      QLineEdit *addComment9;
      QLineEdit *addComment10;


      QPushButton *loadComments;
      QPushButton *loadComments2;
      QPushButton *loadComments3;
      QPushButton *loadComments4;
      QPushButton *loadComments5;
      QPushButton *loadComments6;
      QPushButton *loadComments7;
      QPushButton *loadComments8;
      QPushButton *loadComments9;
      QPushButton *loadComments10;

      QWidget *user;
      QWidget *signinWidget;
      QWidget *shareWidget;
      QWidget *addtoWidget;
      QWidget *newlistWidget;
      QLineEdit *link;
      QLineEdit *listnameField;
      QLineEdit *saveasField;
      QVBoxLayout *lists; //checkboxes for favourites lists in the add to favourites widget
      QLineEdit *usernameField;
      QLineEdit *passwordField;
      User actor;
      QLabel *message;
      QLineEdit *firstnameField;
      QLineEdit *lastnameField;
      QLineEdit *unField;
      QLineEdit *passField;
      QLineEdit *emailField;
      QLineEdit *ccField;
      QPushButton *savesettings;
       QLineEdit *listnameFieldc;

};


#endif // TOOLBAR_H

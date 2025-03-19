#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QNetworkProxy>
#include <QLabel>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QComboBox>
#include <QStyle>
#include <QCursor>

class BrowserWindow : public QWidget {
    Q_OBJECT

public:
    BrowserWindow(QWidget *parent = nullptr) : QWidget(parent), incognitoMode(false) {
        // Load saved theme on startup
        loadTheme();

        QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);

        tabWidget = new QTabWidget(this);
        tabWidget->setTabsClosable(true);
        mainLayout->addWidget(tabWidget);

        openNewTab();

        QHBoxLayout *navLayout = new QHBoxLayout();
        navLayout->setContentsMargins(5, 5, 5, 5);
        navLayout->setSpacing(5);

        QPushButton *backButton = new QPushButton(QIcon(":/icons/back.png"), "", this);
        styleButton(backButton, "Back");
        navLayout->addWidget(backButton);

        QPushButton *forwardButton = new QPushButton(QIcon(":/icons/forward.png"), "", this);
        styleButton(forwardButton, "Forward");
        navLayout->addWidget(forwardButton);

        QPushButton *refreshButton = new QPushButton(QIcon(":/icons/refresh.png"), "", this);
        styleButton(refreshButton, "Refresh");
        navLayout->addWidget(refreshButton);

        QPushButton *privacyButton = new QPushButton(QIcon(":/icons/privacy.png"), "", this);
        styleButton(privacyButton, "Incognito Mode");
        navLayout->addWidget(privacyButton);

        urlBar = new QLineEdit(this);
        urlBar->setPlaceholderText("Enter URL or search...");
        urlBar->setStyleSheet(
            "QLineEdit { "
            "background-color: white; "
            "color: black; "
            "border: 2px solid gold; "
            "border-radius: 5px; "
            "padding: 5px; "
            "}"
        );
        navLayout->addWidget(urlBar);

        QPushButton *saveButton = new QPushButton(QIcon(":/icons/save.png"), "", this);
        styleButton(saveButton, "Save URL to Bookmarks");
        navLayout->addWidget(saveButton);

        QPushButton *bookmarkButton = new QPushButton(QIcon(":/icons/bookmark.png"), "", this);
        styleButton(bookmarkButton, "Show Bookmarks");
        navLayout->addWidget(bookmarkButton);

        QPushButton *newTabButton = new QPushButton(QIcon(":/icons/newtab.png"), "", this);
        styleButton(newTabButton, "New Tab");
        navLayout->addWidget(newTabButton);

        settingsButton = new QPushButton(QIcon(":/icons/settings.png"), "", this);
        styleButton(settingsButton, "Settings");
        navLayout->addWidget(settingsButton, 0, Qt::AlignRight);

        QPushButton *hideButton = new QPushButton(QIcon(":/icons/hide.png"), "", this);
        styleButton(hideButton, "Close Browser");
        navLayout->addWidget(hideButton);

        mainLayout->addLayout(navLayout);

        settingsPanel = new QWidget(this);
        settingsPanel->setVisible(false);

        QVBoxLayout *settingsLayout = new QVBoxLayout(settingsPanel);

        QLabel *logoLabel = new QLabel(settingsPanel);
        logoLabel->setPixmap(QPixmap(":/icons/ApexBrowser.png"));
        logoLabel->setAlignment(Qt::AlignCenter);
        settingsLayout->addWidget(logoLabel);

        QLabel *textLabel = new QLabel(settingsPanel);
        textLabel->setText(
            "Apex Browser Information\n"
            "Super Fast Custom Lightweight Qt6 Browser Written in C++ \n"
            "Version: 1.0 Build Date: 05-02-2025."
        );
        textLabel->setStyleSheet(
            "QLabel { "
            "color: gold; "
            "font-size: 16px; "
            "font-weight: bold; "
            "}"
        );
        textLabel->setAlignment(Qt::AlignCenter);
        settingsLayout->addWidget(textLabel);

        settingsLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));

        QPushButton *menuButton = new QPushButton(QIcon(":/icons/menuoptions.png"), "", this);
        styleButton(menuButton, "Menu");
        settingsLayout->addWidget(menuButton, 0, Qt::AlignRight);

        mainLayout->addWidget(settingsPanel);

        connect(backButton, &QPushButton::clicked, this, &BrowserWindow::goBack);
        connect(forwardButton, &QPushButton::clicked, this, &BrowserWindow::goForward);
        connect(refreshButton, &QPushButton::clicked, this, &BrowserWindow::refreshPage);
        connect(privacyButton, &QPushButton::clicked, this, &BrowserWindow::toggleIncognitoMode);
        connect(urlBar, &QLineEdit::returnPressed, this, &BrowserWindow::navigateToUrl);
        connect(saveButton, &QPushButton::clicked, this, &BrowserWindow::saveBookmark);
        connect(bookmarkButton, &QPushButton::clicked, this, &BrowserWindow::showBookmarks);
        connect(hideButton, &QPushButton::clicked, this, &BrowserWindow::hideBrowser);
        connect(newTabButton, &QPushButton::clicked, this, &BrowserWindow::openNewTab);
        connect(settingsButton, &QPushButton::clicked, this, &BrowserWindow::toggleSettingsPanel);
        connect(menuButton, &QPushButton::clicked, this, &BrowserWindow::showMenu);
        connect(tabWidget, &QTabWidget::tabCloseRequested, this, &BrowserWindow::closeTab);

        setWindowTitle("Apex Browser");
        resize(1024, 768);
    }

private slots:
    void navigateToUrl() {
        QString url = urlBar->text();
        if (!url.startsWith("http://") && !url.startsWith("https://")) {
            url = "https://" + url;
        }
        QWebEngineView *currentWebView = qobject_cast<QWebEngineView *>(tabWidget->currentWidget());
        if (currentWebView) {
            currentWebView->setUrl(QUrl(url));
        }
    }

    void openNewTab() {
        QWebEngineView *webView = new QWebEngineView(this);
        webView->setUrl(QUrl("https://www.google.com"));

        int tabIndex = tabWidget->addTab(webView, "New Tab");
        tabWidget->setTabIcon(tabIndex, QIcon(":/icons/ApexBrowser.png"));
        tabWidget->setCurrentIndex(tabIndex);

        connect(webView, &QWebEngineView::urlChanged, this, [this, webView](const QUrl &url) {
            if (webView == tabWidget->currentWidget()) {
                urlBar->setText(url.toString());
            }
            int index = tabWidget->indexOf(webView);
            if (index != -1) {
                QString host = url.host();
                tabWidget->setTabText(index, host.isEmpty() ? "New Tab" : host);
            }
        });

        connect(webView, &QWebEngineView::titleChanged, this, [this, webView](const QString &title) {
            int index = tabWidget->indexOf(webView);
            if (index != -1) {
                tabWidget->setTabText(index, title);
            }
        });
    }

    void closeTab(int index) {
        QWidget *tab = tabWidget->widget(index);
        tab->deleteLater();
        tabWidget->removeTab(index);
    }

    void goBack() {
        QWebEngineView *currentWebView = qobject_cast<QWebEngineView *>(tabWidget->currentWidget());
        if (currentWebView) {
            currentWebView->back();
        }
    }

    void goForward() {
        QWebEngineView *currentWebView = qobject_cast<QWebEngineView *>(tabWidget->currentWidget());
        if (currentWebView) {
            currentWebView->forward();
        }
    }

    void refreshPage() {
        QWebEngineView *currentWebView = qobject_cast<QWebEngineView *>(tabWidget->currentWidget());
        if (currentWebView) {
            currentWebView->reload();
        }
    }

    void saveBookmark() {
        QString url = urlBar->text();
        if (url.isEmpty()) {
            QMessageBox::warning(this, "No URL", "Please enter a URL to save.");
            return;
        }

        QDir dir("/home/apex/.config/ApexBrowser");
        if (!dir.exists()) {
            dir.mkpath(".");
        }

        QFile file("/home/apex/.config/ApexBrowser/bookmarks.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << url << "\n";
            file.close();
            QMessageBox::information(this, "Bookmark Saved", "The URL has been saved to bookmarks.");
        } else {
            QMessageBox::warning(this, "Error", "Could not save bookmark.");
        }
    }

    void showBookmarks() {
        QFile file("/home/apex/.config/ApexBrowser/bookmarks.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QStringList bookmarks;
            while (!in.atEnd()) {
                bookmarks << in.readLine();
            }
            file.close();

            QMenu menu;
            for (const QString &bookmark : bookmarks) {
                menu.addAction(bookmark);
            }
            menu.exec(QCursor::pos());
        } else {
            QMessageBox::warning(this, "No Bookmarks", "No bookmarks found.");
        }
    }

    void hideBrowser() {
        close();
    }

    void toggleIncognitoMode() {
        incognitoMode = !incognitoMode;

        QWebEngineProfile *profile = QWebEngineProfile::defaultProfile();
        if (incognitoMode) {
            profile->setPersistentCookiesPolicy(QWebEngineProfile::NoPersistentCookies);
            profile->setHttpCacheType(QWebEngineProfile::NoCache);
            QNetworkProxy::setApplicationProxy(QNetworkProxy(QNetworkProxy::HttpProxy, "9.9.9.11", 80));
            QMessageBox::information(this, "Incognito Mode", "Incognito mode is now active with Quad9 DNS.");
        } else {
            profile->setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);
            profile->setHttpCacheType(QWebEngineProfile::MemoryHttpCache);
            QNetworkProxy::setApplicationProxy(QNetworkProxy::NoProxy);
            QMessageBox::information(this, "Incognito Mode", "Incognito mode is now inactive.");
        }
    }

    void toggleSettingsPanel() {
        settingsPanel->setVisible(!settingsPanel->isVisible());
    }

    void showMenu() {
        QMenu menu;
        QAction *option1 = menu.addAction("Change Theme"); // Theme selector
        QAction *option2 = menu.addAction("Option 2");
        QAction *option3 = menu.addAction("Option 3");
        QAction *option4 = menu.addAction("Option 4");

        QAction *selectedOption = menu.exec(QCursor::pos());
        if (selectedOption == option1) {
            showThemeSelector();
        } else if (selectedOption == option2) {
            QMessageBox::information(this, "Option 2", "Not Implemented.");
        } else if (selectedOption == option3) {
            QMessageBox::information(this, "Option 3", "Not Implemented");
        } else if (selectedOption == option4) {
            QMessageBox::information(this, "Option 4", "Not Implemented");
        }
    }

    void showThemeSelector() {
        QDialog dialog(this);
        dialog.setWindowTitle("Select Theme");
        dialog.resize(300, 200); // Smaller size

        QVBoxLayout *dialogLayout = new QVBoxLayout;
        QLabel *themeLabel = new QLabel("Select Theme:", &dialog);
        QComboBox *themeSelector = new QComboBox(&dialog);
        themeSelector->addItem("Blue UI / Gold Text");
        themeSelector->addItem("Red UI / Black Text");
        themeSelector->addItem("Dark Blue UI / White Text");
        themeSelector->addItem("White UI / Red Text");
        themeSelector->addItem("Green UI / Red Text");
        themeSelector->addItem("Gold UI / Teal Text");

        dialogLayout->addWidget(themeLabel);
        dialogLayout->addWidget(themeSelector);

        QPushButton *saveButton = new QPushButton("Save", &dialog);
        dialogLayout->addWidget(saveButton);

        connect(saveButton, &QPushButton::clicked, [&]() {
            QString selectedTheme = themeSelector->currentText();
            QString configPath = "/home/apex/.config/ApexBrowser/Theme.txt";

            QDir dir("/home/apex/.config/ApexBrowser");
            if (!dir.exists()) {
                dir.mkpath(".");
            }

            QFile file(configPath);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out << selectedTheme;
                file.close();
                setTheme(selectedTheme); // Apply the selected theme immediately
                QMessageBox::information(&dialog, "Theme Saved", "Theme has been saved successfully.");
            } else {
                QMessageBox::warning(&dialog, "Error", "Failed to save theme.");
            }
            dialog.close();
        });

        dialog.setLayout(dialogLayout);
        dialog.move(rect().center() - dialog.rect().center()); // Centered above .png buttons
        dialog.exec();
    }

private:
    QTabWidget *tabWidget;
    QLineEdit *urlBar;
    QWidget *settingsPanel;
    QPushButton *settingsButton;
    bool incognitoMode;

    void styleButton(QPushButton *button, const QString &tooltip) {
        button->setToolTip(tooltip);
        button->setFixedSize(90, 30);
        button->setStyleSheet(
            "QPushButton { "
            "background-color: transparent; "
            "border: 2px solid gold; "
            "border-radius: 5px; "
            "padding: 5px; "
            "} "
            "QPushButton:hover { "
            "background-color: rgba(255, 215, 0, 50); "
            "}"
        );
    }

    void setTheme(const QString &theme) {
        if (theme == "Blue UI / Gold Text") {
             setStyleSheet("QWidget { background-color: #00568f; color: rgb(255, 215, 0); }");
        } else if (theme == "Red UI / Black Text") {
            setStyleSheet("QWidget { background-color: rgb(255, 0, 0); color: rgb(0, 0, 0); }");
        } else if (theme == "Dark Blue UI / White Text") {
            setStyleSheet("QWidget { background-color: rgb(0, 0, 128); color: rgb(255, 255, 255); }");
        } else if (theme == "White UI / Red Text") {
            setStyleSheet("QWidget { background-color: rgb(255, 255, 255); color: rgb(255, 0, 0); }");
        } else if (theme == "Green UI / Red Text") {
            setStyleSheet("QWidget { background-color: rgb(0, 128, 0); color: rgb(255, 0, 0); }");
        } else if (theme == "Gold UI / Teal Text") {
            setStyleSheet("QWidget { background-color: rgb(255, 215, 0); color: rgb(0, 128, 128); }");
        }
    }

    void loadTheme() {
        QDir dir("/home/apex/.config/ApexBrowser");
        if (!dir.exists()) {
            dir.mkpath(".");
        }

        QString configPath = "/home/apex/.config/ApexBrowser/Theme.txt";
        QFile file(configPath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString savedTheme = in.readLine();
            file.close();
            setTheme(savedTheme); // Apply the saved theme
        } else {
            setTheme("Teal UI / Gold Text"); // Default theme
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    BrowserWindow window;
    window.show();
    return app.exec();
}

#include "main.moc"

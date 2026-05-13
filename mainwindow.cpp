#include "mainwindow.h"
#include "FileHandler.h"
#include "Utils.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QFont>
#include <QColor>
#include <QGraphicsDropShadowEffect>
#include <QTimer>
#include <QDateTime>
#include <QCloseEvent>

void MainWindow::applyGlobalStyle() {
    qApp->setStyle("Fusion");
    setStyleSheet(R"(
        QMainWindow { background-color: #0B0F19; }
        QWidget { background-color: #0B0F19; color: #F3F4F6; font-family: 'Segoe UI', sans-serif; }
    )");
}

QWidget* MainWindow::makeCard(QWidget* parent) {
    QWidget* card = new QWidget(parent);
    card->setStyleSheet("QWidget { background-color: #111827; border: none; border-radius: 16px; }");
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(25); shadow->setColor(QColor(0, 0, 0, 100)); shadow->setOffset(0, 8);
    card->setGraphicsEffect(shadow);
    return card;
}

static QString shadeColor(const QString& c) {
    if (c == "#2563EB") return "#1D4ED8"; // Blue
    if (c == "#10B981") return "#059669"; // Emerald
    if (c == "#F59E0B") return "#D97706"; // Amber
    if (c == "#8B5CF6") return "#7C3AED"; // Purple
    if (c == "#475569") return "#334155"; // Slate
    if (c == "#EF4444") return "#DC2626"; // Red
    return c;
}

QPushButton* MainWindow::makeBtn(const QString& text, const QString& color) {
    QPushButton* btn = new QPushButton(text);
    btn->setMinimumHeight(55); btn->setCursor(Qt::PointingHandCursor);
    btn->setStyleSheet(QString(R"(
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 %1, stop:1 %2);
            color: #ffffff; border: none; border-radius: 10px; font-size: 15px; font-weight: bold; padding: 0 20px;
        }
        QPushButton:hover { background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 %2, stop:1 %1); }
        QPushButton:pressed { opacity: 0.8; }
    )").arg(color).arg(shadeColor(color)));
    return btn;
}

QLineEdit* MainWindow::makeInput(const QString& placeholder, bool password) {
    QLineEdit* input = new QLineEdit;
    input->setPlaceholderText(placeholder); input->setMinimumHeight(50);
    if (password) input->setEchoMode(QLineEdit::Password);
    input->setStyleSheet(R"(
        QLineEdit { background-color: #1F2937; border: 1px solid #374151; border-radius: 8px; color: #F3F4F6; font-size: 15px; padding: 0 16px; }
        QLineEdit:focus { border: 1px solid #2563EB; background-color: #111827; }
        QLineEdit::placeholder { color: #6B7280; }
    )");
    return input;
}

QLabel* MainWindow::makeLabel(const QString& text, int size, bool bold) {
    QLabel* lbl = new QLabel(text);
    QFont f; f.setPointSize(size); f.setBold(bold); lbl->setFont(f);
    lbl->setStyleSheet("background: transparent; border: none;");
    return lbl;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(nullptr) {
    applyGlobalStyle();
    setWindowTitle("Global Banking System");
    setMinimumSize(950, 650);

    pages = new QStackedWidget(this);
    setCentralWidget(pages);

    loginPage    = buildLoginPage();
    createPage   = buildCreatePage();
    dashPage     = buildDashPage();
    balancePage  = buildBalancePage();
    depositPage  = buildDepositPage();
    withdrawPage  = buildWithdrawPage();
    transferPage = buildTransferPage();
    historyPage  = buildHistoryPage();
    confirmPage  = buildConfirmPage();
    successPage  = buildSuccessPage();

    pages->addWidget(loginPage);
    pages->addWidget(createPage);
    pages->addWidget(dashPage);
    pages->addWidget(balancePage);
    pages->addWidget(depositPage);
    pages->addWidget(withdrawPage);
    pages->addWidget(transferPage);
    pages->addWidget(historyPage);
    pages->addWidget(confirmPage);
    pages->addWidget(successPage);

    pages->setCurrentWidget(loginPage);

    clockTimer = new QTimer(this);
    connect(clockTimer, &QTimer::timeout, this, &MainWindow::updateClock);
    clockTimer->start(1000);
    updateClock();
}

MainWindow::~MainWindow() {}
void MainWindow::updateClock() { if (clockLabel) clockLabel->setText(QDateTime::currentDateTime().toString("ddd, dd MMM yyyy\nhh:mm:ss AP")); }
void MainWindow::showPage(QWidget* page) { pages->setCurrentWidget(page); }

QWidget* MainWindow::buildLoginPage() {
    QWidget* root = new QWidget; QVBoxLayout* rootLayout = new QVBoxLayout(root); rootLayout->setAlignment(Qt::AlignCenter);
    QWidget* card = makeCard(root); card->setFixedSize(480, 500);
    QVBoxLayout* cardLayout = new QVBoxLayout(card); cardLayout->setContentsMargins(40, 50, 40, 50); cardLayout->setSpacing(20);

    QLabel* brand = makeLabel("GLOBAL BANK", 26, true);
    brand->setAlignment(Qt::AlignCenter); brand->setStyleSheet("color: #2563EB; letter-spacing: 2px;");

    QLabel* sub = makeLabel("Access Your Account", 12);
    sub->setAlignment(Qt::AlignCenter); sub->setStyleSheet("color: #9CA3AF; margin-bottom: 20px;");

    loginAccInput = makeInput("Account Number");
    loginPinInput = makeInput("Security PIN", true);

    loginError = makeLabel("", 11); loginError->setAlignment(Qt::AlignCenter); loginError->setStyleSheet("color: #EF4444;");

    QHBoxLayout* btnLayout = new QHBoxLayout;
    QPushButton* loginBtn = makeBtn("AUTHORIZE", "#2563EB");
    QPushButton* createBtn = makeBtn("REGISTER", "#8B5CF6");
    btnLayout->addWidget(loginBtn); btnLayout->addWidget(createBtn);

    connect(loginBtn,  &QPushButton::clicked, this, &MainWindow::onLoginClicked);
    connect(createBtn, &QPushButton::clicked, this, [this]{ showPage(createPage); });

    cardLayout->addWidget(brand); cardLayout->addWidget(sub); cardLayout->addWidget(loginAccInput);
    cardLayout->addWidget(loginPinInput); cardLayout->addWidget(loginError); cardLayout->addLayout(btnLayout); cardLayout->addStretch();
    rootLayout->addWidget(card); return root;
}

QWidget* MainWindow::buildCreatePage() {
    QWidget* root = new QWidget; QVBoxLayout* layout = new QVBoxLayout(root); layout->setAlignment(Qt::AlignCenter);
    QWidget* card = makeCard(root); card->setFixedSize(500, 550);
    QVBoxLayout* cl = new QVBoxLayout(card); cl->setContentsMargins(40, 40, 40, 40); cl->setSpacing(18);

    QLabel* title = makeLabel("Account Registration", 22, true); title->setAlignment(Qt::AlignCenter); title->setStyleSheet("color: #2563EB;");

    createAccInput = makeInput("Enter New Account Number");
    createPinInput = makeInput("Create 4-Digit PIN", true);
    createBalInput = makeInput("Initial Deposit Amount");

    createError = makeLabel("", 11); createError->setAlignment(Qt::AlignCenter);

    QHBoxLayout* btnRow = new QHBoxLayout;
    QPushButton* backBtn    = makeBtn("RETURN", "#475569");
    QPushButton* confirmBtn = makeBtn("CONFIRM REGISTRATION", "#10B981");
    btnRow->addWidget(backBtn); btnRow->addWidget(confirmBtn);

    connect(confirmBtn, &QPushButton::clicked, this, &MainWindow::onCreateConfirmClicked);
    connect(backBtn,    &QPushButton::clicked, this, [this]{ showPage(loginPage); });

    cl->addWidget(title); cl->addSpacing(20); cl->addWidget(makeLabel("Identification Details", 10, true));
    cl->addWidget(createAccInput); cl->addWidget(createPinInput); cl->addWidget(createBalInput);
    cl->addWidget(createError); cl->addLayout(btnRow); cl->addStretch();
    layout->addWidget(card); return root;
}

QWidget* MainWindow::buildDashPage() {
    QWidget* root = new QWidget;
    QVBoxLayout* rootLayout = new QVBoxLayout(root);
    rootLayout->setContentsMargins(50, 30, 50, 40);
    rootLayout->setSpacing(30);

    QHBoxLayout* topRow = new QHBoxLayout;
    clockLabel = makeLabel("", 13, true);
    clockLabel->setStyleSheet("color: #9CA3AF;");
    clockLabel->setAlignment(Qt::AlignRight);
    topRow->addStretch();
    topRow->addWidget(clockLabel);

    QWidget* infoCard = makeCard(root);
    infoCard->setFixedWidth(550);
    QVBoxLayout* infoLayout = new QVBoxLayout(infoCard);
    infoLayout->setAlignment(Qt::AlignCenter);
    infoLayout->setContentsMargins(30, 25, 30, 25);

    QLabel* brandLbl = makeLabel("GLOBAL BANK", 28, true);
    brandLbl->setStyleSheet("color: #2563EB; letter-spacing: 3px;");
    brandLbl->setAlignment(Qt::AlignCenter);

    dashWelcome = makeLabel("Welcome,", 18);
    dashWelcome->setStyleSheet("color: #F3F4F6;");
    dashWelcome->setAlignment(Qt::AlignCenter);

    infoLayout->addWidget(brandLbl);
    infoLayout->addSpacing(10);
    infoLayout->addWidget(dashWelcome);

    QWidget* gridWidget = new QWidget;
    QGridLayout* gridLayout = new QGridLayout(gridWidget);
    gridLayout->setSpacing(20);

    QPushButton* btnDep  = makeBtn("DEPOSIT FUNDS", "#10B981");
    QPushButton* btnWd   = makeBtn("WITHDRAW CASH", "#F59E0B");
    QPushButton* btnTr   = makeBtn("TRANSFER FUNDS", "#8B5CF6");
    QPushButton* btnBal  = makeBtn("CHECK BALANCE", "#2563EB");
    QPushButton* btnHist = makeBtn("TRANSACTION HISTORY", "#475569");

    btnDep->setMinimumHeight(70); btnWd->setMinimumHeight(70);
    btnTr->setMinimumHeight(70); btnBal->setMinimumHeight(70);
    btnHist->setMinimumHeight(70);

    connect(btnDep, &QPushButton::clicked, this, &MainWindow::onDepositClicked);
    connect(btnWd, &QPushButton::clicked, this, &MainWindow::onWithdrawClicked);
    connect(btnTr, &QPushButton::clicked, this, &MainWindow::onTransferClicked);
    connect(btnBal, &QPushButton::clicked, this, &MainWindow::onCheckBalanceClicked);
    connect(btnHist, &QPushButton::clicked, this, &MainWindow::onHistoryClicked);

    gridLayout->addWidget(btnDep, 0, 0);
    gridLayout->addWidget(btnWd, 0, 1);
    gridLayout->addWidget(btnTr, 1, 0);
    gridLayout->addWidget(btnBal, 1, 1);
    gridLayout->addWidget(btnHist, 2, 0, 1, 2);

    QHBoxLayout* bottomRow = new QHBoxLayout;
    QPushButton* logoutBtn = makeBtn("SECURE LOGOUT", "#EF4444");
    logoutBtn->setMinimumWidth(250);
    connect(logoutBtn, &QPushButton::clicked, this, &MainWindow::onLogoutClicked);
    bottomRow->addStretch();
    bottomRow->addWidget(logoutBtn);

    rootLayout->addLayout(topRow);
    rootLayout->addWidget(infoCard, 0, Qt::AlignHCenter);
    rootLayout->addSpacing(10);
    rootLayout->addWidget(gridWidget, 1);
    rootLayout->addLayout(bottomRow);

    return root;
}

QWidget* MainWindow::buildBalancePage() {
    QWidget* root = new QWidget; QVBoxLayout* layout = new QVBoxLayout(root); layout->setAlignment(Qt::AlignCenter);
    QWidget* card = makeCard(root); card->setFixedSize(550, 350); QVBoxLayout* cl = new QVBoxLayout(card); cl->setContentsMargins(50, 50, 50, 50);

    QLabel* title = makeLabel("Available Balance", 22, true); title->setStyleSheet("color: #2563EB;"); title->setAlignment(Qt::AlignCenter);
    balanceDisplayLabel = makeLabel("$0.00", 45, true); balanceDisplayLabel->setStyleSheet("color: #F3F4F6;"); balanceDisplayLabel->setAlignment(Qt::AlignCenter);

    QPushButton* backBtn = makeBtn("RETURN TO DASHBOARD", "#475569");
    connect(backBtn, &QPushButton::clicked, this, [this]{ refreshDash(); showPage(dashPage); });

    cl->addWidget(title); cl->addSpacing(30); cl->addWidget(balanceDisplayLabel); cl->addSpacing(30); cl->addWidget(backBtn, 0, Qt::AlignCenter);
    layout->addWidget(card); return root;
}

QWidget* MainWindow::buildDepositPage() {
    QWidget* root = new QWidget; QVBoxLayout* layout = new QVBoxLayout(root); layout->setAlignment(Qt::AlignCenter);
    QWidget* card = makeCard(root); card->setFixedSize(550, 400); QVBoxLayout* cl = new QVBoxLayout(card); cl->setContentsMargins(50, 50, 50, 50);

    QLabel* title = makeLabel("Cash Deposit", 22, true); title->setStyleSheet("color: #10B981;"); title->setAlignment(Qt::AlignCenter);
    depositInput = makeInput("Enter Deposit Amount"); depositInput->setStyleSheet("font-size: 18px; padding: 20px; background: #1F2937; border: none; border-radius: 10px;"); depositInput->setMinimumHeight(70);
    depositResult = makeLabel("", 12); depositResult->setAlignment(Qt::AlignCenter);

    QHBoxLayout* btnRow = new QHBoxLayout; QPushButton* backBtn = makeBtn("CANCEL", "#475569"); QPushButton* depBtn  = makeBtn("REVIEW", "#10B981");
    btnRow->addWidget(backBtn); btnRow->addWidget(depBtn);
    connect(depBtn,  &QPushButton::clicked, this, &MainWindow::onDepositClicked); connect(backBtn, &QPushButton::clicked, this, [this]{ refreshDash(); showPage(dashPage); });

    cl->addWidget(title); cl->addSpacing(30); cl->addWidget(depositInput); cl->addWidget(depositResult); cl->addSpacing(20); cl->addLayout(btnRow);
    layout->addWidget(card); return root;
}

QWidget* MainWindow::buildWithdrawPage() {
    QWidget* root = new QWidget; QVBoxLayout* layout = new QVBoxLayout(root); layout->setAlignment(Qt::AlignCenter);
    QWidget* card = makeCard(root); card->setFixedSize(550, 400); QVBoxLayout* cl = new QVBoxLayout(card); cl->setContentsMargins(50, 50, 50, 50);

    QLabel* title = makeLabel("Cash Withdrawal", 22, true); title->setStyleSheet("color: #F59E0B;"); title->setAlignment(Qt::AlignCenter);
    withdrawInput = makeInput("Enter Withdrawal Amount"); withdrawInput->setStyleSheet("font-size: 18px; padding: 20px; background: #1F2937; border: none; border-radius: 10px;"); withdrawInput->setMinimumHeight(70);
    withdrawResult = makeLabel("Note: Standard Transaction Fee Applies.", 11); withdrawResult->setStyleSheet("color: #9CA3AF;"); withdrawResult->setAlignment(Qt::AlignCenter);

    QHBoxLayout* btnRow = new QHBoxLayout; QPushButton* backBtn = makeBtn("CANCEL", "#475569"); QPushButton* wdBtn   = makeBtn("REVIEW", "#F59E0B");
    btnRow->addWidget(backBtn); btnRow->addWidget(wdBtn);
    connect(wdBtn,   &QPushButton::clicked, this, &MainWindow::onWithdrawClicked); connect(backBtn, &QPushButton::clicked, this, [this]{ refreshDash(); showPage(dashPage); });

    cl->addWidget(title); cl->addSpacing(30); cl->addWidget(withdrawInput); cl->addWidget(withdrawResult); cl->addSpacing(20); cl->addLayout(btnRow);
    layout->addWidget(card); return root;
}

QWidget* MainWindow::buildTransferPage() {
    QWidget* root = new QWidget; QVBoxLayout* layout = new QVBoxLayout(root); layout->setAlignment(Qt::AlignCenter);
    QWidget* card = makeCard(root); card->setFixedSize(550, 450); QVBoxLayout* cl = new QVBoxLayout(card); cl->setContentsMargins(50, 40, 50, 40);

    QLabel* title = makeLabel("Fund Transfer", 22, true); title->setStyleSheet("color: #8B5CF6;"); title->setAlignment(Qt::AlignCenter);
    transferAccInput = makeInput("Recipient Account Number"); transferAmtInput = makeInput("Enter Transfer Amount");
    transferResult = makeLabel("Note: Standard Transfer Fee Applies.", 11); transferResult->setStyleSheet("color: #9CA3AF;"); transferResult->setAlignment(Qt::AlignCenter);

    QHBoxLayout* btnRow = new QHBoxLayout; QPushButton* backBtn = makeBtn("CANCEL", "#475569"); QPushButton* trBtn   = makeBtn("REVIEW", "#8B5CF6");
    btnRow->addWidget(backBtn); btnRow->addWidget(trBtn);
    connect(trBtn,   &QPushButton::clicked, this, &MainWindow::onTransferClicked); connect(backBtn, &QPushButton::clicked, this, [this]{ refreshDash(); showPage(dashPage); });

    cl->addWidget(title); cl->addSpacing(20); cl->addWidget(transferAccInput); cl->addWidget(transferAmtInput); cl->addWidget(transferResult); cl->addSpacing(20); cl->addLayout(btnRow);
    layout->addWidget(card); return root;
}

QWidget* MainWindow::buildHistoryPage() {
    QWidget* root = new QWidget; QVBoxLayout* layout = new QVBoxLayout(root); layout->setContentsMargins(50, 40, 50, 40); layout->setSpacing(20);
    QLabel* title = makeLabel("Transaction Ledger", 24, true); title->setStyleSheet("color: #2563EB;");
    historyText = new QTextEdit; historyText->setReadOnly(true);
    historyText->setStyleSheet(R"( QTextEdit { background-color: #111827; border: none; border-radius: 12px; color: #D1D5DB; font-family: 'Consolas', monospace; font-size: 14px; padding: 20px; line-height: 1.5; } )");

    QPushButton* backBtn = makeBtn("RETURN TO DASHBOARD", "#475569"); backBtn->setMaximumWidth(300);
    connect(backBtn, &QPushButton::clicked, this, [this]{ refreshDash(); showPage(dashPage); });

    layout->addWidget(title); layout->addWidget(historyText, 1); layout->addWidget(backBtn, 0, Qt::AlignCenter);
    return root;
}

QWidget* MainWindow::buildConfirmPage() {
    QWidget* root = new QWidget; QVBoxLayout* layout = new QVBoxLayout(root); layout->setAlignment(Qt::AlignCenter);
    QWidget* card = makeCard(root); card->setFixedSize(500, 350); QVBoxLayout* cl = new QVBoxLayout(card); cl->setContentsMargins(40, 40, 40, 40);

    confirmTitle = makeLabel("Review Transaction", 20, true);
    confirmTitle->setAlignment(Qt::AlignCenter);

    confirmDetails = makeLabel("Details", 14, false);
    confirmDetails->setStyleSheet("color: #D1D5DB;");
    confirmDetails->setAlignment(Qt::AlignCenter);

    QHBoxLayout* btnRow = new QHBoxLayout;
    QPushButton* noBtn = makeBtn("CANCEL", "#475569");
    QPushButton* yesBtn  = makeBtn("AUTHORIZE", "#2563EB");
    btnRow->addWidget(noBtn); btnRow->addWidget(yesBtn);

    connect(noBtn, &QPushButton::clicked, this, &MainWindow::cancelPendingAction);
    connect(yesBtn, &QPushButton::clicked, this, &MainWindow::executePendingAction);

    cl->addWidget(confirmTitle); cl->addSpacing(20); cl->addWidget(confirmDetails); cl->addSpacing(30); cl->addLayout(btnRow);
    layout->addWidget(card); return root;
}

QWidget* MainWindow::buildSuccessPage() {
    QWidget* root = new QWidget; QVBoxLayout* layout = new QVBoxLayout(root); layout->setAlignment(Qt::AlignCenter);
    QWidget* card = makeCard(root); card->setFixedSize(550, 400); QVBoxLayout* cl = new QVBoxLayout(card); cl->setContentsMargins(40, 40, 40, 40);

    QLabel* thankYouLbl = makeLabel("Thank You for using Global Bank!", 18, true);
    thankYouLbl->setStyleSheet("color: #2563EB;"); thankYouLbl->setAlignment(Qt::AlignCenter);

    successMessage = makeLabel("Transaction details here.", 14, false);
    successMessage->setStyleSheet("color: #D1D5DB;"); successMessage->setAlignment(Qt::AlignCenter);

    successBalanceLabel = makeLabel("Current Balance: $0.00", 24, true);
    successBalanceLabel->setStyleSheet("color: #10B981; margin-top: 10px; margin-bottom: 20px;");
    successBalanceLabel->setAlignment(Qt::AlignCenter);

    QLabel* prompt = makeLabel("Would you like to perform another transaction?", 12, false);
    prompt->setStyleSheet("color: #9CA3AF;"); prompt->setAlignment(Qt::AlignCenter);

    QHBoxLayout* btnRow = new QHBoxLayout;
    QPushButton* noBtn = makeBtn("FINISH & LOGOUT", "#EF4444");
    QPushButton* yesBtn  = makeBtn("NEW TRANSACTION", "#475569");
    btnRow->addWidget(noBtn); btnRow->addWidget(yesBtn);

    connect(yesBtn,  &QPushButton::clicked, this, [this]{ refreshDash(); showPage(dashPage); });
    connect(noBtn, &QPushButton::clicked, this, &MainWindow::onLogoutClicked);

    cl->addWidget(thankYouLbl); cl->addSpacing(15); cl->addWidget(successMessage);
    cl->addWidget(successBalanceLabel); cl->addWidget(prompt); cl->addSpacing(20); cl->addLayout(btnRow);
    layout->addWidget(card); return root;
}

void MainWindow::refreshDash() {
    dashWelcome->setText("Welcome, " + QString::fromStdString(currentAccount.accountNumber));
}

void MainWindow::onLoginClicked() {
    QString acc = loginAccInput->text().trimmed(); QString pin = loginPinInput->text().trimmed();
    if (acc.isEmpty() || pin.isEmpty()) { loginError->setText("Please fill in all required fields."); return; }
    if (!FileHandler::accountExists(acc.toStdString())) { loginError->setText("Account record not found."); return; }

    Account tmpAcc; if (!FileHandler::loadAccount(acc.toStdString(), tmpAcc)) { loginError->setText("System error loading account."); return; }

    if (!tmpAcc.verifyPin(pin.toStdString())) {
        FileHandler::saveAccount(tmpAcc);
        if (tmpAcc.isLocked) loginError->setText("Account restricted due to failed attempts.");
        else loginError->setText("Authentication failed. Attempts remaining: " + QString::number(3 - tmpAcc.failedAttempts));
        return;
    }

    currentAccount = tmpAcc; loggedIn = true; loginError->clear(); loginAccInput->clear(); loginPinInput->clear();
    refreshDash(); showPage(dashPage);
}

void MainWindow::onCreateConfirmClicked() {
    QString acc = createAccInput->text().trimmed(); QString pin = createPinInput->text().trimmed(); QString bal = createBalInput->text().trimmed();
    if (acc.isEmpty() || pin.isEmpty() || bal.isEmpty()) { createError->setText("Please complete all fields."); return; }
    if (FileHandler::accountExists(acc.toStdString())) { createError->setText("Account Number already registered."); return; }

    bool ok; double initBal = bal.toDouble(&ok);
    if (!ok || initBal < 0) { createError->setText("Invalid balance format."); return; }

    Account newAcc(acc.toStdString(), pin.toStdString(), initBal);
    if (!FileHandler::saveAccount(newAcc)) { createError->setText("System error during registration."); return; }

    FileHandler::addToIndex(acc.toStdString());

    createError->setStyleSheet("color: #10B981;"); createError->setText("Registration Successful!");
    createAccInput->clear(); createPinInput->clear(); createBalInput->clear();
    QTimer::singleShot(1500, this, [this]{ createError->setStyleSheet("color: #EF4444;"); createError->clear(); showPage(loginPage); });
}

void MainWindow::onCheckBalanceClicked() {
    balanceDisplayLabel->setText("$" + QString::fromStdString(fmt(currentAccount.balance)));
    showPage(balancePage);
}

void MainWindow::onDepositClicked() {
    if (pages->currentWidget() != depositPage) { depositInput->clear(); depositResult->clear(); showPage(depositPage); return; }

    bool ok; double amount = depositInput->text().toDouble(&ok);
    if (!ok || amount <= 0) { depositResult->setStyleSheet("color: #EF4444;"); depositResult->setText("Invalid transaction amount."); return; }

    currentAction = Deposit; currentAmount = amount;
    confirmTitle->setText("Confirm Deposit"); confirmTitle->setStyleSheet("color: #10B981;");
    confirmDetails->setText("You are about to deposit:\n\n$" + QString::fromStdString(fmt(amount)));
    showPage(confirmPage);
}

void MainWindow::onWithdrawClicked() {
    if (pages->currentWidget() != withdrawPage) { withdrawInput->clear(); withdrawResult->setStyleSheet("color: #9CA3AF;"); withdrawResult->setText("Note: Standard Transaction Fee Applies."); showPage(withdrawPage); return; }

    bool ok; double amount = withdrawInput->text().toDouble(&ok);
    if (!ok || amount <= 0) { withdrawResult->setStyleSheet("color: #EF4444;"); withdrawResult->setText("Invalid transaction amount."); return; }

    currentAction = Withdraw; currentAmount = amount;
    confirmTitle->setText("Confirm Withdrawal"); confirmTitle->setStyleSheet("color: #F59E0B;");
    confirmDetails->setText("You are about to withdraw:\n\n$" + QString::fromStdString(fmt(amount)) + "\n(Includes $2.00 fee)");
    showPage(confirmPage);
}

void MainWindow::onTransferClicked() {
    if (pages->currentWidget() != transferPage) { transferAccInput->clear(); transferAmtInput->clear(); transferResult->setStyleSheet("color: #9CA3AF;"); transferResult->setText("Note: Standard Transfer Fee Applies."); showPage(transferPage); return; }

    QString toAcc = transferAccInput->text().trimmed(); QString amtStr = transferAmtInput->text().trimmed();
    if (toAcc.isEmpty() || amtStr.isEmpty()) { transferResult->setStyleSheet("color: #EF4444;"); transferResult->setText("Please complete all fields."); return; }
    if (toAcc.toStdString() == currentAccount.accountNumber) { transferResult->setStyleSheet("color: #EF4444;"); transferResult->setText("Cannot transfer to the origin account."); return; }
    if (!FileHandler::accountExists(toAcc.toStdString())) { transferResult->setStyleSheet("color: #EF4444;"); transferResult->setText("Recipient account not recognized."); return; }

    bool ok; double amount = amtStr.toDouble(&ok);
    if (!ok || amount <= 0) { transferResult->setStyleSheet("color: #EF4444;"); transferResult->setText("Invalid transaction amount."); return; }

    currentAction = Transfer; currentAmount = amount; currentTarget = toAcc;
    confirmTitle->setText("Confirm Transfer"); confirmTitle->setStyleSheet("color: #8B5CF6;");
    confirmDetails->setText("You are about to transfer:\n\n$" + QString::fromStdString(fmt(amount)) + "\nTo Account: " + toAcc + "\n(Includes $5.00 fee)");
    showPage(confirmPage);
}

void MainWindow::cancelPendingAction() {
    currentAction = None;
    showPage(dashPage);
}

void MainWindow::executePendingAction() {
    if (currentAction == Deposit) {
        currentAccount.deposit(currentAmount); FileHandler::saveAccount(currentAccount);
        depositInput->clear(); depositResult->clear();
        successMessage->setText("Successfully Deposited: $" + QString::fromStdString(fmt(currentAmount)));
    }
    else if (currentAction == Withdraw) {
        if (!currentAccount.withdraw(currentAmount)) {
            withdrawResult->setStyleSheet("color: #EF4444;"); withdrawResult->setText("Insufficient funds for this transaction.");
            showPage(withdrawPage); return;
        }
        FileHandler::saveAccount(currentAccount);
        withdrawInput->clear(); withdrawResult->clear();
        successMessage->setText("Successfully Withdrew: $" + QString::fromStdString(fmt(currentAmount)));
    }
    else if (currentAction == Transfer) {
        Account recipient; FileHandler::loadAccount(currentTarget.toStdString(), recipient);
        if (!currentAccount.sendTransfer(currentAmount, currentTarget.toStdString())) {
            transferResult->setStyleSheet("color: #EF4444;"); transferResult->setText("Insufficient funds for this transfer.");
            showPage(transferPage); return;
        }
        recipient.receiveTransfer(currentAmount, currentAccount.accountNumber);
        FileHandler::saveAccount(currentAccount); FileHandler::saveAccount(recipient);
        transferAccInput->clear(); transferAmtInput->clear(); transferResult->clear();
        successMessage->setText("Successfully Transferred: $" + QString::fromStdString(fmt(currentAmount)) + " to " + currentTarget);
    }

    currentAction = None;
    successBalanceLabel->setText("Available Balance: $" + QString::fromStdString(fmt(currentAccount.balance)));
    showPage(successPage);
}

void MainWindow::onHistoryClicked() {
    if (currentAccount.transactions.empty()) { historyText->setPlainText("No transaction records found."); }
    else {
        QString txt = "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        txt += "  ACCOUNT: " + QString::fromStdString(currentAccount.accountNumber) + "\n";
        txt += "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
        for (int i = currentAccount.transactions.size() - 1; i >= 0; --i) {
            txt += "  [" + QString::number(currentAccount.transactions.size() - i) + "]  " + QString::fromStdString(currentAccount.transactions[i]) + "\n\n";
        }
        historyText->setPlainText(txt);
    }
    showPage(historyPage);
}

void MainWindow::onLogoutClicked() { FileHandler::saveAccount(currentAccount); currentAccount = Account(); loggedIn = false; showPage(loginPage); }
void MainWindow::closeEvent(QCloseEvent *event) { if (loggedIn) { FileHandler::saveAccount(currentAccount); } event->accept(); }
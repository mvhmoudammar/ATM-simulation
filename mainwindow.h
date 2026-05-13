#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include <QCloseEvent>
#include "Account.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void updateClock();
    void onLoginClicked();
    void onCreateConfirmClicked();
    void onCheckBalanceClicked();
    void onDepositClicked();
    void onWithdrawClicked();
    void onTransferClicked();
    void onHistoryClicked();
    void onLogoutClicked();

    void executePendingAction();
    void cancelPendingAction();

private:
    Ui::MainWindow *ui;
    Account currentAccount;
    bool loggedIn = false;

    enum PendingAction { None, Deposit, Withdraw, Transfer };
    PendingAction currentAction = None;
    double currentAmount = 0.0;
    QString currentTarget = "";

    QStackedWidget *pages;
    QTimer *clockTimer;

    QWidget *loginPage;
    QWidget *createPage;
    QWidget *dashPage;
    QWidget *balancePage;
    QWidget *depositPage;
    QWidget *withdrawPage;
    QWidget *transferPage;
    QWidget *historyPage;
    QWidget *confirmPage; 
    QWidget *successPage;

    QLabel *clockLabel;
    QLabel *dashWelcome;
    QLabel *balanceDisplayLabel;

    QLabel *confirmTitle;
    QLabel *confirmDetails;

    QLabel *successMessage;
    QLabel *successBalanceLabel;

    QLabel *loginError;
    QLabel *createError;
    QLabel *depositResult;
    QLabel *withdrawResult;
    QLabel *transferResult;

    QLineEdit *loginAccInput;
    QLineEdit *loginPinInput;
    QLineEdit *createAccInput;
    QLineEdit *createPinInput;
    QLineEdit *createBalInput;

    QLineEdit *depositInput;
    QLineEdit *withdrawInput;
    QLineEdit *transferAccInput;
    QLineEdit *transferAmtInput;

    QTextEdit *historyText;

    void applyGlobalStyle();
    QWidget* makeCard(QWidget* parent = nullptr);
    QPushButton* makeBtn(const QString& text, const QString& color);
    QLineEdit* makeInput(const QString& placeholder, bool password = false);
    QLabel* makeLabel(const QString& text, int size, bool bold = false);

    QWidget* buildLoginPage();
    QWidget* buildCreatePage();
    QWidget* buildDashPage();
    QWidget* buildBalancePage();
    QWidget* buildDepositPage();
    QWidget* buildWithdrawPage();
    QWidget* buildTransferPage();
    QWidget* buildHistoryPage();
    QWidget* buildConfirmPage(); 
    QWidget* buildSuccessPage();

    void refreshDash();
    void showPage(QWidget* page);
};

#endif // MAINWINDOW_H

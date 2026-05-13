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

    // دوال شاشة التأكيد الداخلية الجديدة
    void executePendingAction();
    void cancelPendingAction();

private:
    Ui::MainWindow *ui;
    Account currentAccount;
    bool loggedIn = false;

    // متغيرات لحفظ العملية قبل التأكيد
    enum PendingAction { None, Deposit, Withdraw, Transfer };
    PendingAction currentAction = None;
    double currentAmount = 0.0;
    QString currentTarget = "";

    // المكونات الأساسية
    QStackedWidget *pages;
    QTimer *clockTimer;

    // الشاشات
    QWidget *loginPage;
    QWidget *createPage;
    QWidget *dashPage;
    QWidget *balancePage;
    QWidget *depositPage;
    QWidget *withdrawPage;
    QWidget *transferPage;
    QWidget *historyPage;
    QWidget *confirmPage; // شاشة التأكيد الجديدة
    QWidget *successPage;

    // عناصر الواجهة
    QLabel *clockLabel;
    QLabel *dashWelcome;
    QLabel *balanceDisplayLabel;

    // عناصر شاشة التأكيد
    QLabel *confirmTitle;
    QLabel *confirmDetails;

    // عناصر شاشة النجاح
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

    // دوال المساعدة والبناء
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
    QWidget* buildConfirmPage(); // بناء شاشة التأكيد
    QWidget* buildSuccessPage();

    void refreshDash();
    void showPage(QWidget* page);
};

#endif // MAINWINDOW_H
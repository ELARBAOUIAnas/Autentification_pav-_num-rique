#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTimer>

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);

private slots:
    void togglePasswordVisibility();
    void checkFields();
    void authenticate();

private:
    QLineEdit *idLineEdit;
    QLineEdit *passwordLineEdit;
    QCheckBox *passwordCheckBox;
    QPushButton *loginButton;
    QLabel *messageLabel;

    // Variables internes
    const QString ID = "anas";
    const QString M_p = "1234";
};

#endif // WINDOW_H

/*#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);

private slots:
    void checkFields();
    void authenticate();

private:
    void generateNumPad(QGridLayout *layout);

    QLineEdit *idLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QLabel *messageLabel;
};

#endif // WINDOW_H

*/

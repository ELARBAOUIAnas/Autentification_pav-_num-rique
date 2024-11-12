#include "window.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QTimer>

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    // Création des éléments
    QLabel *idLabel = new QLabel(tr("Identifiant:"));
    QLabel *passwordLabel = new QLabel(tr("Mot de passe:"));

    idLineEdit = new QLineEdit;
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password); // Masquer le mot de passe par défaut

    passwordCheckBox = new QCheckBox(tr("Masquer/afficher le mot de passe"));

    loginButton = new QPushButton(tr("Connexion"));
    loginButton->setEnabled(false); // Bouton désactivé au départ

    messageLabel = new QLabel;

    // Création du pavé numérique
    QGridLayout *numPadLayout = new QGridLayout;
    for (int i = 0; i <= 9; ++i) {
        QPushButton *button = new QPushButton(QString::number(i));
        button->setStyleSheet("background-color: lightgray;"); // Couleur initiale

        int row = (i - 1) / 3;
        int col = (i - 1) % 3;

        if (i == 0) {
            row = 3;
            col = 1;
        }
        numPadLayout->addWidget(button, row, col);

        // Connecter chaque bouton du pavé numérique pour gérer l'appui
        connect(button, &QPushButton::pressed, this, [this, button, i]() {
            // Mettre le bouton en rouge au moment de l'appui
            button->setStyleSheet("background-color: yellow;");

            // Ajouter le chiffre au champ de mot de passe si celui-ci a le focus
            if (passwordLineEdit->hasFocus()) {
                passwordLineEdit->setText(passwordLineEdit->text() + QString::number(i));
            } else {
                passwordLineEdit->setFocus();
                passwordLineEdit->setText(passwordLineEdit->text() + QString::number(i));
            }

            // Restaurer la couleur initiale après 200 ms
            QTimer::singleShot(200, [button]() {
                button->setStyleSheet("background-color: lightgray;");
            });
        });
    }

    // Ajout des éléments à la mise en page
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(idLabel);
    mainLayout->addWidget(idLineEdit);
    mainLayout->addWidget(passwordLabel);
    mainLayout->addWidget(passwordLineEdit);
    mainLayout->addWidget(passwordCheckBox);
    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(messageLabel);
    mainLayout->addLayout(numPadLayout);

    setLayout(mainLayout);

    // Connexions
    connect(passwordCheckBox, &QCheckBox::toggled, this, &Window::togglePasswordVisibility);
    connect(idLineEdit, &QLineEdit::textChanged, this, &Window::checkFields);
    connect(passwordLineEdit, &QLineEdit::textChanged, this, &Window::checkFields);
    connect(loginButton, &QPushButton::clicked, this, &Window::authenticate);
}

void Window::togglePasswordVisibility()
{
    if (passwordCheckBox->isChecked()) {
        passwordLineEdit->setEchoMode(QLineEdit::Normal); // Afficher le mot de passe
    } else {
        passwordLineEdit->setEchoMode(QLineEdit::Password); // Masquer le mot de passe
    }
}

void Window::checkFields()
{
    // Activer le bouton de connexion uniquement lorsque les champs sont remplis
    if (!idLineEdit->text().isEmpty() && !passwordLineEdit->text().isEmpty()) {
        loginButton->setEnabled(true);
    } else {
        loginButton->setEnabled(false);
    }
}

void Window::authenticate()
{
    const QString correctID = "anas";
    const QString correctPassword = "1234";

    // Vérification de l'identifiant et du mot de passe
    if (idLineEdit->text() == correctID && passwordLineEdit->text() == correctPassword) {
        loginButton->setStyleSheet("background-color: green;"); // Connexion réussie
        messageLabel->setText("Authentification réussie.");
        messageLabel->setStyleSheet("color: green;");
    } else {
        loginButton->setStyleSheet("background-color: red;"); // Connexion échouée
        messageLabel->setText("Authentification échouée.");
        messageLabel->setStyleSheet("color: red;");
    }
}

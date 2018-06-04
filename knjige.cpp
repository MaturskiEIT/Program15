#include "knjige.h"
#include "ui_knjige.h"
#include "konekcija.h"
#include <QMessageBox>

Knjige::Knjige(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Knjige)
{
    ui->setupUi(this);

    Konekcija baza;
    if(!baza.dbOpen())
    {
        QMessageBox::critical(this, "Kriticno!!!", "Nismo povezani sa bazom podataka!!!");
    }
    else
    {
        QSqlQuery upit;

        upit.prepare("SELECT KnjigaID, UDK, ISBN, Naziv FROM Knjiga ORDER BY KnjigaID ASC;");

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            QSqlQueryModel *model;
            model = new QSqlQueryModel();
            model->setQuery(upit);
            ui->tableView->setModel(model);
        }
    }
    baza.dbClose();
}

Knjige::~Knjige()
{
    delete ui;
}

void Knjige::on_pushButtonIzadji_clicked()
{
    this->close();
}

void Knjige::on_lineEditSifra_editingFinished()
{
    QString sifra = ui->lineEditSifra->text();

    Konekcija baza;
    if(!baza.dbOpen())
    {
        QMessageBox::critical(this, "Kriticno!!!", "Nismo povezani sa bazom podataka!!!");
    }
    else
    {
        QSqlQuery upit;

        upit.prepare("SELECT UDK, ISBN, Naziv FROM Knjiga WHERE KnjigaID = :sifra;");
        upit.bindValue(":sifra", sifra);

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            upit.next();
            if(upit.isValid())
            {
                ui->lineEditUDK->setText(upit.value(0).toString());
                ui->lineEditISBN->setText(upit.value(1).toString());
                ui->lineEditNaziv->setText(upit.value(2).toString());
            }
        }
    }
    baza.dbClose();
}

void Knjige::on_pushButtonObrisi_clicked()
{
    Konekcija baza;
    if(!baza.dbOpen())
    {
        QMessageBox::critical(this, "Kriticno!!!", "Nismo povezani sa bazom podataka!!!");
    }
    else
    {
        QString sifra = ui->lineEditSifra->text();

        QSqlQuery upit;

        upit.prepare("DELETE FROM Knjiga WHERE KnjigaID = :sifra;");
        upit.bindValue(":sifra", sifra);

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            QMessageBox::information(this, "Uspesno!!!", "Informacija o odabranoj knjizi je uspesno obrisana!!!");

            ui->lineEditSifra->clear();
            ui->lineEditISBN->clear();
            ui->lineEditUDK->clear();
            ui->lineEditNaziv->clear();

            upit.prepare("SELECT KnjigaID, UDK, ISBN, Naziv FROM Knjiga ORDER BY KnjigaID ASC;");

            if(!upit.exec())
            {
                QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
            }
            else
            {
                QSqlQueryModel *model;
                model = new QSqlQueryModel();
                model->setQuery(upit);
                ui->tableView->setModel(model);
            }
        }
    }
    baza.dbClose();
}

void Knjige::on_pushButtonIzmeni_clicked()
{
    Konekcija baza;
    if(!baza.dbOpen())
    {
        QMessageBox::critical(this, "Kriticno!!!", "Nismo povezani sa bazom podataka!!!");
    }
    else
    {
        QString sifra = ui->lineEditSifra->text();
        QString udk = ui->lineEditUDK->text();
        QString isbn = ui->lineEditNaziv->text();
        QString naziv = ui->lineEditNaziv->text();

        QSqlQuery upit;

        upit.prepare("UPDATE Knjiga SET UDK = :udk, ISBN = :isbn, Naziv = :naziv WHERE KnjigaID = :sifra;");
        upit.bindValue(":sifra", sifra);
        upit.bindValue(":udk", udk);
        upit.bindValue(":isbn", isbn);
        upit.bindValue(":naziv", naziv);

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            QMessageBox::information(this, "Uspesno!!!", "Informacija o odabranoj knjizi je uspesno izmenjena!!!");

            upit.prepare("SELECT KnjigaID, UDK, ISBN, Naziv FROM Knjiga ORDER BY KnjigaID ASC;");

            if(!upit.exec())
            {
                QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
            }
            else
            {
                QSqlQueryModel *model;
                model = new QSqlQueryModel();
                model->setQuery(upit);
                ui->tableView->setModel(model);
            }
        }
    }
    baza.dbClose();
}

void Knjige::on_pushButtonUpisi_clicked()
{
    Konekcija baza;
    if(!baza.dbOpen())
    {
        QMessageBox::critical(this, "Kriticno!!!", "Nismo povezani sa bazom podataka!!!");
    }
    else
    {
        QString udk = ui->lineEditUDK->text();
        QString isbn = ui->lineEditNaziv->text();
        QString naziv = ui->lineEditNaziv->text();

        QSqlQuery upit;

        upit.prepare("INSERT INTO Knjiga (UDK, ISBN, Naziv) VALUES (:udk, :isbn, :naziv);");
        upit.bindValue(":udk", udk);
        upit.bindValue(":isbn", isbn);
        upit.bindValue(":naziv", naziv);

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            QMessageBox::information(this, "Uspesno!!!", "Informacija o novoj knjizi je uspesno dodata!!!");

            ui->lineEditSifra->clear();
            ui->lineEditUDK->clear();
            ui->lineEditISBN->clear();
            ui->lineEditNaziv->clear();

            upit.prepare("SELECT KnjigaID, UDK, ISBN, Naziv FROM Knjiga ORDER BY KnjigaID ASC;");

            if(!upit.exec())
            {
                QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
            }
            else
            {
                QSqlQueryModel *model;
                model = new QSqlQueryModel();
                model->setQuery(upit);
                ui->tableView->setModel(model);
            }
        }
    }
    baza.dbClose();
}

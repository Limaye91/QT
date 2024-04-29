#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>
#include <QPdfWriter>
#include <QFileDialog>
#include <QPainter>
#include <QtPrintSupport/QPrinter>
#include "QTextDocumentWriter"
#include "QTextDocument"
#include "QDesktopServices"
#include <QTextCursor>
#include <QVector>
//#include "fold.h"
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    importdata();
    setComboBox2();
}
void Dialog::setComboBox2()
{
    // for(auto it :  mp1)
    // {
    //     for(auto it2: it)
    //      {
    //         ui->comboBoxSno->addItem(it.first);
    //     }

    // }


        ui->comboBoxSno->clear(); // Clear the combo box before populating it
        for(const auto& entry : mp1)
        {
            for(const auto& item : entry.second) // entry.second is the QList
            {
                QString serialNo = item.first; // Assuming serial number is the first element in the inner pair
                ui->comboBoxSno->addItem(serialNo);
            }
        }


}
Dialog::~Dialog()
{
    delete ui;
}

void Dialog::importdata()
{
    mp1.clear();
    mp1=f1->ExportData();
}

void Dialog::on_pushButton_clicked()
{
    QString serial = ui->comboBoxSno->currentText();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF"), "output.pdf", tr("PDF Files (*.pdf)"));

    if(fileName.isEmpty())
    {
        return;
    }

    QTextDocument document;
    QTextCursor cursor(&document);

    QTextImageFormat img; // Declare img variable here

    // Iterate through the map to find the device with the given serial number
    for(auto it = mp1.begin(); it != mp1.end(); ++it)
    {
        const QString& Device_name = it->first; // Device name
        const QVector<std::pair<QString, std::pair<QString, std::pair<QString, QString>>>>& deviceData = it->second;

        // Iterate through the vector associated with each device
        for(const auto& entry : deviceData)
        {
            if(entry.first == serial) // If serial number matches
            {
                // Access data associated with the serial number
                const QString& serialNumber = entry.first;
                const QString& assigned = entry.second.first;
                const QString& location = entry.second.second.first;
                const QString& imagePath = entry.second.second.second;

                // Insert data into QTextDocument
                cursor.insertText("Device Name : " + Device_name + "\n");
                cursor.insertText("Serial Number : " + serialNumber + "\n");
                cursor.insertText("Assigned : " + assigned + "\n");
                cursor.insertText("Location : " + location + "\n");

                // Insert image if imagePath is not empty
                if(!imagePath.isEmpty())
                {
                    img.setName(imagePath); // Set image name
                    cursor.insertImage(img);
                }
                else
                {
                    // Insert a default image
                    img.setName("/home/kasturi/Pictures/Screenshots/man.png");
                    cursor.insertImage(img);
                }

                // No need to continue searching, break out of the loop
                break;
            }
        }
    }

    // Create a QPdfWriter to write PDF content to the file
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setResolution(300);
    QPainter painter(&pdfWriter);
    document.drawContents(&painter);

    // Open the saved PDF file
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}

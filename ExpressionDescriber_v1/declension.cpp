#include "declension.h"







Declension::Declension()
{
}

Declension::~Declension()
{
}
/*!
 *  склоняет заданное слово в заданный падеж
 *  \param [in] word - слово которое сконяем, в именительном падеже
 *  \param [in] decl - нужный падеж
 *  \return - слово в новом падеже
 */
QString Declension::getDeclension(QString word, Declensions decl) {
    if(cache.contains(word)){
        return cache.value(word)[(int)decl - 1];
    }else{
    QUrl url = QString("http://ws3.morpher.ru/russian/declension?format=json&s=") + word;
    QNetworkRequest request(url);
    QNetworkAccessManager *mngr = new QNetworkAccessManager();
    QNetworkReply* reply = mngr->get(request);
    QEventLoop loop;
    connect(mngr, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray content = reply->readAll();
        QJsonDocument jsonDocument(QJsonDocument::fromJson(content));
        QJsonObject root = jsonDocument.object();
        QStringList list;
        list.append(root.value("Р").toString());
        list.append(root.value("Д").toString());
        list.append(root.value("В").toString());
        list.append(root.value("Т").toString());
        list.append(root.value("П").toString());
        cache.insert(word,list);
        return list[(int)decl - 1];

    }
    return NULL;
    }
}



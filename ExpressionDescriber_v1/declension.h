#ifndef DECLENSION_H
#define DECLENSION_H
#include <QObject>
#include <QHash>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QTextCodec>
#include <QJsonDocument>
#include <QJsonObject>


/*!
    \brief Класс, отвечающий за склонение элементов
*/
class Declension : QObject
{

public:
    /// Набор возможных состояний объекта
    enum Declensions {I,///< Именительный
                      R,///< Родительный
                      D,///< Дательный
                      V,///< Винительный
                      T,///< Творительный
                      P///< Предложный
                     };

    Declension();
    QHash<QString, QStringList> cache;///< Кэш запросов склонений
    /*!
     *  склоняет заданное слово в заданный падеж
     *  \param [in] word - слово которое сконяем, в именительном падеже
     *  \param [in] decl - нужный падеж
     *  \return - слово в новом падеже
     */
    QString getDeclension(QString word, Declensions decl,bool useDecl);
    ~Declension();

};

#endif // DECLENSION_H

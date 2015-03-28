#ifndef CG_PIECEIMAGE_H
#define CG_PIECEIMAGE_H

#include <QObject>
#include <QPixmap>
#include <QDebug>
#include <QString>
#include <QQuickImageProvider>

class CG_PieceImage : public QQuickImageProvider
{

public:
    CG_PieceImage(QString filepath);
    ~CG_PieceImage();

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);
private:
    QPixmap  m_piecesSheet;
};

#endif // CG_PIECEIMAGE_H

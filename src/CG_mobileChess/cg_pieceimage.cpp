#include "cg_pieceimage.h"
#include <QDebug>
CG_PieceImage::CG_PieceImage(QString filepath)
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
    m_piecesSheet = QPixmap(filepath);

    if(m_piecesSheet.isNull())
    {
        qDebug() << "Failed to load pieces sprite sheet!";
    }
}

CG_PieceImage::~CG_PieceImage()
{
    m_piecesSheet = QPixmap();
}

QPixmap CG_PieceImage::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int frameNumber = id.toInt();
    qDebug() << frameNumber;
    qDebug() << id;
    //id.right(id.length() - id.lastIndexOf('/')).toInt();
    //id.toInt()

    QPixmap pixmap = m_piecesSheet.copy(40 * frameNumber,0,40,40);
    if(!pixmap.isNull())
        qDebug() << "Not null!";
    return pixmap;
}

#include "CG_pieceImage.h"
#include <QDebug>
CG_PieceImage::CG_PieceImage(QString filepath)
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
    // Set tile sheet to filepath that we pass in from resources
    // (i.e. images/cg_pieces.png)
    m_piecesSheet = QPixmap(filepath);

    // Make sure tilesheet is not null
    if(m_piecesSheet.isNull())
    {
        qDebug() << "Failed to load pieces sprite sheet!";
    }
}

CG_PieceImage::~CG_PieceImage()
{
    m_piecesSheet = QPixmap();
}

// TODO -- Get rid of magic numbers
QPixmap CG_PieceImage::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    int frameNumber = id.toInt();

    qDebug() << frameNumber;
    qDebug() << id;

    QPixmap pixmap = m_piecesSheet.copy(40 * frameNumber,0,40,40);

    if(!pixmap.isNull())
        qDebug() << "Not null!";

    return pixmap;
}

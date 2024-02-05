#include "renderarea.h"
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>


RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent), mShape(Astroid)
{
    this->mBackgroundColor = Qt::black;

    mPen.setWidth(2);
    mPen.setColor(Qt::white);

    on_shape_changed();
}


QSize RenderArea::minimumSizeHint() const
{
    return QSize(400, 400);
}


QSize RenderArea::sizeHint() const
{
    return QSize(400, 400);
}

QPointF RenderArea::compute (float t) {
    switch (mShape) {
    case Astroid:
        return compute_asteroid(t);
        break;

    case Cloud:
        return compute_cloud(t);
        break;

    case HuygensCycloid:
        return compute_huygens(t);
        break;

    case HypoCycloid:
        return compute_hypo(t);
        break;

    case Heart:
        return compute_heart(t);
        break;

    case Fancy:
        return compute_fancy(t);
        break;

    case Starfish:
        return compute_starfish(t);
        break;

    default:
        break;
    }

    return QPointF(0, 0);
}


void RenderArea::paintEvent (QPaintEvent * event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QBrush backgroundBrush(mBackgroundColor);
    painter.setBrush(backgroundBrush);

    painter.setPen(Qt::NoPen);

    // drowing area
    painter.drawRect(this->rect());

    if (this->mShape == FMondelbrot)
    {
        paintFractalMondelbrot(painter);
    }
    else if (this->mShape == FJulia)
    {
        paintFractalJulia(painter);
    }
    else if (this->mShape == FSierpinski)
    {
        paintFSierpinski(painter);
    }
    else if (this->mShape == FTree)
    {
        paintFTree(painter);
    }
    else if (this->mShape == FDragon)
    {
        paintFDragon(painter);
    }
    else
    {
        painter.setPen(mPen);
        QPoint center = this->rect().center();

        QPoint prevPixel;
        float step = mIntervalLenght / mStepCount;

        for (float t = 0; t <= mIntervalLenght; t += step) {

            QPointF point = (t == mIntervalLenght) ? compute (mIntervalLenght) : compute (t);
            QPoint pixel;

            pixel.setX(point.x() * mScale + center.x());
            pixel.setY(point.y() * mScale + center.y());

            if (t < mIntervalLenght)
                painter.drawPoint(pixel);

            if (!prevPixel.isNull())
                painter.drawLine(pixel, prevPixel);
            prevPixel = pixel;
        }

    }
}


void RenderArea::on_shape_changed ()
{
    switch (mShape) {
    case Astroid:
        mScale = 90;
        mIntervalLenght = 2 * M_PI;
        mStepCount = 256;
        break;

    case Cloud:
        mScale = 10;
        mIntervalLenght = 28 * M_PI;
        mStepCount = 128;
        break;

    case HuygensCycloid:
        mScale = 11;
        mIntervalLenght = 4 * M_PI;
        mStepCount = 256;
        break;

    case HypoCycloid:
        mScale = 40;
        mIntervalLenght = 2 * M_PI;
        mStepCount = 256;
        break;

    case Heart:
        mScale = 8;
        mIntervalLenght = 2 * M_PI;
        mStepCount = 256;
        break;

    case Fancy:
        mScale = 10;
        mIntervalLenght = 12 * M_PI;
        mStepCount = 512;
        break;

    case Starfish:
        mScale = 25;
        mIntervalLenght = 6 * M_PI;
        mStepCount = 256;
        break;

    case FMondelbrot:
        mScale = 6;
        mIntervalLenght = 200;
        mStepCount = 200;
        break;

    case FJulia:
        mScale = 6;
        mIntervalLenght = 200;
        mStepCount = 200;
        break;

    case FSierpinski:
        mScale = 180;
        mIntervalLenght = 200;
        mStepCount = 200;
        break;

    case FTree:
        mScale = 124;
        mIntervalLenght = 200;
        mStepCount = 256;
        break;

    case FDragon:
        mScale = 120;
        mIntervalLenght = 200;
        mStepCount = 600;
        break;

    default:
        break;
    }
}


QPointF RenderArea::compute_asteroid (float t)
{
    float x = 2 * pow(cos(t), 3);
    float y = 2 * pow(sin(t), 3);

    return QPointF(x, y);
}


QPointF RenderArea::compute_cloud (float t)
{
    float a = 14;
    float b = 1;
    float x = (a + b) * cos(t * b / a) - b * cos (t * (a + b ) / a);
    float y = (a + b) * sin(t * b / a) - b * sin (t * (a + b ) / a);
    return QPointF(x, y);
}


QPointF RenderArea::compute_huygens (float t)
{
    float x = 4 * (3 * cos(t) - cos(3 * t));
    float y = 4 * (3 * sin(t) - sin(3 * t));
    return QPointF(x, y);
}


QPointF RenderArea::compute_hypo (float t)
{
    float x = 1.5 * (2 * cos(t) + cos(2 * t));
    float y = 1.5 * (2 * sin(t) - sin(2 * t));
    return QPointF(x, y);
}


QPointF RenderArea::compute_heart (float t)
{
    float x = 16 * pow(sin(t), 3);
    float y = -(13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t));
    return QPointF(x, y);
}


QPointF RenderArea::compute_fancy (float t)
{
    float a = 11.0f;
    float b = 6.0f;
    float x = a * cos(t) - b * cos(a / b * t);
    float y = a * sin(t) - b * sin(a / b * t);
    return QPointF(x, y);
}


QPointF RenderArea::compute_starfish (float t)
{
    float R = 5.0f;
    float r = 3.0f;
    float d = 5.0f;
    float a = (R - r);
    float x = a * cos(t) + d * cos(t * (a / r));
    float y = a * sin(t) - d * sin(t * (a / r));
    return QPointF(x, y);
}


bool RenderArea::isMandelbrotMember(float re, float im)
{
    int maxIterations = static_cast<int>(mStepCount);

    float x = 0.0;
    float y = 0.0;

    for (int i = 0; i < maxIterations; ++i)
    {
        float xTmp = x * x - y * y + re;
        float yTmp = 2 * x * y + im;

        x = xTmp;
        y = yTmp;

        if (x * x + y * y > 4.0)
        {
            return false;
        }
    }
    return true;
}


void RenderArea::paintFractalMondelbrot(QPainter &painter)
{
    float scaleFactor = mScale / 1000;
    float offsetX = 0.0;
    float offsetY = 0.0;

    int pointsX = this->width() + 80;
    int pointsY = this->height();

    for (int x = 0; x < pointsX; ++x)
    {
        for (int y = 0; y < pointsY; ++y)
        {
            float re = (x - pointsX / 2.0) * scaleFactor + offsetX;
            float im = (y - pointsY / 2.0) * scaleFactor + offsetY;

            QColor color = isMandelbrotMember(re, im) ? mPen.color() : mBackgroundColor;

            painter.setPen(color);
            painter.drawPoint(x, y);
        }
    }
}


void RenderArea::paintFractalJulia(QPainter &painter)
{

    float scaleFactor = mScale / 1000;
    float offsetX = 0.0;
    float offsetY = 0.0;

    float cRe = -0.7;
    float cIm = 0.27015;

    int pointsX = this->width();
    int pointsY = this->height();

    for (int x = 0; x < pointsX; ++x)
    {
        for (int y = 0; y < pointsY; ++y)
        {
            float re = (x - pointsX / 2.0) * scaleFactor + offsetX;
            float im = (y - pointsY / 2.0) * scaleFactor + offsetY;

            QColor color = isJuliaMember(re, im, cRe, cIm) ? mPen.color() : mBackgroundColor;

            painter.setPen(color);
            painter.drawPoint(x, y);
        }
    }
}


bool RenderArea::isJuliaMember(float re, float im, float cRe, float cIm)
{
    int maxIterations = static_cast<int>(mStepCount);

    float x = re;
    float y = im;

    for (int i = 0; i < maxIterations; ++i)
    {
        float xTmp = x * x - y * y + cRe;
        float yTmp = 2 * x * y + cIm;

        x = xTmp;
        y = yTmp;

        if (x * x + y * y > 4.0)
        {
            return false;
        }
    }
    return true;
}


void RenderArea::paintFSierpinski(QPainter &painter)
{
    float k = mScale;
    float dx = -20;
    float dy = 40;

    QPointF p1(k + dx, k * 2 + dy);
    QPointF p2(k * 3 + dx, k * 2 + dy);
    QPointF p3(k * 2 + dx, 0 + dy);

    int depth = mStepCount / 40;
    paintSierpinskiRecursively(painter, p1, p2, p3, depth);

    painter.setPen(mPen.color());
    painter.drawLine(p1, p2);
    painter.drawLine(p2, p3);
    painter.drawLine(p3, p1);
}


void RenderArea::paintSierpinskiRecursively(QPainter &painter, const QPointF &p1, const QPointF &p2, const QPointF &p3, int depth)
{
    if (depth == 0)
    {
        painter.setPen(mPen.color());
        painter.drawLine(p1, p2);
        painter.drawLine(p2, p3);
        painter.drawLine(p3, p1);
    }
    else
    {
        QPointF mid1 = (p1 + p2) / 2.0;
        QPointF mid2 = (p2 + p3) / 2.0;
        QPointF mid3 = (p3 + p1) / 2.0;

        paintSierpinskiRecursively(painter, p1, mid1, mid3, depth - 1);
        paintSierpinskiRecursively(painter, mid1, p2, mid2, depth - 1);
        paintSierpinskiRecursively(painter, mid3, mid2, p3, depth - 1);
    }
}


void RenderArea::paintFTree(QPainter &painter)
{
    QPoint center = this->rect().center();

    QPointF startPoint(center.x(), 500);
    float initialAngle = -90.0;

    paintTreeRecursively(painter, startPoint, mScale, initialAngle, mStepCount / 32);
}


void RenderArea::paintTreeRecursively(QPainter &painter, const QPointF &point, float length, float angle, int depth)
{
    if (depth == 0)
        return;

    QPointF endPoint(point.x() + length * cos(qDegreesToRadians(angle)),
                     point.y() + length * sin(qDegreesToRadians(angle)));

    painter.setPen(mPen.color());
    painter.drawLine(point, endPoint);

    paintTreeRecursively(painter, endPoint, length * 0.7, angle - 30, depth - 1);
    paintTreeRecursively(painter, endPoint, length * 0.7, angle + 30, depth - 1);
}


void RenderArea::paintFDragon(QPainter &painter)
{
    float k = mScale;
    float dx = 100;
    float dy = 50;

    QPointF p1(k + dx, k * 2 + dy);
    QPointF p2(k * 3 + dx, k * 2 + dy);

    int depth = mStepCount / 60;
    paintDragonRecursively(painter, p1, p2, depth);

}


void RenderArea::paintDragonRecursively(QPainter &painter, const QPointF &p1, const QPointF &p2, int depth)

{
    if (depth == 0)
    {
        painter.setPen(mPen.color());
        painter.drawLine(p1, p2);
    }
    else
    {
        QPointF mid = (p1 + p2) / 2.0;
        QPointF delta = p2 - p1;
        QPointF normal(delta.y(), -delta.x());

        QPointF p3 = mid + normal / 2.0;

        paintDragonRecursively(painter, p2, p3, depth - 1);
        paintDragonRecursively(painter, p1, p3, depth - 1);
    }
}

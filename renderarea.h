#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QMainWindow>
#include <QColor>
#include <QPen>
#include <QPainter>


class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = nullptr);

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

    enum ShapeType { Astroid, Cloud, HuygensCycloid, HypoCycloid, Heart, Fancy,
                     Starfish, FMondelbrot, FJulia, FSierpinski, FTree, FDragon };

    void setBackgroundColor (QColor color) {mBackgroundColor = color; }
    QColor getBackgroundColor() const { return mBackgroundColor; }

    void setShapeColor (QColor color) { mPen.setColor(color); }
    QColor getShapeColor() const { return mPen.color(); }

    void setShape (ShapeType shape) { mShape = shape; on_shape_changed (); }
    ShapeType getShape() const { return mShape;}

    void setScale(float scale) { mScale = scale; repaint (); }
    float getScale() const { return mScale;}

    void setInterval(float interval) { mIntervalLenght = interval; repaint (); }
    float getInterval() const { return mIntervalLenght;}

    void setStepCount(int count) { mStepCount = count; repaint (); }
    int getStepCount() const {return mStepCount;}


protected:
    void paintEvent (QPaintEvent * event) Q_DECL_OVERRIDE;

    void paintFractalMondelbrot(QPainter &painter);
    void paintFractalJulia(QPainter &painter);
    void paintFSierpinski(QPainter &painter);
    void paintFTree(QPainter &painter);
    void paintFDragon(QPainter &painter);


signals:


private:
    void on_shape_changed ();
    QPointF compute (float t);
    QPointF compute_asteroid (float t);
    QPointF compute_cloud (float t);
    QPointF compute_huygens (float t);
    QPointF compute_hypo (float t);
    QPointF compute_heart (float t);
    QPointF compute_fancy (float t);
    QPointF compute_starfish (float t);

    bool isMandelbrotMember(float re, float im);
    bool isJuliaMember(float re, float im, float cRe, float cIm);
    void paintSierpinskiRecursively(QPainter &painter, const QPointF &p1, const QPointF &p2, const QPointF &p3, int depth);
    void paintTreeRecursively(QPainter &painter, const QPointF &point, float length, float angle, int depth);
    void paintDragonRecursively(QPainter &painter, const QPointF &p1, const QPointF &p2, int depth);


private:
    QColor mBackgroundColor;
    ShapeType mShape;
    QPen mPen;

    float mIntervalLenght;
    float mScale;
    float mStep;
    int mStepCount;
};

#endif // RENDERAREA_H

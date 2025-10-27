#ifndef DISCO_H
#define DISCO_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

class Disco : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    Disco(int ancho, int alto, int tamano, QGraphicsItem *parent = nullptr);
    
    int obtenerTamano() const { return tamano; }
    void setSeleccionado(bool seleccionado);
    bool estaSeleccionado() const { return seleccionado; }
    
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;      // ✨ Detectar cuando se presiona
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;    // ✨ Detectar cuando se suelta
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;  // ✨ Detectar cambios

signals:
    void discoPresionado(Disco *disco);       // ✨ Señal cuando se presiona
    void discoSoltado(Disco *disco, QPointF posicion);  // ✨ Señal cuando se suelta

private:
    int tamano;
    bool seleccionado;
    bool hover;
    QColor colorBase;
    QColor colorSeleccionado;
    QColor colorHover;
};

#endif // DISCO_H

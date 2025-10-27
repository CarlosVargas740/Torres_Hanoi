#ifndef TORRE_H
#define TORRE_H

#include <QGraphicsRectItem>
#include <QObject>
#include <vector>
#include "disco.h"

class Torre : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    Torre(int x, int y, int indice, QGraphicsItem *parent = nullptr);
    
    void agregarDisco(Disco *disco);
    Disco* quitarDisco();
    Disco* obtenerDiscoSuperior() const;
    bool estaVacia() const { return discos.empty(); }
    std::vector<Disco*> obtenerDiscos() const { return discos; }
    void limpiar() { discos.clear(); }
    void setTemaOscuro(bool oscuro);
    
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    std::vector<Disco*> discos;
    int posX;
    int posY;
    int indice;
    bool hover;
    bool temaOscuro;
    
    void actualizarPosicionDiscos();

public:  // ✨ Hacer público para poder acceder desde MainWindow
    QPointF calcularPosicionDisco(int posicion);
};

#endif // TORRE_H

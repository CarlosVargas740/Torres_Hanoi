#include "torre.h"
#include <QPainter>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QGraphicsDropShadowEffect>
#include <QLinearGradient>
#include <QLineF>

Torre::Torre(int x, int y, int indice, QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
    , posX(x)
    , posY(y)
    , indice(indice)
    , hover(false)
    , temaOscuro(false)
{
    // Base de la torre MEJORADA - MÁS GRANDE
    int anchoBase = 280;  // ✨ Base más ancha
    int altoBase = 30;     // ✨ Base más gruesa
    setRect(x - anchoBase/2, y, anchoBase, altoBase);
    
    setAcceptHoverEvents(true);
    setZValue(-1);
    
    // Efecto de sombra MEJORADO
    QGraphicsDropShadowEffect *sombra = new QGraphicsDropShadowEffect();
    sombra->setBlurRadius(20);  // ✨ Sombra más difusa
    sombra->setColor(QColor(0, 0, 0, 160));  // ✨ Más oscura
    sombra->setOffset(0, 5);  // ✨ Más separada
    setGraphicsEffect(sombra);
}

void Torre::agregarDisco(Disco *disco)
{
    discos.push_back(disco);
    actualizarPosicionDiscos();
}

Disco* Torre::quitarDisco()
{
    if (discos.empty()) return nullptr;
    
    Disco *disco = discos.back();
    discos.pop_back();
    actualizarPosicionDiscos();
    return disco;
}

Disco* Torre::obtenerDiscoSuperior() const
{
    if (discos.empty()) return nullptr;
    return discos.back();
}

void Torre::actualizarPosicionDiscos()
{
    // ✨ Animación suave y estable con rebote
    for (size_t i = 0; i < discos.size(); i++) {
        QPointF nuevaPos = calcularPosicionDisco(i);
        
        // Solo animar si la posición cambió significativamente
        qreal distancia = QLineF(discos[i]->pos(), nuevaPos).length();
        if (distancia > 5) {  // Más de 5 píxeles
            QPropertyAnimation *animacion = new QPropertyAnimation(discos[i], "pos");
            animacion->setDuration(400);
            animacion->setStartValue(discos[i]->pos());
            animacion->setEndValue(nuevaPos);
            animacion->setEasingCurve(QEasingCurve::OutBounce);
            animacion->start(QAbstractAnimation::DeleteWhenStopped);
        } else {
            // Movimiento instantáneo para cambios pequeños
            discos[i]->setPos(nuevaPos);
        }
    }
}

QPointF Torre::calcularPosicionDisco(int posicion)
{
    int altoDisco = 35;  // ✨ ACTUALIZADO para coincidir con el nuevo tamaño de discos
    int y = posY - (posicion + 1) * altoDisco;
    return QPointF(posX, y);
}

void Torre::setTemaOscuro(bool oscuro)
{
    temaOscuro = oscuro;
    update();
}

void Torre::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    
    painter->setRenderHint(QPainter::Antialiasing);
    
    QRectF r = rect();
    
    // Color de la base
    QColor colorBase = temaOscuro ? QColor(127, 140, 141) : QColor(52, 73, 94);
    QColor colorPoste = temaOscuro ? QColor(189, 195, 199) : QColor(149, 165, 166);
    
    if (hover) {
        colorBase = colorBase.lighter(120);
        colorPoste = colorPoste.lighter(120);
    }
    
    // Gradiente para la base
    QLinearGradient gradienteBase(r.topLeft(), r.bottomLeft());
    gradienteBase.setColorAt(0, colorBase.lighter(120));
    gradienteBase.setColorAt(0.5, colorBase);
    gradienteBase.setColorAt(1, colorBase.darker(120));
    
    painter->setBrush(gradienteBase);
    painter->setPen(QPen(colorBase.darker(150), 2));
    painter->drawRoundedRect(r, 5, 5);
    
    // Poste vertical MEJORADO - MÁS ALTO Y ANCHO
    int anchoPoste = 25;  // ✨ Poste más ancho
    int altoPoste = 450;  // ✨ Poste más alto
    QRectF poste(posX - anchoPoste/2, posY - altoPoste, anchoPoste, altoPoste);
    
    // Gradiente 3D mejorado para el poste
    QLinearGradient gradientePoste(poste.topLeft(), poste.topRight());
    gradientePoste.setColorAt(0, QColor(20, 20, 30));      // Negro azulado
    gradientePoste.setColorAt(0.4, colorPoste.lighter(110)); // Brillo
    gradientePoste.setColorAt(0.6, colorPoste);            // Color base
    gradientePoste.setColorAt(1, colorPoste.darker(130));  // Sombra
    
    painter->setBrush(gradientePoste);
    painter->setPen(QPen(QColor(0, 0, 0, 150), 2));  // Borde oscuro
    painter->drawRoundedRect(poste, 8, 8);  // ✨ Bordes más redondeados
    
    // Brillo MEJORADO en el poste - efecto metálico
    QLinearGradient brillo(poste.topLeft(), poste.topRight());
    brillo.setColorAt(0, QColor(255, 255, 255, 0));
    brillo.setColorAt(0.25, QColor(255, 255, 255, 90));  // ✨ Más brillante
    brillo.setColorAt(0.5, QColor(255, 255, 255, 120));  // ✨ Centro brillante
    brillo.setColorAt(0.75, QColor(255, 255, 255, 90));
    brillo.setColorAt(1, QColor(255, 255, 255, 0));
    
    painter->setBrush(brillo);
    painter->setPen(Qt::NoPen);
    QRectF areabrillo = poste.adjusted(3, 3, -poste.width() * 0.65, -3);
    painter->drawRoundedRect(areabrillo, 5, 5);
    
    // Etiqueta de la torre
    painter->setPen(temaOscuro ? Qt::white : Qt::white);
    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(12);
    painter->setFont(font);
    
    QChar letra = QChar('A' + indice);
    QRectF textoRect = r.adjusted(0, 5, 0, 0);
    painter->drawText(textoRect, Qt::AlignCenter, QString(letra));
    
    // Indicador de hover
    if (hover) {
        painter->setPen(QPen(QColor(52, 152, 219), 3, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
        QRectF bordeHover = r.adjusted(-5, -5, 5, 5);
        painter->drawRoundedRect(bordeHover, 8, 8);
    }
}

void Torre::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    hover = true;
    update();
}

void Torre::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    hover = false;
    update();
}

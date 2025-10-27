#include "disco.h"
#include <QGraphicsDropShadowEffect>
#include <QLinearGradient>
#include <QRadialGradient>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QPropertyAnimation>

Disco::Disco(int ancho, int alto, int tamano, QGraphicsItem *parent)
    : QGraphicsRectItem(parent)
    , tamano(tamano)
    , seleccionado(false)
    , hover(false)
{
    setRect(-ancho/2, -alto/2, ancho, alto);
    
    // Colores vibrantes según el tamaño
    QList<QColor> colores = {
        QColor(231, 76, 60),   // Rojo
        QColor(52, 152, 219),  // Azul
        QColor(46, 204, 113),  // Verde
        QColor(241, 196, 15),  // Amarillo
        QColor(155, 89, 182),  // Púrpura
        QColor(230, 126, 34),  // Naranja
        QColor(26, 188, 156),  // Turquesa
        QColor(236, 240, 241)  // Gris claro
    };
    
    colorBase = colores[(tamano - 1) % colores.size()];
    colorSeleccionado = colorBase.lighter(120);
    colorHover = colorBase.lighter(110);
    
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);        // ✨ Permite mover el disco
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);  // ✨ Notifica cambios de posición
    
    // Efecto de sombra
    QGraphicsDropShadowEffect *sombra = new QGraphicsDropShadowEffect();
    sombra->setBlurRadius(15);
    sombra->setColor(QColor(0, 0, 0, 160));
    sombra->setOffset(0, 5);
    setGraphicsEffect(sombra);
    
    setZValue(tamano);
}

void Disco::setSeleccionado(bool sel)
{
    seleccionado = sel;
    update();
}

void Disco::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    
    painter->setRenderHint(QPainter::Antialiasing);
    
    QRectF r = rect();
    
    // Determinar color actual
    QColor colorActual = colorBase;
    if (seleccionado) {
        colorActual = colorSeleccionado;
    } else if (hover) {
        colorActual = colorHover;
    }
    
    // Gradiente radial MEJORADO para efecto 3D más realista
    QRadialGradient gradiente(r.center().x(), r.center().y() - r.height() * 0.3, r.width() / 1.5);
    gradiente.setColorAt(0, QColor(255, 255, 255, 200));  // ✨ Brillo central blanco
    gradiente.setColorAt(0.3, colorActual.lighter(150));   // ✨ Transición brillante
    gradiente.setColorAt(0.6, colorActual);                // Color base
    gradiente.setColorAt(0.9, colorActual.darker(140));    // ✨ Sombra más pronunciada
    gradiente.setColorAt(1, colorActual.darker(180));      // ✨ Borde oscuro
    
    painter->setBrush(gradiente);
    
    // Borde MEJORADO con efecto de profundidad
    if (seleccionado) {
        // Borde dorado brillante para selección
        painter->setPen(QPen(QColor(255, 215, 0), 4, Qt::SolidLine));
    } else if (hover) {
        // Borde cian brillante para hover
        painter->setPen(QPen(QColor(0, 255, 255), 3, Qt::SolidLine));
    } else {
        // Borde normal con sombra
        painter->setPen(QPen(colorActual.darker(180), 2));
    }
    
    // Dibujar rectángulo con bordes redondeados
    painter->drawRoundedRect(r, 8, 8);
    
    // Efecto de brillo superior
    QLinearGradient brilloSuperior(r.topLeft(), r.bottomLeft());
    brilloSuperior.setColorAt(0, QColor(255, 255, 255, 100));
    brilloSuperior.setColorAt(0.3, QColor(255, 255, 255, 40));
    brilloSuperior.setColorAt(1, QColor(255, 255, 255, 0));
    
    painter->setBrush(brilloSuperior);
    painter->setPen(Qt::NoPen);
    painter->drawRoundedRect(r.adjusted(2, 2, -2, r.height() * 0.3), 6, 6);
    
    // Texto con el número del disco
    if (seleccionado) {
        painter->setPen(Qt::white);
        QFont font = painter->font();
        font.setBold(true);
        font.setPointSize(10);
        painter->setFont(font);
        painter->drawText(r, Qt::AlignCenter, QString::number(tamano));
    }
}

void Disco::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    hover = true;
    
    // ✨ Animación de pulso al hacer hover
    QPropertyAnimation *animPulso = new QPropertyAnimation(this, "scale");
    animPulso->setDuration(200);
    animPulso->setStartValue(scale());
    animPulso->setEndValue(1.1);
    animPulso->setEasingCurve(QEasingCurve::OutQuad);
    animPulso->start(QAbstractAnimation::DeleteWhenStopped);
    
    update();
}

void Disco::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    hover = false;
    
    // ✨ Restaurar escala suavemente
    QPropertyAnimation *animRestaurar = new QPropertyAnimation(this, "scale");
    animRestaurar->setDuration(200);
    animRestaurar->setStartValue(scale());
    animRestaurar->setEndValue(1.0);
    animRestaurar->setEasingCurve(QEasingCurve::InQuad);
    animRestaurar->start(QAbstractAnimation::DeleteWhenStopped);
    
    update();
}

void Disco::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // Emitir señal cuando se presiona el disco
    emit discoPresionado(this);
    setSeleccionado(true);
    setCursor(Qt::ClosedHandCursor);  // ✨ Cambiar cursor a mano cerrada
    QGraphicsRectItem::mousePressEvent(event);
}

void Disco::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // Emitir señal cuando se suelta el disco
    emit discoSoltado(this, scenePos());
    setCursor(Qt::OpenHandCursor);  // ✨ Cambiar cursor a mano abierta
    QGraphicsRectItem::mouseReleaseEvent(event);
}

QVariant Disco::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        // Mientras se arrastra, mantener seleccionado
        setSeleccionado(true);
    }
    return QGraphicsRectItem::itemChange(change, value);
}

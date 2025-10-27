#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QSlider>
#include <QStackedWidget>
#include <QGraphicsTextItem>
#include <QGraphicsEllipseItem>
#include <QProgressBar>
#include <vector>
#include <stack>
#include "disco.h"
#include "torre.h"
#include "soundmanager.h"  // ✨ NUEVO: Sistema de sonidos

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // ✨ ENUM público para temas
    enum TemaVisual {
        TEMA_DARK_MODERN,
        TEMA_LIGHT_ELEGANT,
        TEMA_NEON_CYBERPUNK,
        TEMA_GLASSMORPHISM,
        TEMA_SUNSET_GRADIENT
    };
    
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void iniciarJuego();
    void resolverAutomatico();
    void resolverDesdeAqui();
    void reiniciar();
    void siguienteMovimiento();
    void cambiarVelocidad(int valor);
    void cambiarTema();
    void mostrarPantallaJuego();
    void mostrarAcercaDe();
    void animarParticulas();
    void mostrarMensajeFlotante(QString mensaje, QColor color);
    void reproducirSonidoMovimiento();
    void mostrarHistorial();
    void guardarPartida();
    void cargarPartida();
    void mostrarEstadisticas();
    void cambiarDificultad();
    void activarModoZen();
    void mostrarTutorial();
    void onDiscoPresionado(Disco *disco);   // ✨ Slot para cuando se presiona un disco
    void onDiscoSoltado(Disco *disco, QPointF posicion);  // ✨ Slot para cuando se suelta un disco

private:
    // Interfaz principal
    QStackedWidget *stackedWidget;
    QWidget *pantallaInicio;
    QWidget *pantallaJuego;
    
    // Vista gráfica
    QGraphicsView *vistaGrafica;
    QGraphicsScene *escena;
    QGraphicsScene *escenaInicio;
    
    // Controles pantalla de inicio
    QPushButton *btnComenzar;
    QPushButton *btnAcercaDe;
    QPushButton *btnSalir;
    
    // Controles pantalla de juego
    QPushButton *btnIniciar;
    QPushButton *btnResolver;
    QPushButton *btnResolverDesde;
    QPushButton *btnReiniciar;
    QPushButton *btnTema;
    QPushButton *btnVolver;
    QSpinBox *spinDiscos;
    QLabel *lblMovimientos;
    QLabel *lblMinMovimientos;
    QLabel *lblTiempo;
    QLabel *lblEficiencia;
    QSlider *sliderVelocidad;
    QLabel *lblVelocidad;
    QTimer *timer;
    QTimer *timerJuego;
    QTimer *timerParticulas;
    
    // Efectos visuales
    std::vector<QGraphicsEllipseItem*> particulas;
    QGraphicsTextItem *mensajeFlotante;
    
    // Nuevos controles profesionales
    QPushButton *btnHistorial;
    QPushButton *btnGuardar;
    QPushButton *btnCargar;
    QPushButton *btnEstadisticas;
    QPushButton *btnTutorial;
    QProgressBar *barraProgreso;
    QLabel *lblRecord;
    QLabel *lblNivel;
    
    // Efectos de sonido visual
    QTimer *timerEfectos;
    std::vector<QGraphicsEllipseItem*> efectosExplosion;
    
    // ✨ NUEVO: Sistema de sonidos profesional
    SoundManager *soundManager;
    QPushButton *btnSonido;  // Botón para activar/desactivar sonido
    QSlider *sliderVolumen;  // Control de volumen
    
    // Lógica del juego
    std::vector<Torre*> torres;
    std::vector<Disco*> discos;
    std::vector<std::pair<int, int>> movimientos; // Para resolución automática
    std::vector<std::pair<int, int>> historialMovimientos; // Historial del jugador
    int movimientoActual;
    int numDiscos;
    int contadorMovimientos;
    int tiempoTranscurrido;
    int velocidadAnimacion;
    bool juegoIniciado;
    bool resolviendoAutomatico;
    bool temaOscuro;
    bool modoZen;
    int recordMovimientos;
    int partidasJugadas;
    int partidasGanadas;
    
    // ✨ NUEVOS: Sistema de temas épicos
    TemaVisual temaActual;
    QTimer *timerAnimacionTema;
    
    // Disco seleccionado para juego manual
    Disco *discoSeleccionado;
    int torreOrigen;
    
    // Variables para drag and drop ✨
    Disco *discoArrastrado;
    QPointF posicionOriginal;
    int torreOrigenDrag;
    
    // Métodos auxiliares
    void configurarInterfaz();
    void configurarPantallaInicio();
    void configurarPantallaJuego();
    void crearTorres();
    void crearDiscos(int cantidad);
    void limpiarDiscos();
    void calcularSolucion(int n, int origen, int destino, int auxiliar);
    void moverDisco(int desde, int hacia, bool animado = true);
    bool verificarMovimientoValido(int desde, int hacia);
    bool juegoCompletado();
    void actualizarEstadisticas();
    void aplicarTema();
    void aplicarTemaInicio();
    void aplicarTemaModerno(TemaVisual tema);  // ✨ NUEVO: Aplicar temas épicos
    void animarTransicionTema();  // ✨ NUEVO: Transición suave entre temas
    QString obtenerEstiloBoton(TemaVisual tema);  // ✨ NUEVO: Estilos de botones
    QString obtenerEstiloFondo(TemaVisual tema);  // ✨ NUEVO: Estilos de fondo
    void actualizarColoresTema(TemaVisual tema);  // ✨ NUEVO: Actualizar colores de torres/discos
    void crearEfectoParticulas();
    void mostrarDialogoVictoria();
    void animarTitulo();
    void crearEfectoExplosion(QPointF posicion, QColor color);
    void reproducirEfectoVisual(QString tipo);
    void actualizarProgreso();
    void guardarEstadisticas();
    void cargarEstadisticas();
    void animarMovimiento(Disco *disco, QPointF inicio, QPointF fin);
    void animarMovimientoEpico(Disco *disco, int desde, int hacia);  // ✨ Nueva animación épica
    QString obtenerMensajeMotivacional();
    QString obtenerTipMovimiento();
    void mostrarCelebracion();
    std::vector<std::pair<int, int>> obtenerEstadoActual();
    void resolverDesdeEstado(std::vector<std::stack<int>> estado);
    
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H

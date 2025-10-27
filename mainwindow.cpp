#include "mainwindow.h"
#include <QMouseEvent>
#include <QResizeEvent>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsOpacityEffect>  // ✨ Para animaciones de transición
#include <QPalette>
#include <QGroupBox>
#include <QProgressBar>
#include <QKeyEvent>
#include <QDataStream>
#include <QFile>
#include <QRandomGenerator>
#include <algorithm>
#include <cmath>
#include <functional>  // ✨ Para std::function

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , numDiscos(3)
    , contadorMovimientos(0)
    , tiempoTranscurrido(0)
    , velocidadAnimacion(300)
    , juegoIniciado(false)
    , resolviendoAutomatico(false)
    , temaOscuro(false)
    , discoSeleccionado(nullptr)
    , torreOrigen(-1)
    , movimientoActual(0)
    , modoZen(false)
    , partidasJugadas(0)
    , partidasGanadas(0)
    , recordMovimientos(999999)
    , discoArrastrado(nullptr)      // ✨ Inicializar drag and drop
    , torreOrigenDrag(-1)
    , soundManager(new SoundManager(this))  // ✨ NUEVO: Inicializar sistema de sonidos
    , temaActual(TEMA_DARK_MODERN)  // ✨ NUEVO: Tema inicial
{
    historialMovimientos.clear();
    cargarEstadisticas();
    configurarInterfaz();
    aplicarTema();  // Usar la función simple primero
}

MainWindow::~MainWindow()
{
}

void MainWindow::configurarInterfaz()
{
    // Widget central
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    // Layout principal
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(centralWidget);
    
    // Título
    QLabel *titulo = new QLabel("🗼 TORRES DE HANOI 🗼", this);
    QFont fuenteTitulo;
    fuenteTitulo.setPointSize(24);
    fuenteTitulo.setBold(true);
    titulo->setFont(fuenteTitulo);
    titulo->setAlignment(Qt::AlignCenter);
    titulo->setStyleSheet("color: #2c3e50; margin: 10px;");
    layoutPrincipal->addWidget(titulo);
    
    // Panel de control superior
    QHBoxLayout *layoutControl = new QHBoxLayout();
    
    // Grupo de configuración
    QGroupBox *grupoConfig = new QGroupBox("Configuración", this);
    QHBoxLayout *layoutConfig = new QHBoxLayout(grupoConfig);
    
    QLabel *lblDiscos = new QLabel("Número de discos:", this);
    spinDiscos = new QSpinBox(this);
    spinDiscos->setMinimum(3);
    spinDiscos->setMaximum(8);
    spinDiscos->setValue(3);
    spinDiscos->setStyleSheet("QSpinBox { padding: 5px; font-size: 14px; }");
    
    btnIniciar = new QPushButton("🎮 Iniciar Juego", this);
    btnIniciar->setStyleSheet(
        "QPushButton {"
        "    background-color: #27ae60;"
        "    color: white;"
        "    border: none;"
        "    padding: 10px 20px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #2ecc71;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #229954;"
        "}"
    );
    
    layoutConfig->addWidget(lblDiscos);
    layoutConfig->addWidget(spinDiscos);
    layoutConfig->addWidget(btnIniciar);
    
    // Grupo de acciones
    QGroupBox *grupoAcciones = new QGroupBox("Acciones", this);
    QHBoxLayout *layoutAcciones = new QHBoxLayout(grupoAcciones);
    
    btnResolver = new QPushButton("🤖 Resolver Automático", this);
    btnResolver->setEnabled(false);
    btnResolver->setStyleSheet(
        "QPushButton {"
        "    background-color: #3498db;"
        "    color: white;"
        "    border: none;"
        "    padding: 10px 20px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #5dade2;"
        "}"
        "QPushButton:disabled {"
        "    background-color: #bdc3c7;"
        "}"
    );
    
    btnResolverDesde = new QPushButton("⚡ Resolver desde aquí", this);
    btnResolverDesde->setEnabled(false);
    btnResolverDesde->setStyleSheet(
        "QPushButton {"
        "    background-color: #e67e22;"
        "    color: white;"
        "    border: none;"
        "    padding: 10px 20px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #f39c12;"
        "}"
        "QPushButton:disabled {"
        "    background-color: #bdc3c7;"
        "}"
    );
    
    btnReiniciar = new QPushButton("🔄 Reiniciar", this);
    btnReiniciar->setEnabled(false);
    btnReiniciar->setStyleSheet(
        "QPushButton {"
        "    background-color: #e74c3c;"
        "    color: white;"
        "    border: none;"
        "    padding: 10px 20px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #c0392b;"
        "}"
        "QPushButton:disabled {"
        "    background-color: #bdc3c7;"
        "}"
    );
    
    btnTema = new QPushButton("🌙 Tema Oscuro", this);
    btnTema->setStyleSheet(
        "QPushButton {"
        "    background-color: #34495e;"
        "    color: white;"
        "    border: none;"
        "    padding: 10px 20px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #2c3e50;"
        "}"
    );
    
    layoutAcciones->addWidget(btnResolver);
    layoutAcciones->addWidget(btnResolverDesde);
    layoutAcciones->addWidget(btnReiniciar);
    layoutAcciones->addWidget(btnTema);
    
    // ✨ NUEVO: Botón de sonido
    btnSonido = new QPushButton("🔊 Sonido", this);
    btnSonido->setCheckable(true);
    btnSonido->setChecked(true);
    btnSonido->setStyleSheet(
        "QPushButton {"
        "    background-color: #16a085;"
        "    color: white;"
        "    border: none;"
        "    padding: 10px 20px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "    border-radius: 5px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #1abc9c;"
        "}"
        "QPushButton:checked {"
        "    background-color: #c0392b;"
        "}"
    );
    connect(btnSonido, &QPushButton::toggled, this, [this](bool checked) {
        soundManager->setMuted(!checked);
        btnSonido->setText(checked ? "🔊 Sonido" : "🔇 Mudo");
        if (checked) soundManager->playClickSound();
    });
    layoutAcciones->addWidget(btnSonido);
    
    layoutControl->addWidget(grupoConfig);
    layoutControl->addWidget(grupoAcciones);
    
    layoutPrincipal->addLayout(layoutControl);
    
    // ========== NUEVOS BOTONES PROFESIONALES ==========
    QString estiloBotonExtra = 
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #9b59b6, stop:1 #8e44ad);"
        "    color: white;"
        "    border: none;"
        "    border-radius: 8px;"
        "    padding: 10px 20px;"
        "    font-size: 14px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #a569bd, stop:1 #9b59b6);"
        "}"
        "QPushButton:pressed {"
        "    background: #7d3c98;"
        "}";

    QHBoxLayout *layoutExtras = new QHBoxLayout();
    
    btnHistorial = new QPushButton("📜 Historial");
    btnHistorial->setStyleSheet(estiloBotonExtra);
    connect(btnHistorial, &QPushButton::clicked, this, &MainWindow::mostrarHistorial);
    
    btnGuardar = new QPushButton("💾 Guardar");
    btnGuardar->setStyleSheet(estiloBotonExtra);
    connect(btnGuardar, &QPushButton::clicked, this, &MainWindow::guardarPartida);
    
    btnCargar = new QPushButton("📂 Cargar");
    btnCargar->setStyleSheet(estiloBotonExtra);
    connect(btnCargar, &QPushButton::clicked, this, &MainWindow::cargarPartida);
    
    btnEstadisticas = new QPushButton("📊 Estadísticas");
    btnEstadisticas->setStyleSheet(estiloBotonExtra);
    connect(btnEstadisticas, &QPushButton::clicked, this, &MainWindow::mostrarEstadisticas);
    
    btnTutorial = new QPushButton("📖 Tutorial");
    btnTutorial->setStyleSheet(estiloBotonExtra);
    connect(btnTutorial, &QPushButton::clicked, this, &MainWindow::mostrarTutorial);
    
    QPushButton *btnDificultad = new QPushButton("🎯 Dificultad");
    btnDificultad->setStyleSheet(estiloBotonExtra);
    connect(btnDificultad, &QPushButton::clicked, this, &MainWindow::cambiarDificultad);
    
    QPushButton *btnModoZen = new QPushButton("🧘 Modo Zen");
    btnModoZen->setStyleSheet(estiloBotonExtra);
    connect(btnModoZen, &QPushButton::clicked, this, &MainWindow::activarModoZen);
    
    layoutExtras->addWidget(btnHistorial);
    layoutExtras->addWidget(btnGuardar);
    layoutExtras->addWidget(btnCargar);
    layoutExtras->addWidget(btnEstadisticas);
    layoutExtras->addWidget(btnTutorial);
    layoutExtras->addWidget(btnDificultad);
    layoutExtras->addWidget(btnModoZen);
    layoutExtras->addStretch();
    
    layoutPrincipal->addLayout(layoutExtras);
    
    // Panel de estadísticas
    QHBoxLayout *layoutEstadisticas = new QHBoxLayout();
    
    lblMovimientos = new QLabel("Movimientos: 0", this);
    lblMovimientos->setStyleSheet("font-size: 16px; font-weight: bold; color: #e74c3c;");
    
    lblMinMovimientos = new QLabel("Mínimo: 7", this);
    lblMinMovimientos->setStyleSheet("font-size: 16px; font-weight: bold; color: #27ae60;");
    
    lblTiempo = new QLabel("Tiempo: 00:00", this);
    lblTiempo->setStyleSheet("font-size: 16px; font-weight: bold; color: #3498db;");
    
    lblRecord = new QLabel("🏆 Récord: ---");
    lblRecord->setStyleSheet("font-size: 14px; font-weight: bold; color: #f39c12;");
    
    lblEficiencia = new QLabel("Eficiencia: 100%", this);
    lblEficiencia->setStyleSheet("font-size: 14px; font-weight: bold; color: #9b59b6;");
    
    layoutEstadisticas->addWidget(lblMovimientos);
    layoutEstadisticas->addWidget(lblMinMovimientos);
    layoutEstadisticas->addWidget(lblTiempo);
    layoutEstadisticas->addWidget(lblRecord);
    layoutEstadisticas->addWidget(lblEficiencia);
    layoutEstadisticas->addStretch();
    
    layoutPrincipal->addLayout(layoutEstadisticas);
    
    // ========== BARRA DE PROGRESO ==========
    QHBoxLayout *layoutProgreso = new QHBoxLayout();
    QLabel *lblProgreso = new QLabel("📊 Progreso:");
    lblProgreso->setStyleSheet("font-size: 14px; font-weight: bold;");
    
    barraProgreso = new QProgressBar();
    barraProgreso->setRange(0, 100);
    barraProgreso->setValue(0);
    barraProgreso->setTextVisible(true);
    barraProgreso->setStyleSheet(
        "QProgressBar {"
        "    border: 2px solid #3498db;"
        "    border-radius: 5px;"
        "    text-align: center;"
        "    background: white;"
        "}"
        "QProgressBar::chunk {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #3498db, stop:1 #2ecc71);"
        "    border-radius: 3px;"
        "}"
    );
    
    layoutProgreso->addWidget(lblProgreso);
    layoutProgreso->addWidget(barraProgreso);
    
    layoutPrincipal->addLayout(layoutProgreso);
    
    // Vista gráfica MEJORADA - MÁS GRANDE Y PROFESIONAL
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0, 0, 1200, 700);  // ✨ Escena más grande
    
    // Gradiente de fondo profesional
    QLinearGradient gradienteFondo(0, 0, 0, 700);
    gradienteFondo.setColorAt(0, QColor(44, 62, 80));      // Azul oscuro arriba
    gradienteFondo.setColorAt(0.5, QColor(52, 73, 94));    // Azul medio
    gradienteFondo.setColorAt(1, QColor(44, 62, 80));      // Azul oscuro abajo
    escena->setBackgroundBrush(QBrush(gradienteFondo));
    
    vistaGrafica = new QGraphicsView(escena, this);
    vistaGrafica->setRenderHint(QPainter::Antialiasing);
    vistaGrafica->setRenderHint(QPainter::SmoothPixmapTransform);
    vistaGrafica->setRenderHint(QPainter::TextAntialiasing);
    vistaGrafica->setMinimumHeight(710);  // ✨ Más alto
    vistaGrafica->setMouseTracking(true);  // ✨ Habilitar seguimiento del mouse
    vistaGrafica->viewport()->setMouseTracking(true);  // ✨ En el viewport también
    vistaGrafica->setStyleSheet(
        "border: 3px solid #34495e;"
        "border-radius: 10px;"
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #2c3e50, stop:1 #34495e);"
    );
    layoutPrincipal->addWidget(vistaGrafica);
    
    // Control de velocidad
    QHBoxLayout *layoutVelocidad = new QHBoxLayout();
    QLabel *lblVelText = new QLabel("Velocidad de animación:", this);
    lblVelText->setStyleSheet("font-size: 14px;");
    
    sliderVelocidad = new QSlider(Qt::Horizontal, this);
    sliderVelocidad->setMinimum(1);
    sliderVelocidad->setMaximum(10);
    sliderVelocidad->setValue(7);
    sliderVelocidad->setStyleSheet(
        "QSlider::groove:horizontal {"
        "    border: 1px solid #bbb;"
        "    background: white;"
        "    height: 10px;"
        "    border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal {"
        "    background: #3498db;"
        "    border: 1px solid #5c5c5c;"
        "    width: 18px;"
        "    margin: -2px 0;"
        "    border-radius: 9px;"
        "}"
    );
    
    lblVelocidad = new QLabel("Normal", this);
    lblVelocidad->setStyleSheet("font-size: 14px; font-weight: bold; color: #3498db;");
    lblVelocidad->setMinimumWidth(80);
    
    layoutVelocidad->addWidget(lblVelText);
    layoutVelocidad->addWidget(sliderVelocidad);
    layoutVelocidad->addWidget(lblVelocidad);
    
    layoutPrincipal->addLayout(layoutVelocidad);
    
    // Instrucciones mejoradas con atajos de teclado
    QLabel *instrucciones = new QLabel(
        "📖 <b>Atajos de teclado:</b> [ESPACIO] Resolver desde aquí | [R] Reiniciar | "
        "[H] Historial | [S] Guardar | [L] Cargar | [T] Cambiar tema | [F1] Tutorial", this);
    instrucciones->setWordWrap(true);
    instrucciones->setTextFormat(Qt::RichText);
    instrucciones->setStyleSheet("font-size: 12px; color: #7f8c8d; padding: 10px; background-color: #ecf0f1; border-radius: 5px;");
    layoutPrincipal->addWidget(instrucciones);
    
    // Timers
    timer = new QTimer(this);
    timerJuego = new QTimer(this);
    timerJuego->setInterval(1000);
    
    // Conexiones
    connect(btnIniciar, &QPushButton::clicked, this, &MainWindow::iniciarJuego);
    connect(btnResolver, &QPushButton::clicked, this, &MainWindow::resolverAutomatico);
    connect(btnResolverDesde, &QPushButton::clicked, this, &MainWindow::resolverDesdeAqui);
    connect(btnReiniciar, &QPushButton::clicked, this, &MainWindow::reiniciar);
    connect(btnTema, &QPushButton::clicked, this, &MainWindow::cambiarTema);
    connect(timer, &QTimer::timeout, this, &MainWindow::siguienteMovimiento);
    connect(timerJuego, &QTimer::timeout, this, [this]() {
        if (!modoZen) {
            tiempoTranscurrido++;
            int minutos = tiempoTranscurrido / 60;
            int segundos = tiempoTranscurrido % 60;
            lblTiempo->setText(QString("Tiempo: %1:%2")
                .arg(minutos, 2, 10, QChar('0'))
                .arg(segundos, 2, 10, QChar('0')));
        }
    });
    connect(sliderVelocidad, &QSlider::valueChanged, this, &MainWindow::cambiarVelocidad);
    
    // Configuración de ventana
    setWindowTitle("Torres de Hanoi - Juego Interactivo");
    resize(1000, 700);
    
    crearTorres();
}

void MainWindow::crearTorres()
{
    torres.clear();
    
    // Dimensiones MEJORADAS - MÁS GRANDES
    int anchoEscena = 1200;  // ✨ Escena más ancha
    int altoEscena = 700;    // ✨ Escena más alta
    escena->setSceneRect(0, 0, anchoEscena, altoEscena);
    
    int separacion = anchoEscena / 3;
    int baseY = altoEscena - 80;  // ✨ Más espacio abajo
    
    for (int i = 0; i < 3; i++) {
        int x = separacion / 2 + i * separacion;
        Torre *torre = new Torre(x, baseY, i);
        torres.push_back(torre);
        escena->addItem(torre);
    }
}

void MainWindow::crearDiscos(int cantidad)
{
    limpiarDiscos();
    numDiscos = cantidad;
    
    // Discos MEJORADOS - MÁS GRANDES
    int anchoMax = 220;  // ✨ Discos más anchos
    int anchoMin = 80;   // ✨ Disco mínimo más ancho
    int alto = 35;       // ✨ Discos más altos/gruesos
    
    for (int i = 0; i < cantidad; i++) {
        int ancho = anchoMax - (i * (anchoMax - anchoMin) / (cantidad - 1));
        Disco *disco = new Disco(ancho, alto, cantidad - i);
        discos.push_back(disco);
        escena->addItem(disco);
        
        // ✨ Conectar señales para drag and drop
        connect(disco, &Disco::discoPresionado, this, &MainWindow::onDiscoPresionado);
        connect(disco, &Disco::discoSoltado, this, &MainWindow::onDiscoSoltado);
        
        // Colocar en la primera torre
        torres[0]->agregarDisco(disco);
    }
    
    actualizarEstadisticas();
}

void MainWindow::limpiarDiscos()
{
    for (auto disco : discos) {
        escena->removeItem(disco);
        delete disco;
    }
    discos.clear();
    
    for (auto torre : torres) {
        torre->limpiar();
    }
}

void MainWindow::iniciarJuego()
{
    numDiscos = spinDiscos->value();
    contadorMovimientos = 0;
    tiempoTranscurrido = 0;
    juegoIniciado = true;
    resolviendoAutomatico = false;
    movimientos.clear();
    
    crearDiscos(numDiscos);
    
    btnIniciar->setEnabled(false);
    btnResolver->setEnabled(true);
    btnResolverDesde->setEnabled(true);
    btnReiniciar->setEnabled(true);
    spinDiscos->setEnabled(false);
    
    timerJuego->start();
    
    actualizarEstadisticas();
}

void MainWindow::resolverAutomatico()
{
    if (resolviendoAutomatico) return;
    
    // ✨ NUEVO: Detectar si hay discos movidos manualmente
    bool discosEnPosicionInicial = true;
    auto discosEnA = torres[0]->obtenerDiscos();
    
    // Verificar si todos los discos están en la torre A en orden correcto
    if (discosEnA.size() != static_cast<size_t>(numDiscos)) {
        discosEnPosicionInicial = false;
    } else {
        // Verificar orden correcto (más grande abajo)
        for (size_t i = 0; i < discosEnA.size(); i++) {
            if (discosEnA[i]->obtenerTamano() != static_cast<int>(numDiscos - i)) {
                discosEnPosicionInicial = false;
                break;
            }
        }
    }
    
    movimientos.clear();
    movimientoActual = 0;
    resolviendoAutomatico = true;
    
    btnResolver->setEnabled(false);
    btnResolverDesde->setEnabled(false);
    
    if (discosEnPosicionInicial) {
        // Si están en posición inicial, usar algoritmo clásico
        calcularSolucion(numDiscos, 0, 2, 1);
    } else {
        // Si hay movimientos manuales, resolver desde el estado actual
        std::vector<std::stack<int>> estado(3);
        
        for (int i = 0; i < 3; i++) {
            auto discosEnTorre = torres[i]->obtenerDiscos();
            for (auto disco : discosEnTorre) {
                estado[i].push(disco->obtenerTamano());
            }
        }
        
        resolverDesdeEstado(estado);
    }
    
    // Iniciar animación
    velocidadAnimacion = 1000 - (sliderVelocidad->value() * 90);
    timer->start(velocidadAnimacion);
}

void MainWindow::resolverDesdeAqui()
{
    if (resolviendoAutomatico) return;
    
    // Obtener estado actual
    std::vector<std::stack<int>> estado(3);
    
    for (int i = 0; i < 3; i++) {
        auto discosEnTorre = torres[i]->obtenerDiscos();
        for (auto disco : discosEnTorre) {
            estado[i].push(disco->obtenerTamano());
        }
    }
    
    movimientos.clear();
    movimientoActual = 0;
    resolviendoAutomatico = true;
    
    btnResolver->setEnabled(false);
    btnResolverDesde->setEnabled(false);
    
    resolverDesdeEstado(estado);
    
    velocidadAnimacion = 1000 - (sliderVelocidad->value() * 90);
    timer->start(velocidadAnimacion);
}

void MainWindow::resolverDesdeEstado(std::vector<std::stack<int>> estado)
{
    // ✨ ESTRATEGIA SIMPLE Y EFECTIVA:
    // 1. Primero resetear todos los discos a la torre inicial (A)
    // 2. Luego resolver normalmente de A a C
    
    qDebug() << "🔄 Resolviendo desde estado actual...";
    
    // Crear simulación del estado
    std::vector<std::vector<int>> torres_sim(3);
    
    for (int torre = 0; torre < 3; torre++) {
        std::stack<int> copia = estado[torre];
        std::vector<int> temp;
        while (!copia.empty()) {
            temp.push_back(copia.top());
            copia.pop();
        }
        std::reverse(temp.begin(), temp.end());
        torres_sim[torre] = temp;
    }
    
    // Funciones auxiliares
    auto esMovimientoValido = [&](int desde, int hacia) -> bool {
        if (torres_sim[desde].empty()) return false;
        if (torres_sim[hacia].empty()) return true;
        return torres_sim[desde].back() < torres_sim[hacia].back();
    };
    
    auto hacerMovimiento = [&](int desde, int hacia) -> bool {
        if (!esMovimientoValido(desde, hacia)) return false;
        int disco = torres_sim[desde].back();
        torres_sim[desde].pop_back();
        torres_sim[hacia].push_back(disco);
        movimientos.push_back({desde, hacia});
        return true;
    };
    
    // Función recursiva estándar de Hanoi
    std::function<void(int, int, int, int)> hanoi;
    hanoi = [&](int n, int origen, int destino, int auxiliar) {
        if (n <= 0) return;
        hanoi(n - 1, origen, auxiliar, destino);
        hacerMovimiento(origen, destino);
        hanoi(n - 1, auxiliar, destino, origen);
    };
    
    // FASE 1: Mover todos los discos pequeños a la torre A
    // Ordenar de menor a mayor para moverlos eficientemente
    for (int disco = 1; disco <= numDiscos; disco++) {
        // Encontrar dónde está el disco
        int torreActual = -1;
        for (int t = 0; t < 3; t++) {
            for (int d : torres_sim[t]) {
                if (d == disco) {
                    torreActual = t;
                    break;
                }
            }
            if (torreActual != -1) break;
        }
        
        if (torreActual == 0) continue; // Ya está en A
        
        // Mover este disco a la torre A
        // Primero quitar discos más pequeños que estén encima
        while (!torres_sim[torreActual].empty() && torres_sim[torreActual].back() != disco) {
            int discoEncima = torres_sim[torreActual].back();
            // Mover disco encima a una torre temporal (no A, no torreActual)
            int temporal = (torreActual == 0) ? 1 : ((torreActual == 1) ? 2 : 1);
            if (temporal == 0) temporal = 2;
            hacerMovimiento(torreActual, temporal);
        }
        
        // Ahora el disco está arriba, moverlo a A
        if (!torres_sim[torreActual].empty() && torres_sim[torreActual].back() == disco) {
            // Verificar si hay obstáculo en A
            while (!torres_sim[0].empty() && torres_sim[0].back() < disco) {
                int auxiliarTemp = (torreActual == 1) ? 2 : 1;
                hacerMovimiento(0, auxiliarTemp);
            }
            hacerMovimiento(torreActual, 0);
        }
    }
    
    qDebug() << "✓ Fase 1 completada: Todos los discos en torre A";
    
    // FASE 2: Resolver normalmente de A (0) a C (2)
    hanoi(numDiscos, 0, 2, 1);
    
    qDebug() << "✅ Solución calculada:" << movimientos.size() << "movimientos";
}

void MainWindow::calcularSolucion(int n, int origen, int destino, int auxiliar)
{
    if (n == 1) {
        movimientos.push_back({origen, destino});
        return;
    }
    
    calcularSolucion(n - 1, origen, auxiliar, destino);
    movimientos.push_back({origen, destino});
    calcularSolucion(n - 1, auxiliar, destino, origen);
}

void MainWindow::siguienteMovimiento()
{
    if (movimientoActual >= movimientos.size()) {
        timer->stop();
        resolviendoAutomatico = false;
        btnReiniciar->setEnabled(true);
        
        if (juegoCompletado()) {
            timerJuego->stop();
            QMessageBox::information(this, "¡Felicidades!", 
                QString("¡Juego completado!\n\nMovimientos: %1\nMínimo posible: %2\nTiempo: %3:%4")
                .arg(contadorMovimientos)
                .arg((int)pow(2, numDiscos) - 1)
                .arg(tiempoTranscurrido / 60, 2, 10, QChar('0'))
                .arg(tiempoTranscurrido % 60, 2, 10, QChar('0')));
        }
        return;
    }
    
    auto movimiento = movimientos[movimientoActual];
    moverDisco(movimiento.first, movimiento.second, true);
    movimientoActual++;
}

void MainWindow::moverDisco(int desde, int hacia, bool animado)
{
    if (!verificarMovimientoValido(desde, hacia)) {
        QMessageBox::warning(this, "Movimiento inválido", 
            "No puedes colocar un disco más grande sobre uno más pequeño.");
        soundManager->playErrorSound();  // ✨ Sonido de error
        return;
    }
    
    Disco *disco = torres[desde]->quitarDisco();
    if (!disco) return;
    
    torres[hacia]->agregarDisco(disco);
    contadorMovimientos++;
    
    // ✨ Reproducir sonido de movimiento
    soundManager->playMoveSound();
    
    // ========== AGREGAR AL HISTORIAL ==========
    if (!resolviendoAutomatico) {
        historialMovimientos.push_back({desde, hacia});
    }
    
    actualizarEstadisticas();
    actualizarProgreso();
    
    if (!resolviendoAutomatico && juegoCompletado()) {
        timerJuego->stop();
        soundManager->playVictorySound();  // ✨ Sonido de victoria
        mostrarCelebracion();
    }
}

bool MainWindow::verificarMovimientoValido(int desde, int hacia)
{
    if (torres[desde]->estaVacia()) return false;
    if (torres[hacia]->estaVacia()) return true;
    
    return torres[desde]->obtenerDiscoSuperior()->obtenerTamano() < 
           torres[hacia]->obtenerDiscoSuperior()->obtenerTamano();
}

bool MainWindow::juegoCompletado()
{
    return torres[2]->obtenerDiscos().size() == numDiscos;
}

void MainWindow::actualizarEstadisticas()
{
    lblMovimientos->setText(QString("Movimientos: %1").arg(contadorMovimientos));
    int minMovimientos = (int)pow(2, numDiscos) - 1;
    lblMinMovimientos->setText(QString("Mínimo: %1").arg(minMovimientos));
}

void MainWindow::reiniciar()
{
    timer->stop();
    timerJuego->stop();
    
    contadorMovimientos = 0;
    tiempoTranscurrido = 0;
    juegoIniciado = false;
    resolviendoAutomatico = false;
    movimientos.clear();
    historialMovimientos.clear();
    
    if (barraProgreso) barraProgreso->setValue(0);
    
    limpiarDiscos();
    
    btnIniciar->setEnabled(true);
    btnResolver->setEnabled(false);
    btnResolverDesde->setEnabled(false);
    btnReiniciar->setEnabled(false);
    spinDiscos->setEnabled(true);
    
    actualizarEstadisticas();
}

void MainWindow::cambiarVelocidad(int valor)
{
    velocidadAnimacion = 1000 - (valor * 90);
    
    QString texto;
    if (valor <= 3) texto = "Muy lenta";
    else if (valor <= 5) texto = "Lenta";
    else if (valor <= 7) texto = "Normal";
    else if (valor <= 9) texto = "Rápida";
    else texto = "Muy rápida";
    
    lblVelocidad->setText(texto);
    
    if (timer->isActive()) {
        timer->setInterval(velocidadAnimacion);
    }
}

void MainWindow::cambiarTema()
{
    // Ciclar entre todos los temas épicos
    temaActual = static_cast<TemaVisual>((temaActual + 1) % 5);
    aplicarTemaModerno(temaActual);
}

void MainWindow::animarTransicionTema()
{
    // Función deshabilitada temporalmente - causaba crashes
    // La animación de opacity effect puede causar problemas con QGraphicsView
}

QString MainWindow::obtenerEstiloFondo(TemaVisual tema)
{
    switch (tema) {
        case TEMA_DARK_MODERN:
            return "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                   "stop:0 #0f0c29, stop:0.5 #302b63, stop:1 #24243e);";
        
        case TEMA_LIGHT_ELEGANT:
            return "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                   "stop:0 #ffffff, stop:0.5 #f8f9fa, stop:1 #e9ecef);";
        
        case TEMA_NEON_CYBERPUNK:
            return "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                   "stop:0 #000000, stop:0.3 #0a0a0a, stop:0.7 #1a0a1a, stop:1 #000000);";
        
        case TEMA_GLASSMORPHISM:
            return "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                   "stop:0 #e3f2fd, stop:0.5 #bbdefb, stop:1 #90caf9);";  // Azul suave y claro
        
        case TEMA_SUNSET_GRADIENT:
            return "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                   "stop:0 #ff6b6b, stop:0.3 #ee5a6f, stop:0.6 #c06c84, stop:1 #6c5b7b);";
        
        default:
            return "background: #2c3e50;";
    }
}

QString MainWindow::obtenerEstiloBoton(TemaVisual tema)
{
    switch (tema) {
        case TEMA_DARK_MODERN:
            return "QPushButton {"
                   "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                   "        stop:0 #667eea, stop:1 #764ba2);"
                   "    color: white;"
                   "    border: none;"
                   "    border-radius: 12px;"
                   "    padding: 12px 24px;"
                   "    font-size: 14px;"
                   "    font-weight: bold;"
                   "}"
                   "QPushButton:hover {"
                   "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                   "        stop:0 #764ba2, stop:1 #667eea);"
                   "}"
                   "QPushButton:pressed {"
                   "    background: #5568d3;"
                   "}";
        
        case TEMA_LIGHT_ELEGANT:
            return "QPushButton {"
                   "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                   "        stop:0 #4facfe, stop:1 #00f2fe);"
                   "    color: white;"
                   "    border: 2px solid rgba(255, 255, 255, 0.3);"
                   "    border-radius: 12px;"
                   "    padding: 12px 24px;"
                   "    font-size: 14px;"
                   "    font-weight: bold;"
                   "}"
                   "QPushButton:hover {"
                   "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                   "        stop:0 #00f2fe, stop:1 #4facfe);"
                   "}"
                   "QPushButton:pressed {"
                   "    background: #3d9ae0;"
                   "}";
        
        case TEMA_NEON_CYBERPUNK:
            return "QPushButton {"
                   "    background: transparent;"
                   "    color: #00ff41;"
                   "    border: 2px solid #00ff41;"
                   "    border-radius: 12px;"
                   "    padding: 12px 24px;"
                   "    font-size: 14px;"
                   "    font-weight: bold;"
                   "}"
                   "QPushButton:hover {"
                   "    background: rgba(0, 255, 65, 0.1);"
                   "    border: 2px solid #00ffff;"
                   "    color: #00ffff;"
                   "}"
                   "QPushButton:pressed {"
                   "    background: rgba(0, 255, 65, 0.2);"
                   "}";
        
        case TEMA_GLASSMORPHISM:
            return "QPushButton {"
                   "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                   "        stop:0 rgba(100, 150, 200, 0.8), stop:1 rgba(70, 130, 180, 0.9));"
                   "    color: white;"
                   "    border: 2px solid rgba(255, 255, 255, 0.5);"
                   "    border-radius: 12px;"
                   "    padding: 12px 24px;"
                   "    font-size: 14px;"
                   "    font-weight: bold;"
                   "}"
                   "QPushButton:hover {"
                   "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                   "        stop:0 rgba(70, 130, 180, 0.9), stop:1 rgba(100, 150, 200, 0.8));"
                   "    border: 2px solid rgba(255, 255, 255, 0.8);"
                   "}"
                   "QPushButton:pressed {"
                   "    background: rgba(50, 100, 150, 0.9);"
                   "}";
        
        case TEMA_SUNSET_GRADIENT:
            return "QPushButton {"
                   "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
                   "        stop:0 #f093fb, stop:1 #f5576c);"
                   "    color: white;"
                   "    border: none;"
                   "    border-radius: 12px;"
                   "    padding: 12px 24px;"
                   "    font-size: 14px;"
                   "    font-weight: bold;"
                   "}"
                   "QPushButton:hover {"
                   "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
                   "        stop:0 #f5576c, stop:1 #f093fb);"
                   "}"
                   "QPushButton:pressed {"
                   "    background: #e04858;"
                   "}";
        
        default:
            return "";
    }
}

void MainWindow::aplicarTemaModerno(TemaVisual tema)
{
    // Versión simplificada y segura - solo aplicar estilos básicos
    QString estiloBoton = obtenerEstiloBoton(tema);
    QString estiloFondo = obtenerEstiloFondo(tema);
    QString colorTexto = "#ffffff";
    QString estiloVista = "border: 2px solid rgba(102, 126, 234, 0.5); border-radius: 15px; background: #1a1a2e;";
    QString nombreTema = "🌌 Dark Modern";
    
    switch (tema) {
        case TEMA_DARK_MODERN:
            colorTexto = "#ffffff";
            estiloVista = "border: 2px solid rgba(102, 126, 234, 0.5); border-radius: 15px; background: #1a1a2e;";
            nombreTema = "🌌 Dark Modern";
            break;
        
        case TEMA_LIGHT_ELEGANT:
            colorTexto = "#2c3e50";
            estiloVista = "border: 2px solid rgba(79, 172, 254, 0.4); border-radius: 15px; background: #f0f4f8;";
            nombreTema = "☀️ Light Elegant";
            break;
        
        case TEMA_NEON_CYBERPUNK:
            colorTexto = "#00ff41";
            estiloVista = "border: 2px solid #00ff41; border-radius: 15px; background: #000000;";
            nombreTema = "⚡ Neon Cyberpunk";
            break;
        
        case TEMA_GLASSMORPHISM:
            colorTexto = "#2c3e50";  // Texto oscuro para mejor contraste
            estiloVista = "border: 2px solid rgba(100, 150, 200, 0.5); border-radius: 15px; background: rgba(240, 248, 255, 0.95);";
            nombreTema = "💎 Glassmorphism";
            break;
        
        case TEMA_SUNSET_GRADIENT:
            colorTexto = "#ffffff";
            estiloVista = "border: 2px solid rgba(255, 107, 107, 0.5); border-radius: 15px; background: #fad0c4;";
            nombreTema = "🌅 Sunset Dream";
            break;
    }
    
    // Aplicar estilos globales básicos
    QString estiloGlobal = QString(
        "QMainWindow { %1 }"
        "QWidget { %1 color: %2; font-family: 'Segoe UI', Arial; }"
        "QLabel { color: %2; font-size: 13px; }"
        "QSpinBox {"
        "    background: rgba(255, 255, 255, 0.1);"
        "    color: %2;"
        "    border: 2px solid rgba(255, 255, 255, 0.2);"
        "    border-radius: 8px;"
        "    padding: 8px;"
        "    font-size: 14px;"
        "}"
        "%3"
    ).arg(estiloFondo, colorTexto, estiloBoton);
    
    setStyleSheet(estiloGlobal);
    
    // Aplicar a botones solo si existen
    if (btnTema) {
        btnTema->setStyleSheet(estiloBoton);
        btnTema->setText(nombreTema);
    }
    if (btnIniciar) btnIniciar->setStyleSheet(estiloBoton);
    if (btnResolver) btnResolver->setStyleSheet(estiloBoton);
    if (btnReiniciar) btnReiniciar->setStyleSheet(estiloBoton);
    if (vistaGrafica) vistaGrafica->setStyleSheet(estiloVista);
    
    // Actualizar fondo de escena
    actualizarColoresTema(tema);
}

void MainWindow::aplicarTema()
{
    // Mantener compatibilidad, usar tema moderno
    aplicarTemaModerno(temaActual);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // Ya no se usa, el drag and drop se maneja con señales
    QMainWindow::mousePressEvent(event);
}

// ========== NUEVAS FUNCIONES PROFESIONALES ==========

void MainWindow::reproducirSonidoMovimiento()
{
    // Efecto visual de sonido (sin audio real, solo visual)
    crearEfectoExplosion(QPointF(450, 200), QColor(52, 152, 219));
}

void MainWindow::mostrarHistorial()
{
    // Colores adaptativos según el tema actual
    QString colorTitulo, colorFondo1, colorFondo2, colorTexto, colorEncabezado;
    
    switch (temaActual) {
        case TEMA_DARK_MODERN:
            colorTitulo = "#667eea";
            colorFondo1 = "#2c2c4e";
            colorFondo2 = "#3a3a5e";
            colorTexto = "#ffffff";
            colorEncabezado = "#4a4a6e";
            break;
        
        case TEMA_LIGHT_ELEGANT:
            colorTitulo = "#4facfe";
            colorFondo1 = "#ffffff";
            colorFondo2 = "#f0f4f8";
            colorTexto = "#2c3e50";
            colorEncabezado = "#e3f2fd";
            break;
        
        case TEMA_NEON_CYBERPUNK:
            colorTitulo = "#00ff41";
            colorFondo1 = "#0a0a0a";
            colorFondo2 = "#1a1a1a";
            colorTexto = "#00ff41";
            colorEncabezado = "#001a00";
            break;
        
        case TEMA_GLASSMORPHISM:
            colorTitulo = "#667eea";
            colorFondo1 = "rgba(255, 255, 255, 0.15)";
            colorFondo2 = "rgba(255, 255, 255, 0.25)";
            colorTexto = "#2c3e50";
            colorEncabezado = "rgba(102, 126, 234, 0.2)";
            break;
        
        case TEMA_SUNSET_GRADIENT:
            colorTitulo = "#f5576c";
            colorFondo1 = "#ffe6ea";
            colorFondo2 = "#fff0f2";
            colorTexto = "#5a2a3a";
            colorEncabezado = "#ffd1d8";
            break;
    }
    
    QString historial = QString("<h2 style='color: %1;'>📜 Historial de Movimientos</h2>").arg(colorTitulo);
    historial += QString("<table style='width: 100%; font-size: 14px; color: %1;'>").arg(colorTexto);
    historial += QString("<tr style='background: %1; color: %2; font-weight: bold;'><th>Movimiento</th><th>Desde</th><th>Hacia</th></tr>")
        .arg(colorEncabezado, colorTexto);
    
    char torres[] = {'A', 'B', 'C'};
    for (size_t i = 0; i < historialMovimientos.size(); i++) {
        QString fondo = (i % 2 == 0) ? colorFondo1 : colorFondo2;
        historial += QString("<tr style='background: %1; color: %2;'><td>%3</td><td>Torre %4</td><td>Torre %5</td></tr>")
            .arg(fondo, colorTexto)
            .arg(i + 1)
            .arg(torres[historialMovimientos[i].first])
            .arg(torres[historialMovimientos[i].second]);
    }
    
    historial += "</table>";
    historial += QString("<p style='margin-top: 20px; color: %1;'><b>Total de movimientos: %2</b></p>")
        .arg(colorTitulo)
        .arg(historialMovimientos.size());
    
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Historial de Movimientos");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(historial);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::guardarPartida()
{
    if (!juegoIniciado) {
        QMessageBox::warning(this, "Advertencia", "⚠ No hay partida en curso");
        return;
    }
    
    QFile archivo("partida_hanoi.dat");
    if (archivo.open(QIODevice::WriteOnly)) {
        QDataStream out(&archivo);
        
        // Guardar datos básicos
        out << numDiscos << contadorMovimientos << tiempoTranscurrido;
        
        // Guardar estado de las torres
        for (int i = 0; i < 3; i++) {
            auto discosEnTorre = torres[i]->obtenerDiscos();
            out << (int)discosEnTorre.size();
            for (auto disco : discosEnTorre) {
                out << disco->obtenerTamano();
            }
        }
        
        // Guardar historial
        out << (int)historialMovimientos.size();
        for (auto mov : historialMovimientos) {
            out << mov.first << mov.second;
        }
        
        archivo.close();
        QMessageBox::information(this, "Éxito", "💾 Partida guardada exitosamente");
    } else {
        QMessageBox::critical(this, "Error", "❌ Error al guardar partida");
    }
}

void MainWindow::cargarPartida()
{
    QFile archivo("partida_hanoi.dat");
    if (!archivo.exists()) {
        QMessageBox::warning(this, "Advertencia", "⚠ No hay partida guardada");
        return;
    }
    
    if (archivo.open(QIODevice::ReadOnly)) {
        QDataStream in(&archivo);
        
        // Limpiar juego actual
        limpiarDiscos();
        
        // Cargar datos básicos
        in >> numDiscos >> contadorMovimientos >> tiempoTranscurrido;
        
        // Crear discos
        int anchoMax = 150;
        int anchoMin = 60;
        int alto = 25;
        
        for (int i = 0; i < numDiscos; i++) {
            int ancho = anchoMax - (i * (anchoMax - anchoMin) / (numDiscos - 1));
            Disco *disco = new Disco(ancho, alto, numDiscos - i);
            discos.push_back(disco);
            escena->addItem(disco);
        }
        
        // Cargar estado de las torres
        std::vector<std::vector<int>> estadoTorres(3);
        for (int i = 0; i < 3; i++) {
            int numDiscosEnTorre;
            in >> numDiscosEnTorre;
            for (int j = 0; j < numDiscosEnTorre; j++) {
                int tamano;
                in >> tamano;
                estadoTorres[i].push_back(tamano);
            }
        }
        
        // Colocar discos en las torres
        for (int i = 0; i < 3; i++) {
            for (int tamano : estadoTorres[i]) {
                for (auto disco : discos) {
                    if (disco->obtenerTamano() == tamano) {
                        torres[i]->agregarDisco(disco);
                        break;
                    }
                }
            }
        }
        
        // Cargar historial
        historialMovimientos.clear();
        int numMovimientos;
        in >> numMovimientos;
        for (int i = 0; i < numMovimientos; i++) {
            int desde, hacia;
            in >> desde >> hacia;
            historialMovimientos.push_back({desde, hacia});
        }
        
        archivo.close();
        
        juegoIniciado = true;
        btnIniciar->setEnabled(false);
        btnResolver->setEnabled(true);
        btnResolverDesde->setEnabled(true);
        btnReiniciar->setEnabled(true);
        spinDiscos->setEnabled(false);
        
        timerJuego->start();
        actualizarEstadisticas();
        actualizarProgreso();
        
        QMessageBox::information(this, "Éxito", "📂 Partida cargada exitosamente");
    } else {
        QMessageBox::critical(this, "Error", "❌ Error al cargar partida");
    }
}

void MainWindow::mostrarEstadisticas()
{
    cargarEstadisticas();
    
    QString stats = "<h2 style='color: #3498db;'>📊 Estadísticas Globales</h2>";
    stats += "<div style='background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #3498db, stop:1 #2ecc71); "
             "padding: 20px; border-radius: 10px; color: white;'>";
    
    stats += QString("<p style='font-size: 18px;'><b>🎮 Partidas jugadas:</b> %1</p>").arg(partidasJugadas);
    stats += QString("<p style='font-size: 18px;'><b>🏆 Partidas ganadas:</b> %1</p>").arg(partidasGanadas);
    
    float porcentaje = partidasJugadas > 0 ? (float)partidasGanadas / partidasJugadas * 100 : 0;
    stats += QString("<p style='font-size: 18px;'><b>📈 Porcentaje de éxito:</b> %1%</p>").arg(QString::number(porcentaje, 'f', 1));
    stats += QString("<p style='font-size: 18px;'><b>⭐ Mejor récord:</b> %1 movimientos</p>").arg(recordMovimientos == 999999 ? 0 : recordMovimientos);
    
    stats += "</div>";
    
    stats += "<h3 style='color: #e74c3c; margin-top: 20px;'>🎯 Movimientos Mínimos por Nivel</h3>";
    stats += "<ul>";
    for (int n = 3; n <= 8; n++) {
        int min = (int)pow(2, n) - 1;
        stats += QString("<li><b>%1 discos:</b> %2 movimientos</li>").arg(n).arg(min);
    }
    stats += "</ul>";
    
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Estadísticas");
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(stats);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::guardarEstadisticas()
{
    QFile archivo("estadisticas_hanoi.dat");
    if (archivo.open(QIODevice::WriteOnly)) {
        QDataStream out(&archivo);
        out << partidasJugadas << partidasGanadas << recordMovimientos;
        archivo.close();
    }
}

void MainWindow::cargarEstadisticas()
{
    QFile archivo("estadisticas_hanoi.dat");
    if (archivo.exists() && archivo.open(QIODevice::ReadOnly)) {
        QDataStream in(&archivo);
        in >> partidasJugadas >> partidasGanadas >> recordMovimientos;
        archivo.close();
    } else {
        partidasJugadas = 0;
        partidasGanadas = 0;
        recordMovimientos = 999999;
    }
}

void MainWindow::cambiarDificultad()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Seleccionar Dificultad");
    msgBox.setText("Elige el nivel de dificultad:");
    
    QPushButton *btnFacil = msgBox.addButton("😊 Fácil (3 discos)", QMessageBox::ActionRole);
    QPushButton *btnMedio = msgBox.addButton("😐 Medio (5 discos)", QMessageBox::ActionRole);
    QPushButton *btnDificil = msgBox.addButton("😰 Difícil (7 discos)", QMessageBox::ActionRole);
    QPushButton *btnExperto = msgBox.addButton("🔥 Experto (8 discos)", QMessageBox::ActionRole);
    
    msgBox.exec();
    
    if (msgBox.clickedButton() == btnFacil) {
        spinDiscos->setValue(3);
    } else if (msgBox.clickedButton() == btnMedio) {
        spinDiscos->setValue(5);
    } else if (msgBox.clickedButton() == btnDificil) {
        spinDiscos->setValue(7);
    } else if (msgBox.clickedButton() == btnExperto) {
        spinDiscos->setValue(8);
    }
}

void MainWindow::activarModoZen()
{
    modoZen = !modoZen;
    
    if (modoZen) {
        QMessageBox::information(this, "Modo Zen", "🧘 Modo Zen activado - Sin límite de tiempo");
        timerJuego->stop();
        lblTiempo->setText("⏱ Modo Zen ∞");
    } else {
        QMessageBox::information(this, "Modo Normal", "⏱ Modo Normal activado");
        if (juegoIniciado) {
            timerJuego->start();
        }
    }
}

void MainWindow::mostrarTutorial()
{
    QMessageBox tutorial(this);
    tutorial.setWindowTitle("📖 Tutorial");
    tutorial.setTextFormat(Qt::RichText);
    tutorial.setText(
        "<h2 style='color: #3498db;'>🗼 Cómo Jugar a las Torres de Hanoi</h2>"
        
        "<h3 style='color: #2ecc71;'>🎯 Objetivo:</h3>"
        "<p>Mover todos los discos desde la Torre A hasta la Torre C.</p>"
        
        "<h3 style='color: #e74c3c;'>📜 Reglas:</h3>"
        "<ol>"
        "<li>Solo puedes mover un disco a la vez</li>"
        "<li>Solo puedes mover el disco superior de una torre</li>"
        "<li><b>Regla de oro:</b> Nunca puedes poner un disco grande sobre uno pequeño</li>"
        "</ol>"
        
        "<h3 style='color: #f39c12;'>🎮 Controles:</h3>"
        "<ul>"
        "<li><b>Click en disco:</b> Seleccionar disco superior (se ilumina en amarillo)</li>"
        "<li><b>Click en torre:</b> Mover disco seleccionado a esa torre</li>"
        "<li><b>🤖 Auto:</b> Ver la solución automática completa</li>"
        "<li><b>⚡ Desde aquí:</b> Resolver desde tu posición actual (¡útil si te atascas!)</li>"
        "<li><b>💾 Guardar:</b> Guardar tu partida para continuar después</li>"
        "</ul>"
        
        "<h3 style='color: #9b59b6;'>💡 Tips:</h3>"
        "<ul>"
        "<li>Piensa antes de mover - cada disco pequeño debe 'dar paso' a los grandes</li>"
        "<li>La solución óptima para n discos es: <b>2^n - 1</b> movimientos</li>"
        "<li>Usa la Torre B como 'auxiliar' para movimientos intermedios</li>"
        "<li>Si te atascas, usa 'Resolver desde aquí' para ver la solución óptima</li>"
        "</ul>"
        
        "<p style='background: #ecf0f1; padding: 10px; border-radius: 5px; margin-top: 15px;'>"
        "<b>🌟 ¿Sabías que?</b> Las Torres de Hanoi es un rompecabezas matemático inventado por el matemático francés "
        "Édouard Lucas en 1883. La leyenda dice que los monjes tienen que mover 64 discos de oro, "
        "y cuando terminen, ¡llegará el fin del mundo! 😄"
        "</p>"
    );
    tutorial.setStandardButtons(QMessageBox::Ok);
    tutorial.exec();
}

void MainWindow::crearEfectoExplosion(QPointF posicion, QColor color)
{
    // ✨ EFECTO VISUAL INSTANTÁNEO SIN TIMERS (evita bugs)
    // Crear círculo expandido que se elimina inmediatamente
    
    QGraphicsEllipseItem *circulo = escena->addEllipse(
        posicion.x() - 40, posicion.y() - 40, 80, 80,
        QPen(color, 4),
        QBrush(Qt::NoBrush)
    );
    circulo->setZValue(1000);
    circulo->setOpacity(0.7);
    
    // Eliminar inmediatamente después de mostrar
    QTimer::singleShot(50, [this, circulo]() {
        escena->removeItem(circulo);
        delete circulo;
    });
}

void MainWindow::reproducirEfectoVisual(QString tipo)
{
    if (tipo == "movimiento") {
        crearEfectoExplosion(QPointF(450, 300), QColor(52, 152, 219));
    } else if (tipo == "victoria") {
        for (int i = 0; i < 5; i++) {
            QTimer::singleShot(i * 200, [this, i]() {
                crearEfectoExplosion(
                    QPointF(300 + i * 100, 200),
                    QColor::fromHsv((i * 60) % 360, 255, 255)
                );
            });
        }
    } else if (tipo == "error") {
        crearEfectoExplosion(QPointF(450, 300), QColor(231, 76, 60));
    }
}

void MainWindow::actualizarProgreso()
{
    if (!barraProgreso) return;
    
    int porcentaje = 0;
    if (numDiscos > 0) {
        size_t discosEnC = torres[2]->obtenerDiscos().size();
        porcentaje = (discosEnC * 100) / numDiscos;
    }
    
    barraProgreso->setValue(porcentaje);
    
    if (porcentaje == 100 && juegoCompletado()) {
        barraProgreso->setStyleSheet(
            "QProgressBar {"
            "    border: 2px solid #27ae60;"
            "    border-radius: 5px;"
            "    text-align: center;"
            "    background: white;"
            "}"
            "QProgressBar::chunk {"
            "    background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #27ae60, stop:1 #2ecc71);"
            "    border-radius: 3px;"
            "}"
        );
    }
}

void MainWindow::mostrarCelebracion()
{
    // ✨ CELEBRACIÓN CON EFECTOS VISUALES ESTABLES
    
    // Efectos visuales instantáneos en múltiples posiciones
    for (int i = 0; i < 8; i++) {
        qreal x = 200 + QRandomGenerator::global()->bounded(800);
        qreal y = 100 + QRandomGenerator::global()->bounded(400);
        QColor color = QColor::fromHsv(QRandomGenerator::global()->bounded(360), 255, 255);
        crearEfectoExplosion(QPointF(x, y), color);
    }
    
    // ✨ Mensaje de victoria con animación de escala
    QGraphicsTextItem *mensajeVictoria = new QGraphicsTextItem();
    mensajeVictoria->setPlainText("🎉 ¡VICTORIA! 🎉");
    mensajeVictoria->setDefaultTextColor(QColor(255, 215, 0));  // Dorado
    
    QFont fontVictoria("Arial", 48, QFont::Black);
    mensajeVictoria->setFont(fontVictoria);
    mensajeVictoria->setZValue(2000);
    
    // Centrar en la escena
    QRectF rectMensaje = mensajeVictoria->boundingRect();
    mensajeVictoria->setPos(600 - rectMensaje.width()/2, 250);
    mensajeVictoria->setTransformOriginPoint(rectMensaje.center());
    
    // Efecto de sombra dorada
    QGraphicsDropShadowEffect *sombra = new QGraphicsDropShadowEffect();
    sombra->setBlurRadius(20);
    sombra->setColor(QColor(255, 215, 0, 180));
    sombra->setOffset(0, 0);
    mensajeVictoria->setGraphicsEffect(sombra);
    
    escena->addItem(mensajeVictoria);
    
    // Animación de aparición con escala
    mensajeVictoria->setScale(0);
    QPropertyAnimation *animEscala = new QPropertyAnimation(mensajeVictoria, "scale");
    animEscala->setDuration(600);
    animEscala->setStartValue(0.0);
    animEscala->setEndValue(1.2);
    animEscala->setEasingCurve(QEasingCurve::OutElastic);
    animEscala->start(QAbstractAnimation::DeleteWhenStopped);
    
    // Eliminar mensaje después de 2.5 segundos
    QTimer::singleShot(2500, [this, mensajeVictoria]() {
        QPropertyAnimation *animSalida = new QPropertyAnimation(mensajeVictoria, "scale");
        animSalida->setDuration(300);
        animSalida->setStartValue(mensajeVictoria->scale());
        animSalida->setEndValue(0.0);
        animSalida->setEasingCurve(QEasingCurve::InBack);
        
        connect(animSalida, &QPropertyAnimation::finished, [this, mensajeVictoria]() {
            escena->removeItem(mensajeVictoria);
            delete mensajeVictoria;
        });
        
        animSalida->start(QAbstractAnimation::DeleteWhenStopped);
    });
    
    // Actualizar estadísticas
    partidasJugadas++;
    partidasGanadas++;
    
    int minMovimientos = (int)pow(2, numDiscos) - 1;
    if (contadorMovimientos <= minMovimientos * 1.2) { // 20% de margen
        if (contadorMovimientos < recordMovimientos) {
            recordMovimientos = contadorMovimientos;
            lblRecord->setText(QString("🏆 Récord: %1").arg(recordMovimientos));
        }
    }
    
    guardarEstadisticas();
    
    // ✨ Diálogo de victoria simple
    QTimer::singleShot(1000, [this, minMovimientos]() {
        QMessageBox msgBox;
        msgBox.setWindowTitle("🎊 ¡VICTORIA ÉPICA! 🎊");
        msgBox.setIcon(QMessageBox::Information);
        
        QString eficiencia = contadorMovimientos <= minMovimientos ? "¡PERFECTO! 🌟" : 
                            contadorMovimientos <= minMovimientos * 1.2 ? "¡EXCELENTE! ⭐" : 
                            contadorMovimientos <= minMovimientos * 1.5 ? "¡MUY BIEN! 👍" : "¡COMPLETADO! ✓";
        
        msgBox.setText(QString(
            "<h2>� ¡LO LOGRASTE! �</h2>"
            "<p style='font-size:14pt;'><b>Eficiencia:</b> %1</p>"
            "<hr>"
            "<p><b>📊 Estadísticas:</b></p>"
            "<ul>"
            "<li>Movimientos realizados: <b>%2</b></li>"
            "<li>Movimientos óptimos: <b>%3</b></li>"
            "<li>Tiempo: <b>%4:%5</b></li>"
            "<li>🏆 Tu récord: <b>%6</b></li>"
            "</ul>"
        ).arg(eficiencia)
         .arg(contadorMovimientos)
         .arg(minMovimientos)
         .arg(tiempoTranscurrido / 60, 2, 10, QChar('0'))
         .arg(tiempoTranscurrido % 60, 2, 10, QChar('0'))
         .arg(recordMovimientos == 999999 ? contadorMovimientos : recordMovimientos));
        
        msgBox.exec();
    });
}

QString MainWindow::obtenerMensajeMotivacional()
{
    QStringList mensajes = {
        "¡Excelente movimiento! 🌟",
        "¡Vas muy bien! 💪",
        "¡Sigue así! 🚀",
        "¡Perfecto! ✨",
        "¡Increíble estrategia! 🧠"
    };
    return mensajes[QRandomGenerator::global()->bounded(mensajes.size())];
}

QString MainWindow::obtenerTipMovimiento()
{
    QStringList tips = {
        "💡 Tip: Mueve los discos pequeños con frecuencia",
        "💡 Tip: La torre del medio es tu mejor aliada",
        "💡 Tip: Piensa en la recursión: mueve n-1, luego 1, luego n-1",
        "💡 Tip: Los movimientos alternan: pequeño, grande, pequeño, grande...",
        "💡 Tip: Para discos pares, alterna pequeño (derecha) y otros discos",
        "💡 Tip: Para discos impares, alterna pequeño (izquierda) y otros discos"
    };
    
    return tips[QRandomGenerator::global()->bounded(tips.size())];
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    // Atajos de teclado
    switch (event->key()) {
    case Qt::Key_Space:
        if (juegoIniciado && !resolviendoAutomatico) {
            resolverDesdeAqui();
        }
        break;
    case Qt::Key_R:
        if (juegoIniciado) {
            reiniciar();
        }
        break;
    case Qt::Key_H:
        mostrarHistorial();
        break;
    case Qt::Key_S:
        guardarPartida();
        break;
    case Qt::Key_L:
        cargarPartida();
        break;
    case Qt::Key_T:
        cambiarTema();
        break;
    case Qt::Key_F1:
        mostrarTutorial();
        break;
    case Qt::Key_Escape:
        if (juegoIniciado) {
            reiniciar();
        }
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::animarMovimiento(Disco *disco, QPointF inicio, QPointF fin)
{
    // ✨ ANIMACIÓN SUAVE Y ESTABLE CON ARCO
    // Calcular punto intermedio (arco hacia arriba)
    QPointF puntoAlto(
        (inicio.x() + fin.x()) / 2,
        qMin(inicio.y(), fin.y()) - 100  // 100 píxeles arriba
    );
    
    // Animación en dos fases: subir y bajar
    QPropertyAnimation *animSubida = new QPropertyAnimation(disco, "pos");
    animSubida->setDuration(velocidadAnimacion / 2);
    animSubida->setStartValue(inicio);
    animSubida->setEndValue(puntoAlto);
    animSubida->setEasingCurve(QEasingCurve::OutQuad);
    
    QPropertyAnimation *animBajada = new QPropertyAnimation(disco, "pos");
    animBajada->setDuration(velocidadAnimacion / 2);
    animBajada->setStartValue(puntoAlto);
    animBajada->setEndValue(fin);
    animBajada->setEasingCurve(QEasingCurve::InQuad);
    
    // Rotación suave durante el movimiento
    QPropertyAnimation *animRotacion = new QPropertyAnimation(disco, "rotation");
    animRotacion->setDuration(velocidadAnimacion);
    animRotacion->setStartValue(0);
    animRotacion->setEndValue(360);
    animRotacion->setEasingCurve(QEasingCurve::Linear);
    
    // Ejecutar en secuencia
    QSequentialAnimationGroup *secuencia = new QSequentialAnimationGroup();
    secuencia->addAnimation(animSubida);
    secuencia->addAnimation(animBajada);
    
    // Ejecutar rotación en paralelo
    QParallelAnimationGroup *grupo = new QParallelAnimationGroup();
    grupo->addAnimation(secuencia);
    grupo->addAnimation(animRotacion);
    
    grupo->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::animarMovimientoEpico(Disco *disco, int desde, int hacia)
{
    // ✨ ANIMACIÓN ÉPICA CON ARCO PARABÓLICO Y EFECTOS VISUALES
    // NOTA: Esta función SOLO anima, NO modifica las estructuras de datos de las torres
    
    // Agregar el disco PRIMERO a la torre destino para calcular su posición final
    torres[hacia]->agregarDisco(disco);
    QPointF posicionFinal = disco->pos();  // La torre ya calculó la posición
    
    // Restaurar posición inicial para la animación
    QPointF posicionActual = torres[desde]->calcularPosicionDisco(torres[desde]->obtenerDiscos().size());
    disco->setPos(posicionActual);
    
    // Calcular punto medio del arco (más alto que ambas posiciones)
    qreal alturaPico = qMin(posicionActual.y(), posicionFinal.y()) - 150;  // ✨ Arco alto
    QPointF puntoMedio(
        (posicionActual.x() + posicionFinal.x()) / 2,
        alturaPico
    );
    
    // ✨ FASE 1: Subir con rotación
    QPropertyAnimation *animSubida = new QPropertyAnimation(disco, "pos");
    animSubida->setDuration(velocidadAnimacion);
    animSubida->setStartValue(posicionActual);
    animSubida->setEndValue(puntoMedio);
    animSubida->setEasingCurve(QEasingCurve::OutCubic);
    
    QPropertyAnimation *animRotacionSubida = new QPropertyAnimation(disco, "rotation");
    animRotacionSubida->setDuration(velocidadAnimacion);
    animRotacionSubida->setStartValue(0);
    animRotacionSubida->setEndValue(180);
    animRotacionSubida->setEasingCurve(QEasingCurve::OutCubic);
    
    QPropertyAnimation *animEscalaSubida = new QPropertyAnimation(disco, "scale");
    animEscalaSubida->setDuration(velocidadAnimacion);
    animEscalaSubida->setStartValue(1.0);
    animEscalaSubida->setEndValue(1.2);  // ✨ Agrandar al subir
    animEscalaSubida->setEasingCurve(QEasingCurve::OutCubic);
    
    QParallelAnimationGroup *grupoSubida = new QParallelAnimationGroup();
    grupoSubida->addAnimation(animSubida);
    grupoSubida->addAnimation(animRotacionSubida);
    grupoSubida->addAnimation(animEscalaSubida);
    
    // ✨ FASE 2: Bajar con rebote
    QPropertyAnimation *animBajada = new QPropertyAnimation(disco, "pos");
    animBajada->setDuration(velocidadAnimacion);
    animBajada->setStartValue(puntoMedio);
    animBajada->setEndValue(posicionFinal);
    animBajada->setEasingCurve(QEasingCurve::OutBounce);  // ✨ Rebote al aterrizar
    
    QPropertyAnimation *animRotacionBajada = new QPropertyAnimation(disco, "rotation");
    animRotacionBajada->setDuration(velocidadAnimacion);
    animRotacionBajada->setStartValue(180);
    animRotacionBajada->setEndValue(360);
    animRotacionBajada->setEasingCurve(QEasingCurve::OutBounce);
    
    QPropertyAnimation *animEscalaBajada = new QPropertyAnimation(disco, "scale");
    animEscalaBajada->setDuration(velocidadAnimacion);
    animEscalaBajada->setStartValue(1.2);
    animEscalaBajada->setEndValue(1.0);  // ✨ Volver a tamaño normal
    animEscalaBajada->setEasingCurve(QEasingCurve::OutBounce);
    
    QParallelAnimationGroup *grupoBajada = new QParallelAnimationGroup();
    grupoBajada->addAnimation(animBajada);
    grupoBajada->addAnimation(animRotacionBajada);
    grupoBajada->addAnimation(animEscalaBajada);
    
    // Secuencia completa
    QSequentialAnimationGroup *secuencia = new QSequentialAnimationGroup();
    secuencia->addAnimation(grupoSubida);
    secuencia->addAnimation(grupoBajada);
    
    // ✨ Efectos visuales al completar
    connect(secuencia, &QSequentialAnimationGroup::finished, [this, disco]() {
        // Efecto de aterrizaje
        crearEfectoExplosion(disco->scenePos(), QColor(46, 204, 113));
        
        // Restablecer rotación y escala
        disco->setRotation(0);
        disco->setScale(1.0);
    });
    
    secuencia->start(QAbstractAnimation::DeleteWhenStopped);
    
    // ✨ Estela de partículas durante el movimiento
    QTimer *timerEstela = new QTimer();
    int contador = 0;
    connect(timerEstela, &QTimer::timeout, [this, disco, timerEstela, &contador]() mutable {
        contador++;
        if (contador > 20) {  // Durar toda la animación
            timerEstela->stop();
            timerEstela->deleteLater();
            return;
        }
        
        // Crear partícula de estela
        QGraphicsEllipseItem *estela = escena->addEllipse(
            -5, -5, 10, 10,
            QPen(Qt::NoPen),
            QBrush(QColor(52, 152, 219, 180))
        );
        estela->setPos(disco->scenePos());
        estela->setZValue(-1);
        
        // ✨ Desvanecer estela con timer manual
        QTimer *timerFade = new QTimer();
        int pasosFade = 0;
        const int maxPasosFade = 25;
        
        connect(timerFade, &QTimer::timeout, [this, estela, timerFade, &pasosFade, maxPasosFade]() mutable {
            pasosFade++;
            qreal progreso = qreal(pasosFade) / maxPasosFade;
            estela->setOpacity(1.0 - progreso);
            
            if (pasosFade >= maxPasosFade) {
                timerFade->stop();
                escena->removeItem(estela);
                delete estela;
                timerFade->deleteLater();
            }
        });
        
        timerFade->start(20);
    });
    timerEstela->start(30);
}

std::vector<std::pair<int, int>> MainWindow::obtenerEstadoActual()
{
    // Función auxiliar para obtener el estado actual del juego
    return historialMovimientos;
}

void MainWindow::mostrarPantallaJuego()
{
    // Cambiar de pantalla de inicio a pantalla de juego
    vistaGrafica->setScene(escena);
    vistaGrafica->show();
}

void MainWindow::mostrarAcercaDe()
{
    QMessageBox::about(this, "Acerca de Torres de Hanoi",
        "<h2>Torres de Hanoi Profesional</h2>"
        "<p><b>Versión:</b> 2.0</p>"
        "<p><b>Desarrollador:</b> Carlos Vargas</p>"
        "<p><b>Año:</b> 2025</p>"
        "<hr>"
        "<p>Un juego clásico de lógica implementado con Qt6 y C++.</p>"
        "<p><b>Características:</b></p>"
        "<ul>"
        "<li>Animaciones fluidas</li>"
        "<li>Sistema de guardado/carga</li>"
        "<li>Estadísticas y récords</li>"
        "<li>Modo Zen (sin tiempo)</li>"
        "<li>Tutorial interactivo</li>"
        "<li>Efectos visuales profesionales</li>"
        "</ul>"
        "<p><b>Atajos de teclado:</b></p>"
        "<ul>"
        "<li><b>Espacio:</b> Resolver automáticamente</li>"
        "<li><b>R:</b> Reiniciar juego</li>"
        "<li><b>H:</b> Ver historial</li>"
        "<li><b>S:</b> Guardar partida</li>"
        "<li><b>L:</b> Cargar partida</li>"
        "<li><b>T:</b> Cambiar tema</li>"
        "<li><b>F1:</b> Tutorial</li>"
        "<li><b>Esc:</b> Cancelar/Reiniciar</li>"
        "</ul>");
}

void MainWindow::animarParticulas()
{
    // Animar las partículas de fondo (efecto continuo)
    for (auto particula : particulas) {
        qreal y = particula->y() + 2.0;
        if (y > 600) {
            y = -20;
            particula->setX(QRandomGenerator::global()->bounded(900));
        }
        particula->setY(y);
    }
}

void MainWindow::mostrarMensajeFlotante(QString mensaje, QColor color)
{
    // Crear o actualizar mensaje flotante
    if (!mensajeFlotante) {
        mensajeFlotante = new QGraphicsTextItem();
        escena->addItem(mensajeFlotante);
    }
    
    mensajeFlotante->setPlainText(mensaje);
    mensajeFlotante->setDefaultTextColor(color);
    
    QFont font("Arial", 16, QFont::Bold);
    mensajeFlotante->setFont(font);
    
    // Centrar mensaje
    QRectF rect = mensajeFlotante->boundingRect();
    mensajeFlotante->setPos(450 - rect.width()/2, 100);
    
    // Animar aparición y desaparición
    mensajeFlotante->setOpacity(0);
    QPropertyAnimation *animIn = new QPropertyAnimation(mensajeFlotante, "opacity");
    animIn->setDuration(300);
    animIn->setStartValue(0.0);
    animIn->setEndValue(1.0);
    animIn->setEasingCurve(QEasingCurve::InOutQuad);
    
    QPropertyAnimation *animOut = new QPropertyAnimation(mensajeFlotante, "opacity");
    animOut->setDuration(300);
    animOut->setStartValue(1.0);
    animOut->setEndValue(0.0);
    animOut->setEasingCurve(QEasingCurve::InOutQuad);
    
    QSequentialAnimationGroup *grupo = new QSequentialAnimationGroup();
    grupo->addAnimation(animIn);
    grupo->addPause(2000);
    grupo->addAnimation(animOut);
    grupo->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    // Ajustar vista al redimensionar ventana
    if (vistaGrafica) {
        vistaGrafica->fitInView(escena->sceneRect(), Qt::KeepAspectRatio);
    }
}

// ========== FUNCIONES DRAG AND DROP ✨ ==========

void MainWindow::onDiscoPresionado(Disco *disco)
{
    if (!juegoIniciado || resolviendoAutomatico) {
        return;
    }
    
    // Verificar que este disco esté en la parte superior de alguna torre
    for (int i = 0; i < 3; i++) {
        if (!torres[i]->estaVacia() && torres[i]->obtenerDiscoSuperior() == disco) {
            discoArrastrado = disco;
            torreOrigenDrag = i;
            posicionOriginal = disco->pos();
            
            // Elevar el disco para que se vea arriba de todo
            disco->setZValue(1000);
            disco->setOpacity(0.8);  // Hacerlo semitransparente mientras se arrastra
            
            return;
        }
    }
    
    // Si no es el disco superior, no permitir arrastrarlo
    QMessageBox::warning(this, "Movimiento inválido", 
        "Solo puedes mover el disco que está en la parte superior de una torre.");
    disco->setPos(disco->pos());  // Revertir posición
}

void MainWindow::onDiscoSoltado(Disco *disco, QPointF posicion)
{
    if (!juegoIniciado || resolviendoAutomatico || !discoArrastrado) {
        return;
    }
    
    // Restaurar opacidad y z-value
    disco->setOpacity(1.0);
    disco->setZValue(disco->obtenerTamano());
    
    // Determinar en qué torre se soltó (por posición X)
    int anchoEscena = 1200;
    int separacion = anchoEscena / 3;
    int torreDestino = -1;
    
    for (int i = 0; i < 3; i++) {
        int centroX = separacion / 2 + i * separacion;
        if (qAbs(posicion.x() - centroX) < separacion / 2) {
            torreDestino = i;
            break;
        }
    }
    
    // Si se soltó fuera de las torres o en la misma torre de origen
    if (torreDestino == -1 || torreDestino == torreOrigenDrag) {
        // ✨ ANIMACIÓN ÉPICA DE REGRESO con rotación y rebote
        QPropertyAnimation *animRegreso = new QPropertyAnimation(disco, "pos");
        animRegreso->setDuration(400);
        animRegreso->setStartValue(disco->pos());
        animRegreso->setEndValue(posicionOriginal);
        animRegreso->setEasingCurve(QEasingCurve::OutElastic);  // ✨ Rebote elástico
        
        // ✨ Animación de rotación de error
        QPropertyAnimation *animRotacion = new QPropertyAnimation(disco, "rotation");
        animRotacion->setDuration(400);
        animRotacion->setStartValue(0);
        animRotacion->setEndValue(360);
        animRotacion->setEasingCurve(QEasingCurve::OutBack);
        
        // ✨ Animación de opacidad parpadeante
        QPropertyAnimation *animOpacidad = new QPropertyAnimation(disco, "opacity");
        animOpacidad->setDuration(400);
        animOpacidad->setKeyValueAt(0, 1.0);
        animOpacidad->setKeyValueAt(0.25, 0.5);
        animOpacidad->setKeyValueAt(0.5, 1.0);
        animOpacidad->setKeyValueAt(0.75, 0.5);
        animOpacidad->setKeyValueAt(1, 1.0);
        
        QParallelAnimationGroup *grupo = new QParallelAnimationGroup();
        grupo->addAnimation(animRegreso);
        grupo->addAnimation(animRotacion);
        grupo->addAnimation(animOpacidad);
        grupo->start(QAbstractAnimation::DeleteWhenStopped);
        
        // ✨ Efecto visual de error
        crearEfectoExplosion(disco->scenePos(), QColor(231, 76, 60));
        
        discoArrastrado = nullptr;
        torreOrigenDrag = -1;
        disco->setSeleccionado(false);
        return;
    }
    
    // Intentar mover el disco
    if (verificarMovimientoValido(torreOrigenDrag, torreDestino)) {
        // Quitar disco de torre origen
        torres[torreOrigenDrag]->quitarDisco();
        
        // Agregar disco a torre destino (con animación simple de la torre)
        torres[torreDestino]->agregarDisco(disco);
        
        // ✨ Efecto visual de movimiento exitoso
        crearEfectoExplosion(disco->scenePos(), QColor(46, 204, 113));
        
        contadorMovimientos++;
        historialMovimientos.push_back({torreOrigenDrag, torreDestino});
        
        actualizarEstadisticas();
        actualizarProgreso();
        
        if (juegoCompletado()) {
            timerJuego->stop();
            mostrarCelebracion();
        }
    } else {
        // Movimiento inválido - regresar a posición original con efecto épico
        QMessageBox::warning(this, "❌ Movimiento inválido", 
            "⚠️ No puedes colocar un disco más grande sobre uno más pequeño.");
        
        // ✨ Animación épica de error
        QPropertyAnimation *animRegreso = new QPropertyAnimation(disco, "pos");
        animRegreso->setDuration(500);
        animRegreso->setStartValue(disco->pos());
        animRegreso->setEndValue(posicionOriginal);
        animRegreso->setEasingCurve(QEasingCurve::OutElastic);
        
        QPropertyAnimation *animShake = new QPropertyAnimation(disco, "rotation");
        animShake->setDuration(500);
        animShake->setKeyValueAt(0, 0);
        animShake->setKeyValueAt(0.2, -15);
        animShake->setKeyValueAt(0.4, 15);
        animShake->setKeyValueAt(0.6, -10);
        animShake->setKeyValueAt(0.8, 10);
        animShake->setKeyValueAt(1, 0);
        
        QParallelAnimationGroup *grupo = new QParallelAnimationGroup();
        grupo->addAnimation(animRegreso);
        grupo->addAnimation(animShake);
        grupo->start(QAbstractAnimation::DeleteWhenStopped);
        
        crearEfectoExplosion(disco->scenePos(), QColor(231, 76, 60));
    }
    
    discoArrastrado = nullptr;
    torreOrigenDrag = -1;
    disco->setSeleccionado(false);
}

void MainWindow::actualizarColoresTema(TemaVisual tema)
{
    // Verificar que la escena esté inicializada
    if (!escena) return;
    
    // Simplemente actualizar el fondo de la escena según el tema
    // Los discos y torres ya tienen sus colores por defecto
    
    switch (tema) {
        case TEMA_DARK_MODERN:
            escena->setBackgroundBrush(QBrush(QColor(26, 26, 46)));
            break;
        
        case TEMA_LIGHT_ELEGANT:
            escena->setBackgroundBrush(QBrush(QColor(255, 255, 255)));
            break;
        
        case TEMA_NEON_CYBERPUNK:
            escena->setBackgroundBrush(QBrush(QColor(0, 0, 0)));
            break;
        
        case TEMA_GLASSMORPHISM:
            escena->setBackgroundBrush(QBrush(QColor(227, 242, 253)));  // Azul muy claro
            break;
        
        case TEMA_SUNSET_GRADIENT:
            escena->setBackgroundBrush(QBrush(QColor(255, 154, 158)));
            break;
    }
}

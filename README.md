# 🗼 Torres de Hanoi - Versión Profesional Interactiva

![Qt](https://img.shields.io/badge/Qt-6.9.2-green.svg)
![C++](https://img.shields.io/badge/C++-17-blue.svg)
![Lines](https://img.shields.io/badge/lines-3590-yellow.svg)
![Status](https://img.shields.io/badge/status-production-success.svg)

## 📋 Información del Proyecto

**Universidad Politécnica de Victoria**  
**Materia**: Estructura de Datos
**Proyecto**: Torres de Hanoi Interactivo con Interfaz Gráfica Moderna

### 👥 Equipo de Desarrollo

| Nombre | Rol |
|--------|-----|
| **Carlos Adrian Vargas Saldierna** | Desarrollador Principal / Arquitecto de Software |
| **Eliezer Mores Oyervides** | Desarrollador / Algoritmos |
| **Carlos Guillermo Moncada Ortiz** | Desarrollador / Interfaz Gráfica |
| **Mauricio Garcia Cervantes** | Desarrollador / Testing |

### 📅 Información de Desarrollo
- **Fecha**: Octubre 2025
- **Versión**: 2.0 Professional Edition
- **Líneas de Código**: 3,590
- **Lenguaje**: C++17
- **Framework**: Qt6 6.9.2

---

## 🎮 Descripción del Proyecto

**Torres de Hanoi Professional** es una implementación completa y moderna del clásico problema matemático de las Torres de Hanoi. Este proyecto combina algoritmos recursivos avanzados, estructuras de datos eficientes, interfaz gráfica profesional con Qt6, y características innovadoras como **drag & drop**, **5 temas visuales épicos**, **sistema de audio**, y **resolver desde estado arbitrario**.

### 🎯 Objetivos Académicos

1. **Dominar Recursividad**: Implementar y visualizar el algoritmo recursivo clásico
2. **Estructuras de Datos**: Usar pilas (stacks) y vectores de forma efectiva
3. **Programación Orientada a Objetos**: Diseño con clases, herencia y polimorfismo
4. **Interfaz Gráfica**: Desarrollo profesional con Qt Graphics View Framework
5. **Patrones de Diseño**: MVC, Signals/Slots, Observer Pattern

---

## ✨ Características Principales

### 🎨 **5 Temas Visuales Épicos**

| Tema | Descripción | Colores Principal |
|------|-------------|-------------------|
| � **Dark Modern** | Gradientes púrpura-azul oscuros | `#667eea` → `#764ba2` |
| ☀️ **Light Elegant** | Diseño limpio azul cielo | `#4facfe` → `#00f2fe` |
| ⚡ **Neon Cyberpunk** | Bordes neón vibrantes | `#00ff41`, `#00ffff` |
| 💎 **Glassmorphism** | Efectos translúcidos blur | Azul-morado degradado |
| 🌅 **Sunset Dream** | Gradientes cálidos rosa-coral | `#f093fb` → `#f5576c` |

### 🎮 **Modos de Juego Avanzados**

#### 1. **Juego Manual con Drag & Drop**
- ✅ Arrastra discos con el mouse naturalmente
- ✅ Validación en tiempo real de reglas de Hanoi
- ✅ Efectos hover y feedback visual
- ✅ Animaciones suaves de movimiento

#### 2. **Resolver Automático (Algoritmo Recursivo)**
- ✅ Implementación clásica optimizada
- ✅ Complejidad: O(2^n - 1) movimientos
- ✅ Animaciones con velocidad ajustable
- ✅ Visualización paso a paso

#### 3. **Resolver desde Estado Arbitrario** ⭐ (Innovación)
- ✅ Continúa desde cualquier configuración válida
- ✅ Resetea a posición inicial y resuelve
- ✅ Útil cuando te quedas atascado
- ✅ Algoritmo inteligente en 2 fases

### 🔊 **Sistema de Audio Profesional**

Generación programática de sonidos WAV en memoria:

| Sonido | Tipo | Frecuencia |
|--------|------|------------|
| 🔊 Movimiento | Sine Wave | C5 (523Hz) → E5 (659Hz) |
| ❌ Error | Square Wave | 440Hz (áspero) |
| 🎉 Victoria | Acorde Mayor | C-E-G (523/659/784Hz) |
| 🖱️ Hover | Sine Wave | 800Hz |
| 👆 Click | Square Wave | 1000Hz |

```cpp
// Sistema SoundManager con Qt6::Multimedia
QMediaPlayer *movePlayer;
QAudioOutput *audioOutput;
generateWaveform(frequency, duration, waveType);
```

### 📊 **Interfaz Profesional**

- ✅ **Contador de Movimientos**: Actualizados en tiempo real
- ✅ **Movimientos Mínimos**: Cálculo de solución óptima (2^n - 1)
- ✅ **Eficiencia**: Porcentaje vs óptimo
- ✅ **Control de Velocidad**: Slider para animaciones
- ✅ **Historial**: Registro completo de movimientos
- ✅ **Estadísticas**: Récord, partidas jugadas/ganadas

---

## 🏗️ Arquitectura del Proyecto

### 📁 Estructura de Archivos

```
torres_hanoi/
├── 📄 CMakeLists.txt        (54 líneas)   - Build configuration
├── 📄 main.cpp              (12 líneas)   - Entry point
├── 📄 mainwindow.h          (193 líneas)  - Main window header
├── 📄 mainwindow.cpp        (2086 líneas) - Main logic ⭐
├── 📄 disco.h               (44 líneas)   - Disk class header
├── 📄 disco.cpp             (173 líneas)  - Disk implementation
├── 📄 torre.h               (43 líneas)   - Tower class header
├── 📄 torre.cpp             (179 líneas)  - Tower implementation
├── 📄 soundmanager.h        (73 líneas)   - Audio system header
├── 📄 soundmanager.cpp      (327 líneas)  - Audio implementation
├── 📄 funciones_extra.cpp   (460 líneas)  - Extra utilities
└── 📁 build/                             - Compiled binaries
```

**Total**: 3,590 líneas de código C++

### 🧩 Clases Principales

#### 1. `MainWindow` (2086 líneas)
**Propósito**: Controlador principal de la aplicación

**Miembros Clave**:
```cpp
class MainWindow : public QMainWindow {
    // Estructuras de datos
    std::vector<Torre*> torres;                    // 3 torres
    std::vector<Disco*> discos;                    // N discos
    std::vector<std::pair<int,int>> movimientos;   // Cola de movimientos
    std::vector<std::pair<int,int>> historialMovimientos;  // Historial
    
    // Temas visuales
    enum TemaVisual {
        TEMA_DARK_MODERN,
        TEMA_LIGHT_ELEGANT,
        TEMA_NEON_CYBERPUNK,
        TEMA_GLASSMORPHISM,
        TEMA_SUNSET_GRADIENT
    };
    TemaVisual temaActual;
    
    // Sistema de audio
    SoundManager *soundManager;
    
    // Métodos principales
    void iniciarJuego();
    void resolverAutomatico();
    void resolverDesdeEstado(std::vector<std::stack<int>> estado);
    void moverDisco(int desde, int hacia, bool animado = true);
    bool verificarMovimientoValido(int desde, int hacia);
    void aplicarTemaModerno(TemaVisual tema);
};
```

**Funcionalidades Implementadas**:
- ✅ Iniciar juego (3-8 discos)
- ✅ Resolver automático
- ✅ Resolver desde estado
- ✅ Drag and drop
- ✅ Cambiar tema
- ✅ Historial
- ✅ Estadísticas
- ✅ Guardar/Cargar partida
- ✅ Control de velocidad
- ✅ Validación de movimientos

#### 2. `Disco` (173 líneas)
**Propósito**: Representar y gestionar discos gráficos

**Herencia**: `QObject`, `QGraphicsRectItem`

**Características**:
```cpp
class Disco : public QObject, public QGraphicsRectItem {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)  // Para animaciones
    
signals:
    void discoPresionado(Disco *disco);            // Drag & drop
    void discoSoltado(Disco *disco, QPointF pos);
    
protected:
    void paint(QPainter *painter, ...);            // Gradientes 3D
    void hoverEnterEvent(...);                     // Efectos hover
    void mousePressEvent(...);                     // Drag inicio
    void mouseReleaseEvent(...);                   // Drag fin
};
```

**Efectos Visuales**:
- Gradientes lineales 3D
- Cambio de color al hover
- Resaltado al seleccionar
- Sombras dinámicas

#### 3. `Torre` (179 líneas)
**Propósito**: Gestionar pilas de discos

**Estructura de Datos**: `std::vector<Disco*>`

```cpp
class Torre : public QObject, public QGraphicsRectItem {
    std::vector<Disco*> discos;  // Pila de discos
    
public:
    void agregarDisco(Disco *disco);
    Disco* quitarDisco();
    Disco* obtenerDiscoSuperior() const;
    bool estaVacia() const;
    QPointF calcularPosicionDisco(int posicion);
};
```

#### 4. `SoundManager` (327 líneas)
**Propósito**: Sistema de audio profesional

```cpp
class SoundManager : public QObject {
    QMediaPlayer *movePlayer;
    QMediaPlayer *victoryPlayer;
    QMediaPlayer *errorPlayer;
    QAudioOutput *audioOutputs[6];
    QBuffer *soundBuffers[6];
    
    QByteArray generateWaveform(int freq, int duration, WaveType type);
    QByteArray generateChord(std::vector<int> frequencies);
    QByteArray createWavHeader(int dataSize, int sampleRate);
};
```

**Generación de Audio**:
- Sine wave (tonos puros)
- Square wave (tonos ásperos)
- Triangle wave (tonos suaves)
- Acordes (múltiples frecuencias)
- Sample rate: 44100 Hz
- Format: PCM 16-bit mono

---

## 🧮 Algoritmos Implementados

### 1. **Algoritmo Recursivo Clásico**

```cpp
void MainWindow::calcularSolucion(int n, int origen, int destino, int auxiliar) {
    if (n <= 0) return;
    
    // Fase 1: Mover n-1 discos a torre auxiliar
    calcularSolucion(n - 1, origen, auxiliar, destino);
    
    // Fase 2: Mover disco más grande a destino
    movimientos.push_back({origen, destino});
    
    // Fase 3: Mover n-1 discos desde auxiliar a destino
    calcularSolucion(n - 1, auxiliar, destino, origen);
}
```

**Análisis de Complejidad**:
- **Temporal**: O(2^n - 1)
- **Espacial**: O(n) por la pila de recursión
- **Movimientos mínimos**:
  - 3 discos = 7 movimientos
  - 4 discos = 15 movimientos
  - 5 discos = 31 movimientos
  - 8 discos = 255 movimientos

### 2. **Resolver desde Estado Arbitrario** ⭐

```cpp
void MainWindow::resolverDesdeEstado(std::vector<std::stack<int>> estado) {
    // ESTRATEGIA EN 2 FASES:
    
    // FASE 1: Resetear - Mover todos los discos a torre inicial (A)
    for (int disco = 1; disco <= numDiscos; disco++) {
        // Encontrar disco
        int torreActual = buscarDisco(disco, estado);
        
        // Quitar discos encima
        while (hayDiscosEncima(disco, torreActual)) {
            int discoEncima = quitarDiscoSuperior(torreActual);
            moverATemporaria(discoEncima);
        }
        
        // Mover disco a torre A
        moverDisco(torreActual, 0);
    }
    
    // FASE 2: Resolver normalmente de A → C
    hanoi(numDiscos, 0, 2, 1);
}
```

**Innovación**: Este algoritmo permite continuar desde cualquier configuración válida, no solo desde el estado inicial.

### 3. **Validación de Movimientos**

```cpp
bool MainWindow::verificarMovimientoValido(int desde, int hacia) {
    // Regla 1: Torre origen no vacía
    if (torres[desde]->estaVacia()) return false;
    
    // Regla 2: Si destino vacío, siempre válido
    if (torres[hacia]->estaVacia()) return true;
    
    // Regla 3: Disco pequeño sobre disco grande
    int discoOrigen = torres[desde]->obtenerDiscoSuperior()->obtenerTamano();
    int discoDestino = torres[hacia]->obtenerDiscoSuperior()->obtenerTamano();
    
    return discoOrigen < discoDestino;
}
```

---

## 🎨 Sistema de Temas Dinámicos

### Implementación Técnica

```cpp
QString MainWindow::obtenerEstiloBoton(TemaVisual tema) {
    switch (tema) {
        case TEMA_NEON_CYBERPUNK:
            return "QPushButton {"
                   "    background: transparent;"
                   "    color: #00ff41;"
                   "    border: 2px solid #00ff41;"
                   "    border-radius: 12px;"
                   "}"
                   "QPushButton:hover {"
                   "    background: rgba(0, 255, 65, 0.1);"
                   "    border: 2px solid #00ffff;"
                   "    color: #00ffff;"
                   "}";
        // ... otros temas
    }
}
```

### Personalización por Tema

Cada tema define:
- 🎨 Fondo con gradientes `qlineargradient`
- 📝 Color de texto optimizado para contraste
- 🔘 Estilos de botones (normal, hover, pressed)
- 🖼️ Fondo de escena `QGraphicsScene`
- 🎭 Bordes y efectos visuales

---

## 🛠️ Instalación y Compilación

### **Requisitos del Sistema**

| Componente | Versión Mínima | Recomendada |
|------------|----------------|-------------|
| Qt | 6.0 | 6.9.2 |
| CMake | 3.16 | 3.27+ |
| C++ Compiler | C++17 | GCC 11+/Clang 14+ |
| Sistema Operativo | Linux/Windows/macOS | - |

### **Dependencias Qt6**

```bash
# Arch Linux / CachyOS
sudo pacman -S qt6-base qt6-multimedia cmake gcc

# Ubuntu / Debian
sudo apt install qt6-base-dev qt6-multimedia-dev cmake g++

# Fedora
sudo dnf install qt6-qtbase-devel qt6-qtmultimedia-devel cmake gcc-c++
```

### **Pasos de Compilación**

```bash
# 1. Clonar repositorio
git clone https://github.com/UPV-Programacion-Orientada-a-Objetos/ds-actividad-5-unidad-1-CarlosVargas740.git
cd torres_hanoi

# 2. Crear directorio de build
mkdir build && cd build

# 3. Configurar CMake
cmake ..

# 4. Compilar (usar todos los cores)
make -j$(nproc)

# 5. Ejecutar
./TorresDeHanoi
```

### **Compilación con Audio**

```bash
# Instalar dependencias multimedia
sudo pacman -S qt6-multimedia pipewire-pulse

# Recompilar
cd build
rm -rf * && cmake .. && make -j4
./TorresDeHanoi
```

---

## 🎮 Guía de Uso

### **Controles Básicos**

| Acción | Control |
|--------|---------|
| Iniciar juego | Botón "🎮 Iniciar Juego" |
| Seleccionar discos | SpinBox (3-8 discos) |
| Mover disco (manual) | Arrastrar y soltar con mouse |
| Resolver auto | Botón "🤖 Resolver Automático" |
| Resolver desde aquí | Botón "🔧 Resolver desde Aquí" |
| Reiniciar | Botón "🔄 Reiniciar" |
| Cambiar tema | Botón con icono de tema |
| Ajustar velocidad | Slider "Velocidad" |

### **Reglas del Juego**

1. ✅ Solo se mueve un disco a la vez
2. ✅ Un disco solo puede ir sobre uno más grande
3. ✅ Objetivo: Mover todos de Torre A → Torre C
4. ✅ Usar Torre B como auxiliar

### **Ejemplos de Juego**

**3 Discos** (7 movimientos mínimos):
```
A→C, A→B, C→B, A→C, B→A, B→C, A→C
```

**4 Discos** (15 movimientos mínimos):
```
A→B, A→C, B→C, A→B, C→A, C→B, A→B,
A→C, B→C, B→A, C→A, B→C, A→B, A→C, B→C
```

---

## 📊 Métricas del Proyecto

### **Estadísticas de Código**

| Archivo | Líneas | Descripción |
|---------|--------|-------------|
| `mainwindow.cpp` | 2,086 | Lógica principal |
| `soundmanager.cpp` | 327 | Sistema de audio |
| `mainwindow.h` | 193 | Definiciones |
| `torre.cpp` | 179 | Gestión de torres |
| `disco.cpp` | 173 | Gestión de discos |
| `funciones_extra.cpp` | 460 | Utilidades |
| Otros | 172 | Headers + main |
| **TOTAL** | **3,590** | **Líneas totales** |

### **Funcionalidades Implementadas**

- ✅ **20+** funciones principales
- ✅ **5** temas visuales completos
- ✅ **6** tipos de sonidos
- ✅ **3** modos de juego
- ✅ **15+** efectos visuales
- ✅ **Drag & drop** completamente funcional
- ✅ **Animaciones** suaves con Qt Property Animation
- ✅ **Validación** en tiempo real
- ✅ **Historial** de movimientos

---

## 🎓 Conceptos Aplicados

### **Programación Orientada a Objetos**

- ✅ **Clases**: `MainWindow`, `Disco`, `Torre`, `SoundManager`
- ✅ **Herencia**: `QMainWindow`, `QGraphicsRectItem`, `QObject`
- ✅ **Encapsulamiento**: Miembros privados/públicos/protegidos
- ✅ **Polimorfismo**: Virtual functions, Qt signals/slots
- ✅ **Composición**: MainWindow contiene Torres y Discos

### **Algoritmos y Estructuras de Datos**

- ✅ **Recursividad**: Algoritmo de Torres de Hanoi
- ✅ **Pilas (Stack)**: `std::stack<int>` para torres
- ✅ **Vectores**: `std::vector` para colecciones
- ✅ **Pares**: `std::pair<int,int>` para movimientos
- ✅ **Validación**: Algoritmos de verificación

### **Qt Framework**

- ✅ **Graphics View**: QGraphicsScene, QGraphicsItem
- ✅ **Signals & Slots**: Comunicación entre objetos
- ✅ **Property Animation**: QPropertyAnimation
- ✅ **Multimedia**: QMediaPlayer, QAudioOutput
- ✅ **Stylesheets**: QSS para temas dinámicos
- ✅ **Event Handling**: Mouse events, hover events

### **Patrones de Diseño**

- ✅ **MVC**: Model-View-Controller
- ✅ **Observer**: Signals/Slots de Qt
- ✅ **Singleton**: SoundManager
- ✅ **Strategy**: Diferentes algoritmos de resolución

---

## 🐛 Solución de Problemas

### **Error: Qt6 no encontrado**
```bash
# Verificar instalación
which qmake6
qmake6 --version

# Reinstalar
sudo pacman -S qt6-base qt6-multimedia
```

### **Error de compilación: C++17**
```bash
# CMakeLists.txt debe tener:
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

### **No hay sonido**
```bash
# Instalar dependencias multimedia
sudo pacman -S qt6-multimedia pipewire-pulse

# Verificar PipeWire
systemctl --user status pipewire
```

### **Crash al iniciar**
```bash
# Compilar en modo debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
gdb ./TorresDeHanoi
```

---

## 📚 Referencias y Recursos

### **Documentación**
- [Qt6 Documentation](https://doc.qt.io/qt-6/)
- [Qt Graphics View Framework](https://doc.qt.io/qt-6/graphicsview.html)
- [Qt Multimedia](https://doc.qt.io/qt-6/qtmultimedia-index.html)
- [C++17 Reference](https://en.cppreference.com/w/cpp/17)

### **Algoritmo Torres de Hanoi**
- [Wikipedia - Torres de Hanoi](https://es.wikipedia.org/wiki/Torres_de_Hanoi)
- [Análisis matemático](https://www.cut-the-knot.org/recurrence/hanoi.shtml)

### **Qt Stylesheets**
- [Qt Style Sheets Reference](https://doc.qt.io/qt-6/stylesheet-reference.html)
- [Qt Style Sheets Examples](https://doc.qt.io/qt-6/stylesheet-examples.html)

---

## 🏆 Logros del Proyecto

### **Técnicos**
✅ 3,590 líneas de código C++ profesional  
✅ Arquitectura limpia y modular  
✅ 5 temas visuales completamente funcionales  
✅ Sistema de audio generado programáticamente  
✅ Drag & drop nativo y fluido  
✅ Animaciones suaves con Qt Property Animation  
✅ Algoritmo innovador "resolver desde estado"  
✅ Sin memory leaks (gestión automática Qt)  

### **Educativos**
✅ Dominio de recursividad y complejidad algorítmica  
✅ Uso avanzado de estructuras de datos (pilas, vectores)  
✅ Programación orientada a objetos aplicada  
✅ Desarrollo profesional con Qt6  
✅ Patrones de diseño implementados  

### **Creativos**
✅ Diseño visual moderno y atractivo  
✅ 5 temas únicos con identidad propia  
✅ Efectos visuales profesionales  
✅ Experiencia de usuario intuitiva  

---

## 📄 Licencia

Este proyecto fue desarrollado con fines educativos para la **Universidad Politécnica de Victoria**.

**Uso Académico** - © 2025 Equipo Torres de Hanoi

---

## 👏 Agradecimientos

- **Universidad Politécnica de Victoria** - Formación en POO y Estructuras de Datos
- **Profesores** - Guía y mentoría en el desarrollo
- **Comunidad Qt** - Documentación y recursos
- **Stack Overflow** - Solución de problemas técnicos
- **GitHub Education** - Plataforma de desarrollo colaborativo

---

## 📞 Contacto

**Repositorio**: [ds-actividad-5-unidad-1-CarlosVargas740](https://github.com/UPV-Programacion-Orientada-a-Objetos/ds-actividad-5-unidad-1-CarlosVargas740)

**Organización**: [UPV-Programacion-Orientada-a-Objetos](https://github.com/UPV-Programacion-Orientada-a-Objetos)

---

<div align="center">

## 🗼 Torres de Hanoi Professional Edition 🗼

**Desarrollado con ❤️ usando C++17 y Qt6**

*Programación Estructurada - Universidad Politécnica de Valencia*

![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)
![Code Quality](https://img.shields.io/badge/code%20quality-A+-blue.svg)
![Maintained](https://img.shields.io/badge/maintained-yes-success.svg)

</div>
bash
cd torres_hanoi
mkdir build
cd build
cmake ..
make
./torres_hanoi
```

### Opción 2: Compilar con qmake

```bash
cd torres_hanoi
qmake torres_hanoi.pro
make
./torres_hanoi
```

### Opción 3: Compilar directamente con g++

Si tienes Qt6 instalado pero prefieres compilar manualmente:

```bash
cd torres_hanoi
g++ -std=c++17 -fPIC -I/usr/include/x86_64-linux-gnu/qt6 \
    -I/usr/include/x86_64-linux-gnu/qt6/QtWidgets \
    -I/usr/include/x86_64-linux-gnu/qt6/QtGui \
    -I/usr/include/x86_64-linux-gnu/qt6/QtCore \
    main.cpp mainwindow.cpp disco.cpp torre.cpp \
    -lQt6Widgets -lQt6Gui -lQt6Core -o torres_hanoi
./torres_hanoi
```

### Instalación de Qt6 (si no lo tienes)

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install qt6-base-dev qt6-base-dev-tools
```

**Fedora:**
```bash
sudo dnf install qt6-qtbase-devel
```

**Arch Linux:**
```bash
sudo pacman -S qt6-base
```

**macOS (con Homebrew):**
```bash
brew install qt@6
```

**Windows:**
Descarga el instalador oficial desde: https://www.qt.io/download

## 🎮 Cómo Jugar

### Inicio
1. Selecciona el número de discos (3-8) con el SpinBox
2. Haz click en "🎮 Iniciar Juego"
3. Los discos aparecerán apilados en la torre izquierda (Torre A)

### Modo Manual
1. Click en el disco superior de una torre para seleccionarlo (se ilumina)
2. Click en otra torre para moverlo ahí
3. Solo puedes mover un disco sobre uno más grande
4. El objetivo es mover todos los discos a la torre derecha (Torre C)

### Modo Automático
1. Click en "🤖 Resolver Automático" para ver la solución completa
2. Ajusta la velocidad con el slider si es muy rápida o lenta
3. La solución usa el algoritmo óptimo (2^n - 1 movimientos)

### Resolver desde Estado Actual
1. Juega manualmente algunos movimientos
2. Si te atascas, click en "⚡ Resolver desde aquí"
3. El algoritmo completará el puzzle desde tu posición actual

### Otras Funciones
- **🔄 Reiniciar**: Vuelve al menú inicial
- **🌙 Tema Oscuro / ☀️ Tema Claro**: Cambia el esquema de colores
- **Slider de Velocidad**: Controla qué tan rápido se mueven los discos en modo automático

## 📐 Algoritmo

El juego implementa el algoritmo recursivo clásico de Torres de Hanoi:

```cpp
void moverDiscos(int n, Torre origen, Torre destino, Torre auxiliar) {
    if (n == 1) {
        mover(origen, destino);
        return;
    }
    moverDiscos(n-1, origen, auxiliar, destino);
    mover(origen, destino);
    moverDiscos(n-1, auxiliar, destino, origen);
}
```

**Complejidad**: O(2^n) movimientos, siendo n el número de discos.

Para n discos, el número mínimo de movimientos es: **2^n - 1**

Ejemplos:
- 3 discos = 7 movimientos
- 4 discos = 15 movimientos
- 5 discos = 31 movimientos
- 6 discos = 63 movimientos
- 7 discos = 127 movimientos
- 8 discos = 255 movimientos

## 🎨 Características Visuales

- **Discos con Gradientes**: Cada disco tiene un gradiente radial para efecto 3D
- **Sombras Dinámicas**: Sombras suaves en discos y torres
- **Efectos Hover**: Iluminación al pasar el mouse
- **Animaciones Bounce**: Los discos "rebotan" al posicionarse
- **Colores Vibrantes**: 8 colores diferentes para los discos
- **Torres Realistas**: Postes con efecto de brillo y base sólida
- **Tema Oscuro/Claro**: Dos esquemas de colores completos

## 📊 Estadísticas

El juego muestra en tiempo real:
- **Movimientos**: Cantidad de movimientos realizados
- **Mínimo**: Número mínimo de movimientos posible (2^n - 1)
- **Tiempo**: Cronómetro en formato MM:SS

Al completar el juego, se muestra un diálogo con:
- Total de movimientos
- Comparación con el óptimo
- Tiempo total empleado

## 🏗️ Arquitectura del Código

### Clases Principales

**MainWindow** (`mainwindow.h/cpp`)
- Clase principal que gestiona toda la interfaz
- Controla el flujo del juego
- Maneja las animaciones y la lógica

**Torre** (`torre.h/cpp`)
- Representa una torre (poste + base)
- Maneja la pila de discos
- Efectos visuales y hover

**Disco** (`disco.h/cpp`)
- Representa un disco individual
- Manejo de selección y hover
- Renderizado con gradientes y efectos

### Patrones de Diseño Utilizados

- **Observer**: Uso de signals/slots de Qt
- **Component**: Composición de QGraphicsItems
- **Strategy**: Diferentes algoritmos de resolución

## 🐛 Solución de Problemas

### Error: "Qt6 not found"
```bash
# Ubuntu/Debian
sudo apt install qt6-base-dev

# Actualiza la variable de entorno
export Qt6_DIR=/usr/lib/x86_64-linux-gnu/cmake/Qt6
```

### Error: "MOC not found"
```bash
export CMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu/cmake/Qt6
```

### Compilación lenta
Usa compilación paralela:
```bash
make -j$(nproc)
```

## 📝 Licencia

Este proyecto está bajo la licencia MIT. Siéntete libre de usar, modificar y distribuir.

## 👨‍💻 Autor

Creado como proyecto educativo para demostrar:
- Programación orientada a objetos en C++
- Desarrollo de GUI con Qt6
- Algoritmos recursivos
- Animaciones y efectos visuales

## 🎓 Propósito Educativo

Este proyecto es ideal para:
- Aprender Qt6 y desarrollo de interfaces gráficas
- Entender algoritmos recursivos
- Practicar programación orientada a objetos
- Estudiar el problema clásico de Torres de Hanoi

## 🚀 Mejoras Futuras

Posibles extensiones:
- [ ] Tabla de récords
- [ ] Más temas visuales
- [ ] Sonidos y efectos de audio
- [ ] Modo multijugador
- [ ] Variantes del juego (4 torres, restricciones adicionales)
- [ ] Tutorial interactivo
- [ ] Replay de partidas

---

¡Disfruta jugando y aprendiendo con Torres de Hanoi! 🗼✨

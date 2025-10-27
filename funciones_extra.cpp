// Funciones auxiliares profesionales agregadas a mainwindow.cpp
// Copia estas funciones al final de tu mainwindow.cpp

void MainWindow::reproducirSonidoMovimiento()
{
    // Efecto visual de sonido (sin audio real, solo visual)
    crearEfectoExplosion(QPointF(450, 200), QColor(52, 152, 219));
}

void MainWindow::mostrarHistorial()
{
    QString historial = "<h2 style='color: #3498db;'>📜 Historial de Movimientos</h2>";
    historial += "<table style='width: 100%; font-size: 14px;'>";
    historial += "<tr style='background: #ecf0f1;'><th>Movimiento</th><th>Desde</th><th>Hacia</th></tr>";
    
    char torres[] = {'A', 'B', 'C'};
    for (size_t i = 0; i < historialMovimientos.size(); i++) {
        QString fondo = (i % 2 == 0) ? "#ffffff" : "#f8f9fa";
        historial += QString("<tr style='background: %1;'><td>%2</td><td>Torre %3</td><td>Torre %4</td></tr>")
            .arg(fondo)
            .arg(i + 1)
            .arg(torres[historialMovimientos[i].first])
            .arg(torres[historialMovimientos[i].second]);
    }
    
    historial += "</table>";
    historial += QString("<p style='margin-top: 20px; color: #27ae60;'><b>Total de movimientos: %1</b></p>").arg(historialMovimientos.size());
    
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
        mostrarMensajeFlotante("⚠ No hay partida en curso", QColor(230, 126, 34));
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
        mostrarMensajeFlotante("💾 Partida guardada exitosamente", QColor(46, 204, 113));
    } else {
        mostrarMensajeFlotante("❌ Error al guardar partida", QColor(231, 76, 60));
    }
}

void MainWindow::cargarPartida()
{
    QFile archivo("partida_hanoi.dat");
    if (!archivo.exists()) {
        mostrarMensajeFlotante("⚠ No hay partida guardada", QColor(230, 126, 34));
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
        
        mostrarMensajeFlotante("📂 Partida cargada exitosamente", QColor(52, 152, 219));
    } else {
        mostrarMensajeFlotante("❌ Error al cargar partida", QColor(231, 76, 60));
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
    stats += QString("<p style='font-size: 18px;'><b>⭐ Mejor record:</b> %1 movimientos</p>").arg(recordMovimientos == 999999 ? 0 : recordMovimientos);
    
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
        mostrarMensajeFlotante("🧘 Modo Zen activado - Sin límite de tiempo", QColor(155, 89, 182));
        timerJuego->stop();
        lblTiempo->setText("⏱ Modo Zen ∞");
    } else {
        mostrarMensajeFlotante("⏱ Modo Normal activado", QColor(52, 152, 219));
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
        "<li>Piensa antes de mover - cada disco pequeño debe "dar paso" a los grandes</li>"
        "<li>La solución óptima para n discos es: <b>2^n - 1</b> movimientos</li>"
        "<li>Usa la Torre B como "auxiliar" para movimientos intermedios</li>"
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
    int numParticulas = 15;
    for (int i = 0; i < numParticulas; i++) {
        qreal angulo = (360.0 / numParticulas) * i;
        qreal radianes = angulo * M_PI / 180.0;
        
        QGraphicsEllipseItem *particula = escena->addEllipse(
            posicion.x() - 5, posicion.y() - 5, 10, 10,
            QPen(Qt::NoPen),
            QBrush(color)
        );
        
        efectosExplosion.push_back(particula);
        
        // Animar partícula
        QPropertyAnimation *animX = new QPropertyAnimation(particula, "x");
        animX->setDuration(800);
        animX->setStartValue(posicion.x());
        animX->setEndValue(posicion.x() + cos(radianes) * 80);
        animX->setEasingCurve(QEasingCurve::OutQuad);
        
        QPropertyAnimation *animY = new QPropertyAnimation(particula, "y");
        animY->setDuration(800);
        animY->setStartValue(posicion.y());
        animY->setEndValue(posicion.y() + sin(radianes) * 80);
        animY->setEasingCurve(QEasingCurve::OutQuad);
        
        QPropertyAnimation *animOpacity = new QPropertyAnimation(particula, "opacity");
        animOpacity->setDuration(800);
        animOpacity->setStartValue(1.0);
        animOpacity->setEndValue(0.0);
        
        QParallelAnimationGroup *grupo = new QParallelAnimationGroup();
        grupo->addAnimation(animX);
        grupo->addAnimation(animY);
        grupo->addAnimation(animOpacity);
        
        connect(grupo, &QParallelAnimationGroup::finished, [this, particula]() {
            escena->removeItem(particula);
            delete particula;
        });
        
        grupo->start(QAbstractAnimation::DeleteWhenStopped);
    }
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
    reproducirEfectoVisual("victoria");
    mostrarMensajeFlotante("🎉 ¡FELICIDADES! ¡LO LOGRASTE! 🎉", QColor(46, 204, 113));
    
    // Actualizar estadísticas
    partidasJugadas++;
    partidasGanadas++;
    
    int minMovimientos = (int)pow(2, numDiscos) - 1;
    if (contadorMovimientos <= minMovimientos * 1.2) { // 20% de margen
        if (contadorMovimientos < recordMovimientos) {
            recordMovimientos = contadorMovimientos;
            mostrarMensajeFlotante("🏆 ¡NUEVO RÉCORD PERSONAL!", QColor(241, 196, 15));
        }
    }
    
    guardarEstadisticas();
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
        if (stackedWidget->currentIndex() == 1) {
            stackedWidget->setCurrentIndex(0);
        }
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

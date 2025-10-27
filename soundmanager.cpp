#include "soundmanager.h"
#include <QDebug>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

SoundManager::SoundManager(QObject *parent)
    : QObject(parent)
    , m_volume(70)
    , m_muted(false)
{
    qDebug() << "🎵 Inicializando sistema de sonidos...";
    
    // Crear reproductores y salidas de audio
    m_movePlayer = new QMediaPlayer(this);
    m_victoryPlayer = new QMediaPlayer(this);
    m_errorPlayer = new QMediaPlayer(this);
    m_hoverPlayer = new QMediaPlayer(this);
    m_clickPlayer = new QMediaPlayer(this);
    m_musicPlayer = new QMediaPlayer(this);
    
    m_moveOutput = new QAudioOutput(this);
    m_victoryOutput = new QAudioOutput(this);
    m_errorOutput = new QAudioOutput(this);
    m_hoverOutput = new QAudioOutput(this);
    m_clickOutput = new QAudioOutput(this);
    m_musicOutput = new QAudioOutput(this);
    
    qDebug() << "✓ Reproductores creados";
    
    // Conectar reproductores con salidas
    m_movePlayer->setAudioOutput(m_moveOutput);
    m_victoryPlayer->setAudioOutput(m_victoryOutput);
    m_errorPlayer->setAudioOutput(m_errorOutput);
    m_hoverPlayer->setAudioOutput(m_hoverOutput);
    m_clickPlayer->setAudioOutput(m_clickOutput);
    m_musicPlayer->setAudioOutput(m_musicOutput);
    
    qDebug() << "✓ Salidas de audio conectadas";
    
    // Configurar volumen
    m_moveOutput->setVolume(m_volume / 100.0);
    m_victoryOutput->setVolume(m_volume / 100.0);
    m_errorOutput->setVolume(m_volume / 100.0);
    m_hoverOutput->setVolume(m_volume / 100.0);
    m_clickOutput->setVolume(m_volume / 100.0);
    m_musicOutput->setVolume(m_volume / 200.0); // Música más baja
    
    qDebug() << "✓ Volumen configurado:" << m_volume << "%";
    
    // Conectar señales de error
    connect(m_movePlayer, &QMediaPlayer::errorOccurred, this, [](QMediaPlayer::Error error, const QString &errorString) {
        qDebug() << "❌ Error en movePlayer:" << error << errorString;
    });
    connect(m_victoryPlayer, &QMediaPlayer::errorOccurred, this, [](QMediaPlayer::Error error, const QString &errorString) {
        qDebug() << "❌ Error en victoryPlayer:" << error << errorString;
    });
    
    setupSounds();
    
    qDebug() << "🎵 Sistema de sonidos profesional inicializado";
}

SoundManager::~SoundManager()
{
    // Los QMediaPlayer se eliminarán automáticamente por ser hijos de este objeto
    if (m_moveBuffer) delete m_moveBuffer;
    if (m_victoryBuffer) delete m_victoryBuffer;
    if (m_errorBuffer) delete m_errorBuffer;
    if (m_hoverBuffer) delete m_hoverBuffer;
    if (m_clickBuffer) delete m_clickBuffer;
    if (m_musicBuffer) delete m_musicBuffer;
}

QByteArray SoundManager::createWavHeader(int dataSize, int sampleRate, int channels, int bitsPerSample)
{
    QByteArray header;
    QDataStream stream(&header, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    
    // RIFF header
    stream.writeRawData("RIFF", 4);
    stream << quint32(36 + dataSize);
    stream.writeRawData("WAVE", 4);
    
    // fmt chunk
    stream.writeRawData("fmt ", 4);
    stream << quint32(16);  // Tamaño del chunk
    stream << quint16(1);   // Formato PCM
    stream << quint16(channels);
    stream << quint32(sampleRate);
    stream << quint32(sampleRate * channels * bitsPerSample / 8);
    stream << quint16(channels * bitsPerSample / 8);
    stream << quint16(bitsPerSample);
    
    // data chunk
    stream.writeRawData("data", 4);
    stream << quint32(dataSize);
    
    return header;
}

QByteArray SoundManager::generateWaveform(double frequency, int durationMs, const QString& waveType)
{
    const int sampleRate = 44100;
    const int numSamples = (sampleRate * durationMs) / 1000;
    
    QByteArray audioData;
    QDataStream stream(&audioData, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    
    for (int i = 0; i < numSamples; i++) {
        double t = static_cast<double>(i) / sampleRate;
        double value = 0;
        
        if (waveType == "sine") {
            value = std::sin(2.0 * M_PI * frequency * t);
        } else if (waveType == "square") {
            value = std::sin(2.0 * M_PI * frequency * t) > 0 ? 1.0 : -1.0;
        } else if (waveType == "triangle") {
            value = 2.0 * std::abs(2.0 * (t * frequency - std::floor(t * frequency + 0.5))) - 1.0;
        }
        
        // Aplicar envelope (fade in/out)
        double envelope = 1.0;
        if (i < sampleRate * 0.01) { // Fade in 10ms
            envelope = static_cast<double>(i) / (sampleRate * 0.01);
        } else if (i > numSamples - sampleRate * 0.01) { // Fade out 10ms
            envelope = static_cast<double>(numSamples - i) / (sampleRate * 0.01);
        }
        
        qint16 sample = static_cast<qint16>(value * envelope * 32767 * 0.3); // 30% volumen
        stream << sample;
    }
    
    return createWavHeader(audioData.size()) + audioData;
}

QByteArray SoundManager::generateChord(const std::vector<double>& frequencies, int durationMs)
{
    const int sampleRate = 44100;
    const int numSamples = (sampleRate * durationMs) / 1000;
    
    QByteArray audioData;
    QDataStream stream(&audioData, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    
    for (int i = 0; i < numSamples; i++) {
        double t = static_cast<double>(i) / sampleRate;
        double value = 0;
        
        for (double freq : frequencies) {
            value += std::sin(2.0 * M_PI * freq * t) / frequencies.size();
        }
        
        // Envelope
        double envelope = 1.0;
        if (i < sampleRate * 0.01) {
            envelope = static_cast<double>(i) / (sampleRate * 0.01);
        } else if (i > numSamples - sampleRate * 0.05) {
            envelope = static_cast<double>(numSamples - i) / (sampleRate * 0.05);
        }
        
        qint16 sample = static_cast<qint16>(value * envelope * 32767 * 0.3);
        stream << sample;
    }
    
    return createWavHeader(audioData.size()) + audioData;
}

void SoundManager::setupSounds()
{
    // 🔊 Sonido de movimiento: Tono ascendente suave (C5 -> E5)
    QByteArray moveSound;
    moveSound += generateWaveform(523.25, 100, "sine");  // C5
    moveSound.remove(0, 44); // Quitar header duplicado
    moveSound.prepend(createWavHeader(moveSound.size()));
    
    m_moveBuffer = new QBuffer(this);
    m_moveBuffer->setData(moveSound);
    m_moveBuffer->open(QIODevice::ReadOnly);  // ✨ ABRIR BUFFER
    m_movePlayer->setSourceDevice(m_moveBuffer, QUrl("move.wav"));
    
    // 🎉 Sonido de victoria: Acorde mayor ascendente (C-E-G-C)
    QByteArray victorySound = generateChord({523.25, 659.25, 783.99}, 800);
    
    m_victoryBuffer = new QBuffer(this);
    m_victoryBuffer->setData(victorySound);
    m_victoryBuffer->open(QIODevice::ReadOnly);  // ✨ ABRIR BUFFER
    m_victoryPlayer->setSourceDevice(m_victoryBuffer, QUrl("victory.wav"));
    
    // ❌ Sonido de error: Tono descendente áspero
    QByteArray errorSound = generateWaveform(440, 150, "square");
    
    m_errorBuffer = new QBuffer(this);
    m_errorBuffer->setData(errorSound);
    m_errorBuffer->open(QIODevice::ReadOnly);  // ✨ ABRIR BUFFER
    m_errorPlayer->setSourceDevice(m_errorBuffer, QUrl("error.wav"));
    
    // 🖱️ Sonido de hover: Click corto agudo
    QByteArray hoverSound = generateWaveform(1200, 30, "sine");
    
    m_hoverBuffer = new QBuffer(this);
    m_hoverBuffer->setData(hoverSound);
    m_hoverBuffer->open(QIODevice::ReadOnly);  // ✨ ABRIR BUFFER
    m_hoverPlayer->setSourceDevice(m_hoverBuffer, QUrl("hover.wav"));
    
    // 🎯 Sonido de click: Click seco
    QByteArray clickSound = generateWaveform(1500, 40, "triangle");
    
    m_clickBuffer = new QBuffer(this);
    m_clickBuffer->setData(clickSound);
    m_clickBuffer->open(QIODevice::ReadOnly);  // ✨ ABRIR BUFFER
    m_clickPlayer->setSourceDevice(m_clickBuffer, QUrl("click.wav"));
    
    qDebug() << "✅ Sonidos generados exitosamente";
}

void SoundManager::setVolume(int volume)
{
    m_volume = qBound(0, volume, 100);
    float vol = m_volume / 100.0f;
    
    m_moveOutput->setVolume(vol);
    m_victoryOutput->setVolume(vol);
    m_errorOutput->setVolume(vol);
    m_hoverOutput->setVolume(vol);
    m_clickOutput->setVolume(vol);
    m_musicOutput->setVolume(vol * 0.5f);
}

void SoundManager::setMuted(bool muted)
{
    m_muted = muted;
    
    m_moveOutput->setMuted(muted);
    m_victoryOutput->setMuted(muted);
    m_errorOutput->setMuted(muted);
    m_hoverOutput->setMuted(muted);
    m_clickOutput->setMuted(muted);
    m_musicOutput->setMuted(muted);
}

void SoundManager::playMoveSound()
{
    if (m_muted) {
        qDebug() << "🔇 Sonido muteado";
        return;
    }
    
    qDebug() << "🔊 Reproduciendo sonido de movimiento...";
    qDebug() << "   Estado del reproductor:" << m_movePlayer->playbackState();
    qDebug() << "   Fuente:" << m_movePlayer->source();
    
    m_movePlayer->stop();
    m_movePlayer->setPosition(0);
    m_movePlayer->play();
    
    qDebug() << "   Nuevo estado:" << m_movePlayer->playbackState();
}

void SoundManager::playVictorySound()
{
    if (m_muted) {
        qDebug() << "🔇 Sonido muteado";
        return;
    }
    
    qDebug() << "🎉 Reproduciendo sonido de victoria...";
    
    m_victoryPlayer->stop();
    m_victoryPlayer->setPosition(0);
    m_victoryPlayer->play();
}

void SoundManager::playErrorSound()
{
    if (m_muted) {
        qDebug() << "🔇 Sonido muteado";
        return;
    }
    
    qDebug() << "❌ Reproduciendo sonido de error...";
    
    m_errorPlayer->stop();
    m_errorPlayer->setPosition(0);
    m_errorPlayer->play();
}

void SoundManager::playHoverSound()
{
    if (m_muted) return;
    
    m_hoverPlayer->stop();
    m_hoverPlayer->setPosition(0);
    m_hoverPlayer->play();
}

void SoundManager::playClickSound()
{
    if (m_muted) return;
    
    m_clickPlayer->stop();
    m_clickPlayer->setPosition(0);
    m_clickPlayer->play();
    
    qDebug() << "🖱️ Click";
}

void SoundManager::playBackgroundMusic()
{
    // Música de fondo relajante (loop)
    m_musicPlayer->setLoops(QMediaPlayer::Infinite);
    m_musicPlayer->play();
    
    qDebug() << "🎵 Música de fondo activada";
}

void SoundManager::stopBackgroundMusic()
{
    m_musicPlayer->stop();
    
    qDebug() << "⏹️ Música de fondo detenida";
}


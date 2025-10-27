#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QBuffer>
#include <vector>
#include <cmath>

// Generador de sonidos profesional con Qt6 Multimedia
class SoundManager : public QObject
{
    Q_OBJECT

public:
    explicit SoundManager(QObject *parent = nullptr);
    ~SoundManager();
    
    // Reproducir sonidos
    void playMoveSound();
    void playVictorySound();
    void playErrorSound();
    void playHoverSound();
    void playClickSound();
    void playBackgroundMusic();
    void stopBackgroundMusic();
    
    // Control de volumen
    void setVolume(int volume); // 0-100
    void setMuted(bool muted);
    bool isMuted() const { return m_muted; }
    
private:
    // Generar ondas de audio WAV programáticamente
    QByteArray generateWaveform(double frequency, int durationMs, const QString& waveType = "sine");
    QByteArray generateChord(const std::vector<double>& frequencies, int durationMs);
    QByteArray createWavHeader(int dataSize, int sampleRate = 44100, int channels = 1, int bitsPerSample = 16);
    
    // Reproductores
    QMediaPlayer* m_movePlayer;
    QMediaPlayer* m_victoryPlayer;
    QMediaPlayer* m_errorPlayer;
    QMediaPlayer* m_hoverPlayer;
    QMediaPlayer* m_clickPlayer;
    QMediaPlayer* m_musicPlayer;
    
    // Salidas de audio
    QAudioOutput* m_moveOutput;
    QAudioOutput* m_victoryOutput;
    QAudioOutput* m_errorOutput;
    QAudioOutput* m_hoverOutput;
    QAudioOutput* m_clickOutput;
    QAudioOutput* m_musicOutput;
    
    // Buffers de audio
    QBuffer* m_moveBuffer;
    QBuffer* m_victoryBuffer;
    QBuffer* m_errorBuffer;
    QBuffer* m_hoverBuffer;
    QBuffer* m_clickBuffer;
    QBuffer* m_musicBuffer;
    
    int m_volume;
    bool m_muted;
    
    void setupSounds();
};

#endif // SOUNDMANAGER_H

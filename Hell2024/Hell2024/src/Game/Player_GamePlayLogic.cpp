#include "Player.hpp"
#include "Core/Audio.hpp"

void Player::CheckForSuicide()
{
    if (IsAlive())
    {
        if (GetFeetPosition().y < Y_DEATH_ALTITUDE_LIMIT)
        {
            Kill();
            m_suicideCount++;
            m_killCount--;
            std::cout << "Fell into a black hole meaning you are now dead... (" << _playerName << ")" << "\n";
        }
    }
}

void Player::CheckForAndEvaluateFlashlight(float deltaTime)
{
    if (PressedFlashlight())
    {
        Audio::PlayAudio("Flashlight.wav", 1.0f);
        m_flashlightOn = !m_flashlightOn;
    }
}
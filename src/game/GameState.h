#pragma once

#include "util/NonCopyable.h"
#include "util/NonMovable.h"
#include "message/Mailbox.h"

class MessageBus;
class RenderEngine;
class InputEngine;
class AudioEngine;
class TextureManager;
class StylesheetManager;
class GuiManager;
class MusicManager;

class GameState : public NonCopyable, public NonMovable
{
public:
    struct Event
    {
        enum class Type{RESUME_GAME, NEW_GAME, LOAD_GAME, PAUSE_GAME, DISPLAY_MENU};

        Type type;
    };

    GameState();
    virtual ~GameState();

    static void setMessageBus(MessageBus* messageBus);
    static void setGameId(Id gameId);
    static void setRenderEngine(RenderEngine* renderEngine);
    static void setInputEngine(InputEngine* inputEngine);
    static void setAudioEngine(AudioEngine* audioEngine);
    static void setTextureManager(TextureManager* textureManager);
    static void setStylesheetManager(StylesheetManager* stylesheetManager);
    static void setGuiManager(GuiManager* guiManager);
    static void setMusicManager(MusicManager* musicManager);

    virtual void enter() = 0;
    virtual void handleMessages() = 0;
    virtual void update(float dt) = 0;
    virtual void draw() = 0;
    virtual void exit() = 0;

protected:
    static MessageBus* sMessageBus;
    static Id sGameId;
    static RenderEngine* sRenderEngine;
    static InputEngine* sInputEngine;
    static AudioEngine* sAudioEngine;
    static TextureManager* sTextureManager;
    static StylesheetManager* sStylesheetManager;
    static GuiManager* sGuiManager;
    static MusicManager* sMusicManager;

    Mailbox mMailbox;
};
